#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade Integradora 24: JSON e Serialização Rust-SQL.
 * 
 * Aprendizados: Serde, JSON no SQLite, UPSERT via Rust.
 * 
 * @author SENAI - Rust/SQL Master
 * @date 21/04/2026
 */

use rusqlite::{params, Connection, Result};
use serde::{Serialize, Deserialize}; // Traits para serialização
use serde_json; // Biblioteca para manipulação de texto JSON

/// Nossa Struct que representa os dados flexíveis dos sensores.
/// 'derive' gera automaticamente o código de conversão para JSON.
#[derive(Serialize, Deserialize, Debug)]
struct TelemetriaIoT {
    temp: f64,
    bateria: u32,
    status: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    versao_sensor: Option<String>, // Campo opcional
}

fn main() -> Result<()> {
    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE TELEMETRIA JSON     ");
    println!("===============================================");

    // 1. CONEXÃO: Apontando para o banco da Atividade 13 de SQL.
    let path = "../sql-mastery/exercicios/13-json-e-upsert-avancado/database.db";
    let conn = Connection::open(path)?;

    // 2. CRIAÇÃO DO OBJETO RUST
    let info_drone = TelemetriaIoT {
        temp: 24.5,
        bateria: 92,
        status: String::from("Estável"),
        versao_sensor: Some(String::from("v2.1")),
    };

    // 3. SERIALIZAÇÃO: Transformando Struct em String JSON
    let json_payload = serde_json::to_string(&info_drone).unwrap();
    println!("\x1b[35m[RUST]:\x1b[0m Objeto serializado para JSON:");
    println!(">> {}\n", json_payload);

    // 4. ESCRITA NO BANCO (UPSERT)
    // Usamos o comando que você aprendeu no SQL para lidar com conflitos de ID.
    let drone_serial = "SN-MASTER-01";
    println!("\x1b[33m[SISTEMA]:\x1b[0m Enviando dados para a Fortaleza SQL...");
    
    conn.execute(
        "INSERT INTO telemetria_avancada (drone_serial, dados_json)
         VALUES (?, ?)
         ON CONFLICT(drone_serial) DO UPDATE SET
            dados_json = excluded.dados_json,
            ultima_atualizacao = CURRENT_TIMESTAMP",
        params![drone_serial, json_payload],
    )?;

    // 5. LEITURA E DESERIALIZAÇÃO
    println!("\x1b[34m[SISTEMA]:\x1b[0m Recuperando dados para conferência...");
    
    let mut stmt = conn.prepare("SELECT dados_json FROM telemetria_avancada WHERE drone_serial = ?")?;
    let json_do_banco: String = stmt.query_row(params![drone_serial], |row| row.get(0))?;

    // Transformando o texto do banco de volta para a Struct Rust
    let objeto_recuperado: TelemetriaIoT = serde_json::from_str(&json_do_banco).unwrap();

    println!("\n\x1b[32m[SUCESSO]:\x1b[0m Dados recuperados como Objeto Rust:");
    println!("{:#?}", objeto_recuperado);

    println!("===============================================");
    Ok(())
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O PODER DO JSON NO BACKEND
    ===============================================================

    1. SERDE (SERIALIZE/DESERIALIZE): 
       - É a biblioteca mais poderosa do ecossistema Rust. 
       - Ela permite que o Rust converse com qualquer formato 
         (JSON, YAML, XML, Binary) de forma segura e veloz.

    2. FLEXIBILIDADE DO BANCO: 
       - Graças ao JSON, se o drone enviar um novo campo amanhã, o 
         nosso banco SQL não precisará de um 'ALTER TABLE'. O Rust 
         apenas adiciona um campo na struct.

    3. UPSERT NO BACKEND: 
       - O comando 'ON CONFLICT' garante que a nossa aplicação seja 
         Idempotente (pode rodar 1000 vezes sem criar duplicatas).

    VANTAGEM DIDÁTICA: 
    O aluno aprende a lidar com a variabilidade dos dados modernos 
    sem perder a rigidez da tipagem do Rust.
    ===============================================================
*/

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
