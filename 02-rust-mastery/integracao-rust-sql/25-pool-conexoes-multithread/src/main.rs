#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
use r2d2::Pool; // O objeto do Pool
/**
 * @file main.rs
 * @brief Atividade Integradora 25: Connection Pooling e Multithreading.
 *
 * Aprendizados: r2d2 Pool, Arc compartilhado, Escrita concorrente em SQL.
 *
 * @author SENAI - Master Orchestrator
 * @date 21/04/2026
 */
use r2d2_sqlite::SqliteConnectionManager; // Gerenciador de conexões SQLite
use std::sync::Arc; // Para compartilhar o pool entre threads
use std::thread; // Para criar a frota paralela
use std::time::Duration;

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - CENTRAL DE ESCALA MASSIVA      ");
    println!("===============================================");

    // 1. CONFIGURAÇÃO DO POOL
    // Criamos um gerenciador que aponta para o banco de automação (Ativ 09 SQL)
    let manager = SqliteConnectionManager::file(
        "../sql-mastery/exercicios/09-gatilhos-automacao/database.db",
    );

    // Criamos o Pool que manterá, por exemplo, até 5 conexões abertas ao mesmo tempo.
    let pool = Pool::builder()
        .max_size(5)
        .build(manager)
        .expect("Falha ao criar pool de conexões");

    // Envolvemos o pool em um Arc para que ele possa viajar entre threads com segurança.
    let pool_compartilhado = Arc::new(pool);

    println!("[SISTEMA]: Pool de conexões inicializado (Max: 5).");

    // 2. A FROTA MULTITHREAD
    let mut handles = vec![];

    for i in 1..=10 {
        let pool_thread = Arc::clone(&pool_compartilhado);

        let handle = thread::spawn(move || {
            // Cada thread solicita uma conexão ao Pool.
            // Se as 5 conexões estiverem ocupadas, a thread espera automaticamente.
            let conn = pool_thread.get().expect("Falha ao obter conexão do pool");

            println!(
                "   \x1b[33m>> Drone #{}:\x1b[0m Conexão obtida. Registrando log...",
                i
            );

            // Simula um tempo de processamento
            thread::sleep(Duration::from_millis(100));

            // Realiza uma inserção no banco
            conn.execute(
                "INSERT INTO vendas_registro (produto_id, qtd_vendida) VALUES (1, ?)",
                [i], // Registrando a ID do drone como quantidade vendida para teste
            )
            .expect("Falha ao inserir");

            println!(
                "   \x1b[32m[OK] Drone #{}:\x1b[0m Dados salvos com sucesso.",
                i
            );
            // Ao sair de escopo, a 'conn' volta para o pool automaticamente (não fecha!).
        });

        handles.push(handle);
    }

    // 3. SINCRONIZAÇÃO
    for h in handles {
        h.join().unwrap();
    }

    println!("\n[SISTEMA]: Todas as threads concluíram a operação.");

    // 4. VALIDAÇÃO FINAL
    let conn_final = pool_compartilhado.get().unwrap();
    let total: i32 = conn_final
        .query_row("SELECT COUNT(*) FROM vendas_registro", [], |r| r.get(0))
        .unwrap();

    println!("===============================================");
    println!("RESUMO DA OPERAÇÃO:");
    println!(
        "Total de registros inseridos concorrentemente: \x1b[36m{}\x1b[0m",
        total
    );
    println!("===============================================");
}

/*
    ===============================================================
    RESUMO TEÓRICO: ORQUESTRAÇÃO DE ALTA PERFORMANCE
    ===============================================================

    1. O PROBLEMA DA CONEXÃO ÚNICA:
       - No Rust, um objeto 'Connection' não pode ser compartilhado
         entre threads (não é thread-safe).
       - O Pool resolve isso entregando uma 'Connection' diferente
         para cada thread que pedir.

    2. ECONOMIA DE RECURSOS:
       - Abrir e fechar um arquivo de banco é uma operação cara.
       - O Pool mantém o arquivo aberto, apenas reciclando os
         ponteiros, o que é milhares de vezes mais rápido.

    3. BACKPRESSURE:
       - Note o 'max_size(5)'. Se tivéssemos 10.000 drones, o banco
         não explodiria, pois o Pool limitaria a pressão a apenas
         5 acessos por vez, enfileirando o restante.

    VANTAGEM DIDÁTICA:
    O aluno aprende a arquitetura de SERVIDORES REAIS, onde a
    concorrência é a regra e o gerenciamento de recursos é o segredo
    do sucesso.
    ===============================================================
*/

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
