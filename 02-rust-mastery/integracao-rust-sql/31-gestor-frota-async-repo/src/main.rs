/**
 * @file main.rs
 * @brief Atividade Integradora 31: Gestor de Frota Pro (Repository Pattern).
 *
 * Aprendizados: Padrão Repository, Async Traits, tokio-rusqlite.
 *
 * @author SENAI - Arquiteto de Sistemas
 * @date 21/04/2026
 */
use async_trait::async_trait;
use std::io::{self, Write};
use tokio_rusqlite::Connection;

// -----------------------------------------------------------------------------
// 1. MODELO DE NEGÓCIO
// -----------------------------------------------------------------------------
#[derive(Debug)]
struct Drone {
    id: i32,
    serial: String,
    status: String,
}

// -----------------------------------------------------------------------------
// 2. O CONTRATO (REPOSITORY TRAIT)
// -----------------------------------------------------------------------------
#[async_trait]
trait DroneRepository {
    async fn listar(&self) -> Result<Vec<Drone>, Box<dyn std::error::Error + Send + Sync>>;
    async fn cadastrar(
        &self,
        serial: String,
    ) -> Result<(), Box<dyn std::error::Error + Send + Sync>>;
}

// -----------------------------------------------------------------------------
// 3. IMPLEMENTAÇÃO ESPECÍFICA (TOKIO-RUSQLITE)
// -----------------------------------------------------------------------------
struct SqliteRepo {
    conn: Connection,
}

#[async_trait]
impl DroneRepository for SqliteRepo {
    async fn listar(&self) -> Result<Vec<Drone>, Box<dyn std::error::Error + Send + Sync>> {
        let drones = self
            .conn
            .call(|c| {
                let mut stmt = c.prepare("SELECT id, serial, status FROM drones_pro")?;
                let iter = stmt.query_map([], |row| {
                    Ok(Drone {
                        id: row.get(0)?,
                        serial: row.get(1)?,
                        status: row.get(2)?,
                    })
                })?;

                let mut res = Vec::new();
                for item in iter {
                    res.push(item?);
                }
                Ok(res)
            })
            .await?;

        Ok(drones)
    }

    async fn cadastrar(
        &self,
        serial: String,
    ) -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
        self.conn
            .call(move |c| {
                c.execute(
                    "INSERT INTO drones_pro (serial, status) VALUES (?, 'PRONTO')",
                    [serial],
                )?;
                Ok(()) // Retorno explícito do Result para a closure
            })
            .await?;
        Ok(())
    }
}

// -----------------------------------------------------------------------------
// 4. INTERFACE DE USUÁRIO (UI)
// -----------------------------------------------------------------------------
async fn pedir_input(label: &str) -> String {
    print!("{}", label);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Falha ao ler");
    input.trim().to_string()
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("===============================================");
    println!("     SKYCARGO PRO - GESTOR ASSÍNCRONO          ");
    println!("===============================================");

    // Inicializando banco de dados
    let conn = Connection::open_in_memory().await?;

    conn.call(|c| {
        c.execute(
            "CREATE TABLE drones_pro (id INTEGER PRIMARY KEY, serial TEXT UNIQUE, status TEXT)",
            [],
        )?;
        Ok(())
    })
    .await?;

    // Injetando a conexão na implementação do Repositório
    let repo = SqliteRepo { conn };

    loop {
        println!("\nMENU PRO (Async):");
        println!("1. Listar Frota");
        println!("2. Novo Drone");
        println!("0. Sair");

        let opcao = pedir_input("Opção: ").await;

        match opcao.as_str() {
            "1" => match repo.listar().await {
                Ok(lista) => {
                    println!("\n\x1b[36m--- LISTA DE DRONES ---\x1b[0m");
                    if lista.is_empty() {
                        println!("(Frota vazia)");
                    }
                    for d in lista {
                        println!("[#{}] {} -> {}", d.id, d.serial, d.status);
                    }
                }
                Err(e) => println!("\x1b[31m[ERRO]: {}\x1b[0m", e),
            },
            "2" => {
                let serial = pedir_input("Serial: ").await;
                if let Err(e) = repo.cadastrar(serial).await {
                    println!("\x1b[31m[ERRO]: Falha ao salvar: {}\x1b[0m", e);
                } else {
                    println!("\x1b[32m[OK]: Salvo assincronamente.\x1b[0m");
                }
            }
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    Ok(())
}
