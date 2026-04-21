/**
 * @file main.rs
 * @brief Atividade Integradora 23: Gerenciamento de Transações.
 *
 * Aprendizados: Atomicidade, Rollback automático, rusqlite transactions.
 *
 * @author SENAI - Rust/SQL Master
 * @date 21/04/2026
 */
use rusqlite::{Connection, Result, params};
use std::io::{self, Write};

fn exibir_estado_atual(conn: &Connection) -> Result<()> {
    let estoque: i32 = conn.query_row(
        "SELECT quantidade FROM estoque_geral WHERE item = 'Bateria Lipo 4S'",
        [],
        |r| r.get(0),
    )?;
    let drone: i32 = conn.query_row(
        "SELECT quantidade FROM carga_drone WHERE item = 'Bateria Lipo 4S'",
        [],
        |r| r.get(0),
    )?;
    println!(
        "\n[ESTADO ATUAL]: Armazém: {} un | Drone: {} un",
        estoque, drone
    );
    Ok(())
}

fn realizar_transferencia(conn: &mut Connection, qtd: i32, simular_erro: bool) -> Result<()> {
    // 1. INICIANDO TRANSAÇÃO NO RUST
    // O objeto 'tx' controla o banco agora.
    let tx = conn.transaction()?;

    println!(
        "\x1b[33m[SISTEMA]: Iniciando transferência de {} unidades...\x1b[0m",
        qtd
    );

    // Passo A: Retirar do estoque
    tx.execute(
        "UPDATE estoque_geral SET quantidade = quantidade - ? WHERE item = 'Bateria Lipo 4S'",
        params![qtd],
    )?;

    // SIMULAÇÃO DE FALHA
    if simular_erro {
        println!("\x1b[31m[ERRO CRÍTICO]: Falha na conexão com o Drone! Cancelando...\x1b[0m");
        // Ao retornar erro aqui, o Rust descartará 'tx' e o banco fará ROLLBACK automático.
        return Err(rusqlite::Error::InvalidQuery);
    }

    // Passo B: Adicionar ao drone
    tx.execute(
        "UPDATE carga_drone SET quantidade = quantidade + ? WHERE item = 'Bateria Lipo 4S'",
        params![qtd],
    )?;

    // 2. CONFIRMAÇÃO (COMMIT)
    tx.commit()?; // Somente aqui as mudanças tornam-se permanentes.
    println!("\x1b[32m[SUCESSO]: Transferência concluída e salva no HD.\x1b[0m");
    Ok(())
}

fn main() -> Result<()> {
    let mut conn = Connection::open("../sql-mastery/exercicios/06-transacoes-acid/database.db")?;

    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE CARGA BLINDADA      ");
    println!("===============================================");

    exibir_estado_atual(&conn)?;

    // TESTE 1: Transferência com Sucesso
    println!("\n--- TESTE 1: OPERAÇÃO NORMAL ---");
    let _ = realizar_transferencia(&mut conn, 10, false);
    exibir_estado_atual(&conn)?;

    // TESTE 2: Transferência com Falha (Garantindo que o estoque não mude)
    println!("\n--- TESTE 2: OPERAÇÃO COM FALHA (ROLLBACK) ---");
    let _ = realizar_transferencia(&mut conn, 50, true);
    exibir_estado_atual(&conn)?;

    println!("===============================================");
    Ok(())
}

/*
    ===============================================================
    RESUMO TEÓRICO: TRANSAÇÕES NO BACKEND
    ===============================================================

    1. O OBJETO TX:
       - O rusqlite cria um objeto temporário que representa a
         transação. Se ele sair de escopo sem o 'commit()', o banco
         desfaz tudo automaticamente. Isso é RAII aplicado ao SQL.

    2. SEGURANÇA DE DADOS:
       - Imagine que a bateria do seu computador acabe entre o
         Passo A e o Passo B. O motor do SQLite garantirá que o
         armazém não perca o item se o drone não o receber.

    3. VANTAGEM DIDÁTICA:
       - O aluno aprende que o Backend é o "Mestre de Cerimônias"
         da integridade, usando o poder do Rust para tratar as
         falhas de negócio do SQL.
    ===============================================================
*/
