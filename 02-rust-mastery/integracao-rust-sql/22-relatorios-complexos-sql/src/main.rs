#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade Integradora 22: Relatórios com JOIN Rust-SQL.
 *
 * Aprendizados: Queries multi-tabela, Mapeamento complexo, Aliasing.
 *
 * @author SENAI - Rust/SQL Master
 * @date 21/04/2026
 */
use rusqlite::{Connection, Result};

/// Struct que consolida dados de duas tabelas diferentes.
#[derive(Debug)]
struct ProdutoFornecedor {
    produto: String,
    preco: f64,
    fornecedor: String,
    pais: String,
}

fn main() -> Result<()> {
    println!("===============================================");
    println!("     SKYCARGO - RELATÓRIO GLOBAL DE COMPRAS    ");
    println!("===============================================");

    // 1. CONEXÃO: Apontando para o banco da Atividade 03 de SQL.
    let path = "../sql-mastery/exercicios/03-relacionamento-fornecedores/database.db";
    let conn = Connection::open(path)?;

    // 2. QUERY COMPLEXA: Usando INNER JOIN diretamente no Rust.
    let mut stmt = conn.prepare(
        "
        SELECT p.nome, p.preco, f.nome, f.pais
        FROM produtos p
        INNER JOIN fornecedores f ON p.fornecedor_id = f.id
    ",
    )?;

    // 3. MAPEAMENTO: Transformando o resultado do JOIN em nossa Struct.
    let relatorio_iter = stmt.query_map([], |row| {
        Ok(ProdutoFornecedor {
            produto: row.get(0)?,
            preco: row.get(1)?,
            fornecedor: row.get(2)?,
            pais: row.get(3)?,
        })
    })?;

    // 4. EXIBIÇÃO: Interface profissional.
    println!("\n\x1b[35m[LOGÍSTICA]:\x1b[0m Cruzando dados de estoque e origem...\n");

    for item in relatorio_iter {
        let it = item?;
        println!("\x1b[33mPRODUTO:\x1b[0m {}", it.produto);
        println!("  ├─ Preço: R$ {:.2}", it.preco);
        println!("  └─ Origem: {} ({})", it.fornecedor, it.pais);
        println!("-----------------------------------------------");
    }

    println!("\n\x1b[32m[SUCESSO]: Relatório consolidado gerado com dados cross-table.\x1b[0m");
    println!("===============================================");

    Ok(())
}

/*
    ===============================================================
    RESUMO TEÓRICO: JOINs NO BACKEND
    ===============================================================

    1. POR QUE FAZER O JOIN NO SQL?
       - Poderíamos buscar os produtos e depois os fornecedores no
         Rust, mas isso seria LENTO (2 viagens ao banco).
       - Fazer o JOIN no SQL é 100x mais rápido, pois o banco de
         dados é otimizado para essa operação atômica.

    2. MAPEAMENTO DE STRUCTS:
       - No Rust, criamos structs que não precisam ser iguais às
         tabelas. Podemos criar "Structs de Relatório" que
         consolidam apenas os campos que queremos exibir.

    3. SEGURANÇA DE CONEXÃO:
       - O Rust garante que a conexão será fechada corretamente
         quando o 'main' terminar, mesmo se houver erro no meio
         da listagem.

    VANTAGEM DIDÁTICA:
    O aluno aprende que o Backend não deve "pensar" em tabelas, mas
    em "objetos de negócio" que são alimentados pela inteligência
    relacional do SQL.
    ===============================================================
*/

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
