/**
 * @file main.rs
 * @brief Atividade Integradora: Escrita e Leitura Rust-SQL.
 *
 * Aprendizados: Prepared Statements, Inserção via Rust, Interatividade.
 *
 * @author SENAI - Rust/SQL Master
 * @date 21/04/2026
 */
use rusqlite::{Connection, Result, params};
use std::io::{self, Write};

#[derive(Debug)]
struct Produto {
    id: i32,
    nome: String,
    preco: f64,
    estoque: i32,
}

/// Função utilitária para capturar entrada do usuário
fn pedir_input(label: &str) -> String {
    print!("{}", label);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Falha ao ler");
    input.trim().to_string()
}

fn listar_estoque(conn: &Connection) -> Result<()> {
    let mut stmt = conn.prepare("SELECT id, nome, preco, estoque FROM produtos")?;
    let produtos_iter = stmt.query_map([], |row| {
        Ok(Produto {
            id: row.get(0)?,
            nome: row.get(1)?,
            preco: row.get(2)?,
            estoque: row.get(3)?,
        })
    })?;

    println!("\n\x1b[36m--- ESTOQUE ATUAL ---\x1b[0m");
    for produto in produtos_iter {
        let p = produto?;
        println!(
            "ID: {:<3} | {:<20} | R$ {:>8.2} | Qtd: {}",
            p.id, p.nome, p.preco, p.estoque
        );
    }
    Ok(())
}

fn main() -> Result<()> {
    let path = "../sql-mastery/exercicios/01-explorador-estoque/database.db";
    let conn = Connection::open(path)?;

    println!("===============================================");
    println!("     SKYCARGO - GESTOR DE ESTOQUE PRO          ");
    println!("===============================================");

    loop {
        println!("\nMENU:");
        println!("1. Listar Produtos");
        println!("2. Cadastrar Novo Produto");
        println!("0. Sair");

        let opcao = pedir_input("Escolha: ");

        match opcao.as_str() {
            "1" => {
                listar_estoque(&conn)?;
            }
            "2" => {
                println!("\n\x1b[33m--- CADASTRO DE PRODUTO ---\x1b[0m");
                let nome = pedir_input("Nome do item: ");
                let preco: f64 = pedir_input("Preço (R$): ").parse().unwrap_or(0.0);
                let qtd: i32 = pedir_input("Quantidade: ").parse().unwrap_or(0);

                // SEGURANÇA: Usamos 'params!' para evitar SQL Injection.
                // O Rust envia o comando e os dados separadamente para o SQLite.
                conn.execute(
                    "INSERT INTO produtos (nome, categoria, preco, estoque) VALUES (?, 'Integracao', ?, ?)",
                    params![nome, preco, qtd],
                )?;

                println!("\x1b[32m[SUCESSO]: Produto inserido no banco de dados!\x1b[0m");
            }
            "0" => {
                println!("Encerrando gestor...");
                break;
            }
            _ => println!("Opção inválida."),
        }
    }

    Ok(())
}
