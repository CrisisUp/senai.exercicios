/**
 * @file main.rs
 * @brief SA-01: Sistema de Rastreamento de Drones de Resgate.
 * 
 * Integração de Lógica, Enums, Pattern Matching e Ownership.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

use std::fmt;

/// Representa os estados possíveis de um drone na frota.
#[derive(Debug, PartialEq)]
enum StatusDrone {
    Disponivel,
    EmMissao,
    Manutencao,
}

/// Níveis de prioridade de suprimentos médicos.
#[derive(Debug, Clone, Copy)]
enum PrioridadeCarga {
    Baixa,
    Media,
    Alta,
}

/// Analisa se a missão oferece risco aceitável.
/// @return true se a missão for arriscada.
fn analisar_risco(prioridade: PrioridadeCarga, clima_ruim: bool) -> bool {
    match (prioridade, clima_ruim) {
        (PrioridadeCarga::Alta, true) => false, // Alta prioridade justifica o risco do clima
        (_, true) => true,                      // Outras prioridades com clima ruim são arriscadas
        _ => false,                             // Clima bom nunca é arriscado
    }
}

/**
 * Processa o relatório final da missão.
 * Toma posse (ownership) da String do log e limpa da memória ao fim.
 */
fn processar_relatorio(log: String) {
    println!("\n\x1b[34m[CENTRAL DE COMANDO]: Arquivando Log de Missão...\x1b[0m");
    println!("DADOS DO LOG: {}", log);
    println!("\x1b[32m[SISTEMA]: Memória do log liberada com segurança.\x1b[0m");
}

fn main() {
    println!("===============================================");
    println!("     SKYRESCUE - CENTRAL DE OPERAÇÕES (SA-01)  ");
    println!("===============================================");

    // 1. Configuração da Missão
    let id_drone = "RESCUE-X01";
    let mut status_atual = StatusDrone::Disponivel;
    let carga = PrioridadeCarga::Alta;
    let clima_adverso = true;

    println!("Drone Identificado: {}", id_drone);
    println!("Status Inicial: {:?}", status_atual);

    // 2. Triagem e Início de Missão
    if status_atual == StatusDrone::Disponivel {
        let eh_arriscado = analisar_risco(carga, clima_adverso);
        
        if eh_arriscado {
            println!("\x1b[31m[BLOQUEIO]: Missão abortada por alto risco climático.\x1b[0m");
        } else {
            println!("\x1b[32m[AUTORIZADO]: Iniciando Missão de Entrega Crítica.\x1b[0m");
            status_atual = StatusDrone::EmMissao;
            
            // 3. Simulação de Log de Missão (Ownership)
            let log_missao = format!("Drone {} completou entrega de prioridade {:?} com sucesso.", id_drone, carga);
            
            // Enviamos o log para a central. O main perde a posse dele aqui.
            processar_relatorio(log_missao);
            
            // Finalizamos a missão
            status_atual = StatusDrone::Disponivel;
        }
    }

    println!("\nStatus Final da Frota: {:?}", status_atual);
    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS (Garantia de Qualidade SA-01)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_risco_clima_bom() {
        assert_eq!(analisar_risco(PrioridadeCarga::Baixa, false), false);
    }

    #[test]
    fn test_risco_clima_ruim_prioridade_baixa() {
        assert_eq!(analisar_risco(PrioridadeCarga::Baixa, true), true);
    }

    #[test]
    fn test_risco_clima_ruim_prioridade_alta() {
        // Prioridade alta ignora o risco do clima
        assert_eq!(analisar_risco(PrioridadeCarga::Alta, true), false);
    }

    #[test]
    fn test_status_drone_transicao() {
        let s = StatusDrone::Disponivel;
        assert_eq!(s, StatusDrone::Disponivel);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-01
    ===============================================================

    1. RUST vs C++ (O grande salto):
       - Diferente da SA-1 em C++, aqui não precisamos nos preocupar 
         com 'delete' para o log de missão. O Ownership fez isso.
       - O compilador garantiu que o StatusDrone fosse comparado
         de forma segura usando o trait 'PartialEq'.

    2. MATRIZ DE DECISÃO COM MATCH:
       - No C++, usaríamos IFs aninhados. No Rust, usamos tuplas no 
         match: `match (prioridade, clima)`. Isso é muito mais 
         legível e menos propenso a erros.

    3. SEGURANÇA DE MEMÓRIA:
       - O log de missão foi gerado dinamicamente com 'format!'. 
         A central de comando tomou a posse e limpou os bytes 
         imediatamente após a exibição.

    4. FORMATO INDUSTRIAL:
       - O uso de crates, README, e testes unitários integrados 
         prepara o aluno para o fluxo de trabalho real em Rust.
    ===============================================================
*/
