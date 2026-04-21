/**
 * @file main.rs
 * @brief Atividade Integradora 26: Migrações Automáticas.
 *
 * Aprendizados: DDL via Backend, Versionamento de Banco, Transações de Esquema.
 *
 * @author SENAI - Master Orchestrator
 * @date 21/04/2026
 */
use rusqlite::{Connection, Result};

/// Estrutura para representar uma migração de banco de dados.
struct Migracao {
    versao: i32,
    sql: &'static str,
    descricao: &'static str,
}

fn inicializar_controle_versao(conn: &Connection) -> Result<()> {
    conn.execute(
        "CREATE TABLE IF NOT EXISTS schema_version (
            versao INTEGER PRIMARY KEY,
            data_atualizacao TEXT DEFAULT CURRENT_TIMESTAMP
        )",
        [],
    )?;
    Ok(())
}

fn obter_versao_atual(conn: &Connection) -> Result<i32> {
    let mut stmt = conn.prepare("SELECT MAX(versao) FROM schema_version")?;
    let versao: Option<i32> = stmt.query_row([], |row| row.get(0))?;
    Ok(versao.unwrap_or(0))
}

fn executar_migracoes(conn: &mut Connection) -> Result<()> {
    let plano = vec![
        Migracao {
            versao: 1,
            sql: "CREATE TABLE IF NOT EXISTS telemetria_v2 (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    drone_id TEXT NOT NULL,
                    altitude REAL
                  )",
            descricao: "Criando tabela de telemetria v2",
        },
        Migracao {
            versao: 2,
            sql: "ALTER TABLE telemetria_v2 ADD COLUMN sinal_wifi INTEGER DEFAULT 0",
            descricao: "Adicionando suporte a monitoramento de sinal Wi-Fi",
        },
    ];

    let versao_atual = obter_versao_atual(conn)?;
    println!(
        "\x1b[34m[SISTEMA]:\x1b[0m Versão atual do banco: v{}",
        versao_atual
    );

    for m in plano {
        if m.versao > versao_atual {
            println!("\n\x1b[33m--- APLICANDO MIGRAÇÃO v{} ---\x1b[0m", m.versao);
            println!(">> Descrição: {}", m.descricao);

            // Iniciamos uma transação para cada migração individual
            let tx = conn.transaction()?;

            // Executa o SQL da migração
            tx.execute(m.sql, [])?;

            // Atualiza a tabela de controle de versão
            tx.execute("INSERT INTO schema_version (versao) VALUES (?)", [m.versao])?;

            tx.commit()?;
            println!(
                "\x1b[32m[SUCESSO]:\x1b[0m Banco atualizado para v{}.",
                m.versao
            );
        }
    }

    Ok(())
}

fn main() -> Result<()> {
    println!("===============================================");
    println!("     SKYCARGO - MOTOR DE MIGRAÇÃO AUTOMÁTICA   ");
    println!("===============================================");

    // Criamos um novo banco específico para esta atividade
    let mut conn = Connection::open("drone_os.db")?;

    // 1. Prepara o banco para rastrear versões
    inicializar_controle_versao(&conn)?;

    // 2. Executa o plano de atualização
    executar_migracoes(&mut conn)?;

    println!("\n[SISTEMA]: Verificando estrutura final...");
    let versao_final = obter_versao_atual(&conn)?;
    println!(
        "\x1b[32m[OK]:\x1b[0m Sistema operacional do drone em v{}.",
        versao_final
    );

    println!("===============================================");
    Ok(())
}

/*
    ===============================================================
    RESUMO TEÓRICO: MIGRAÇÕES (SCHEMA EVOLUTION)
    ===============================================================

    1. POR QUE AUTOMATIZAR?
       - Em sistemas distribuídos (como drones ou apps de celular),
         o banco de dados é atualizado via código.
       - Isso garante que todos os usuários tenham a mesma estrutura.

    2. ATOMICIDADE DE ESQUEMA:
       - Usamos transações (tx) nas migrações. Se a alteração de
         coluna falhar, o registro de versão também não é inserido,
         evitando que o banco fique "mentindo" sua versão.

    3. DDL NO BACKEND:
       - DDL (Data Definition Language) são os comandos CREATE, ALTER,
         DROP. O Rust é excelente para orquestrar esses comandos com
         segurança.

    VANTAGEM DIDÁTICA:
    O aluno aprende que ser Engenheiro é pensar no CICLO DE VIDA do
    software, não apenas no código que roda hoje, mas em como esse
    código sobreviverá a futuras mudanças.
    ===============================================================
*/
