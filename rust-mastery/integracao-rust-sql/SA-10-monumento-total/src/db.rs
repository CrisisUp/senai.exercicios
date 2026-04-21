use anyhow::{Context, Result};
use r2d2::Pool;
use r2d2_sqlite::SqliteConnectionManager;
use rusqlite::params;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Telemetria {
    pub bateria: u32,
    pub distancia: f64,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Drone {
    pub id: Option<i32>,
    pub serial: String,
    pub regiao: String,
}

pub type SqlPool = Pool<SqliteConnectionManager>;

pub struct SkyRepo {
    pool: SqlPool,
}

impl SkyRepo {
    pub fn new(file_path: &str) -> Result<Self> {
        let manager = SqliteConnectionManager::file(file_path);
        let pool = Pool::new(manager).context("Falha ao criar o pool de conexões SQLite")?;
        Ok(Self { pool })
    }

    pub fn inicializar(&self) -> Result<()> {
        let conn = self.pool.get().context("Erro ao obter conexão")?;
        conn.execute_batch(
            "
            PRAGMA foreign_keys = ON;
            CREATE TABLE IF NOT EXISTS frota_final (
                id INTEGER PRIMARY KEY,
                serial TEXT UNIQUE NOT NULL,
                regiao TEXT NOT NULL
            );
            CREATE TABLE IF NOT EXISTS operacoes_final (
                id INTEGER PRIMARY KEY,
                drone_serial TEXT NOT NULL,
                telemetria_json TEXT NOT NULL,
                data_hora TEXT DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY(drone_serial) REFERENCES frota_final(serial) ON DELETE CASCADE
            );
        ",
        ).context("Falha ao criar esquema")?;
        Ok(())
    }

    // --- CRUD DE FROTA (ENGINEERING ELITE) ---

    pub fn cadastrar_drone(&self, serial: &str, regiao: &str) -> Result<()> {
        let conn = self.pool.get()?;
        conn.execute(
            "INSERT INTO frota_final (serial, regiao) VALUES (?, ?)",
            params![serial, regiao],
        ).context(format!("Falha ao cadastrar drone {}", serial))?;
        Ok(())
    }

    pub fn listar_frota(&self) -> Result<Vec<Drone>> {
        let conn = self.pool.get()?;
        let mut stmt = conn.prepare("SELECT id, serial, regiao FROM frota_final")?;
        let rows = stmt.query_map([], |row| {
            Ok(Drone {
                id: Some(row.get(0)?),
                serial: row.get(1)?,
                regiao: row.get(2)?,
            })
        })?;

        let mut frota = Vec::new();
        for res in rows { frota.push(res?); }
        Ok(frota)
    }

    pub fn atualizar_regiao(&self, serial: &str, nova_regiao: &str) -> Result<()> {
        let conn = self.pool.get()?;
        let affected = conn.execute(
            "UPDATE frota_final SET regiao = ? WHERE serial = ?",
            params![nova_regiao, serial],
        )?;
        if affected == 0 { anyhow::bail!("Drone {} não encontrado para atualização", serial); }
        Ok(())
    }

    pub fn remover_drone(&self, serial: &str) -> Result<()> {
        let conn = self.pool.get()?;
        conn.execute("DELETE FROM frota_final WHERE serial = ?", params![serial])?;
        Ok(())
    }

    // --- OPERAÇÕES DE MISSÃO ---

    pub fn registrar_missao(&self, serial: &str, telemetria: Telemetria) -> Result<()> {
        let conn = self.pool.get()?;
        let json_payload = serde_json::to_string(&telemetria)?;
        conn.execute(
            "INSERT INTO operacoes_final (drone_serial, telemetria_json) VALUES (?, ?)",
            params![serial, json_payload],
        ).context("Falha ao registrar missão. O drone existe na frota?")?;
        Ok(())
    }

    pub fn gerar_dashboard(&self) -> Result<Vec<(String, f64, i32)>> {
        let conn = self.pool.get()?;
        let mut stmt = conn.prepare(
            "
            SELECT drone_serial, 
                   SUM(json_extract(telemetria_json, '$.distancia')) as km_total,
                   RANK() OVER(ORDER BY SUM(json_extract(telemetria_json, '$.distancia')) DESC) as rank
            FROM operacoes_final
            GROUP BY drone_serial
            ",
        )?;
        let rows = stmt.query_map([], |row| Ok((row.get(0)?, row.get(1)?, row.get(2)?)))?;
        let mut res = Vec::new();
        for r in rows { res.push(r?); }
        Ok(res)
    }
}

// -----------------------------------------------------------------------------
// SEÇÃO DE TESTES (ENGENHARIA DE QUALIDADE)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    // Helper para criar um repositório limpo em memória para cada teste
    fn setup_test_repo() -> SkyRepo {
        let repo = SkyRepo::new(":memory:").unwrap();
        repo.inicializar().unwrap();
        repo
    }

    #[test]
    fn test_cadastrar_e_listar_drone() {
        let repo = setup_test_repo();
        repo.cadastrar_drone("TEST-01", "Brasil").unwrap();
        
        let frota = repo.listar_frota().unwrap();
        assert_eq!(frota.len(), 1);
        assert_eq!(frota[0].serial, "TEST-01");
    }

    #[test]
    fn test_erro_serial_duplicado() {
        let repo = setup_test_repo();
        repo.cadastrar_drone("DUPLICADO", "Sul").unwrap();
        let resultado = repo.cadastrar_drone("DUPLICADO", "Norte");
        
        assert!(resultado.is_err(), "Deveria falhar ao cadastrar serial duplicado");
    }

    #[test]
    fn test_atualizar_regiao() {
        let repo = setup_test_repo();
        repo.cadastrar_drone("UP-01", "Antiga").unwrap();
        repo.atualizar_regiao("UP-01", "Nova").unwrap();
        
        let frota = repo.listar_frota().unwrap();
        assert_eq!(frota[0].regiao, "Nova");
    }

    #[test]
    fn test_remover_drone_e_cascata() {
        let repo = setup_test_repo();
        repo.cadastrar_drone("DEL-01", "Leste").unwrap();
        
        // Registra missão para testar o CASCADE
        repo.registrar_missao("DEL-01", Telemetria { bateria: 100, distancia: 50.0 }).unwrap();
        
        repo.remover_drone("DEL-01").unwrap();
        
        let frota = repo.listar_frota().unwrap();
        assert!(frota.is_empty());
        
        let dash = repo.gerar_dashboard().unwrap();
        assert!(dash.is_empty(), "Logs de missão deveriam sumir com o drone (CASCADE)");
    }

    #[test]
    fn test_dashboard_ranking() {
        let repo = setup_test_repo();
        repo.cadastrar_drone("ALPHA", "R1").unwrap();
        repo.cadastrar_drone("BETA", "R2").unwrap();
        
        // BETA voa mais que ALPHA
        repo.registrar_missao("ALPHA", Telemetria { bateria: 80, distancia: 100.0 }).unwrap();
        repo.registrar_missao("BETA", Telemetria { bateria: 90, distancia: 250.0 }).unwrap();
        
        let dash = repo.gerar_dashboard().unwrap();
        assert_eq!(dash[0].0, "BETA"); // Rank #1
        assert_eq!(dash[0].2, 1);      // Rank integer
        assert_eq!(dash[1].0, "ALPHA"); // Rank #2
    }
}
