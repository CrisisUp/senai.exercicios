const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
//! @author Cristiano
//! @date 2026

#[cfg(test)]
mod tests {
    use rusqlite::{params, Connection, Result};

    /**
     * @file lib.rs
     * @brief Testes de Integração SQL (Nível Engenharia de Elite).
     * 
     * Valida a integridade dos gatilhos e cálculos financeiros 
     * em um ambiente isolado (:memory:).
     */

    #[test]
    fn test_sql_trigger_audit() -> Result<()> {
        let conn = Connection::open_in_memory()?;

        // 1. Setup: Criar tabelas e Gatilho de Auditoria
        conn.execute(
            "CREATE TABLE frota (id INTEGER PRIMARY KEY, nome TEXT, saldo REAL)",
            [],
        )?;

        conn.execute(
            "CREATE TABLE auditoria (id INTEGER PRIMARY KEY, frota_id INTEGER, antigo_saldo REAL, novo_saldo REAL)",
            [],
        )?;

        conn.execute(
            "CREATE TRIGGER audit_saldo AFTER UPDATE OF saldo ON frota
             BEGIN
                INSERT INTO auditoria (frota_id, antigo_saldo, novo_saldo)
                VALUES (old.id, old.saldo, new.saldo);
             END",
            [],
        )?;

        // 2. Act: Inserir e Atualizar
        conn.execute("INSERT INTO frota (nome, saldo) VALUES (?1, ?2)", params!["Drone-Alpha", 100.0])?;
        conn.execute("UPDATE frota SET saldo = ?1 WHERE id = ?2", params![150.0, 1])?;

        // 3. Assert: Verificar se o gatilho funcionou
        let count: i32 = conn.query_row("SELECT COUNT(*) FROM auditoria", [], |r| r.get(0))?;
        assert_eq!(count, 1);

        let (antigo, novo): (f64, f64) = conn.query_row(
            "SELECT antigo_saldo, novo_saldo FROM auditoria WHERE frota_id = 1",
            [],
            |r| Ok((r.get(0)?, r.get(1)?)),
        )?;

        assert_eq!(antigo, 100.0);
        assert_eq!(novo, 150.0);

        Ok(())
    }
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */
