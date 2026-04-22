/**
 * @file main.rs
 * @brief SA-01: Sistema de Rastreamento de Drones de Resgate (Refatoração de Elite).
 * 
 * Integração de Lógica, Enums, Pattern Matching e Ownership Tree.
 * 
 * @section MemoryMap Árvore de Posse (Ownership Tree)
 * - `id_drone`: &'static str (Stack reference para binário/Data segment).
 * - `status_atual`: StatusDrone (Stack, Simple Enum).
 * - `carga`: PrioridadeCarga (Stack, Copy trait).
 * - `log_missao`: String (Heap-allocated, Posse transferida para `processar_relatorio`).
 * - `custo_operacional`: u32 (Stack, Guardião Financeiro - centavos inteiros).
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

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
    // Fantasma do CPU: Usamos match por valor pois PrioridadeCarga é Copy (Zero cost)
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
fn processar_relatorio(log: String, custo: u32) {
    println!("\n\x1b[34m[CENTRAL DE COMANDO]: Arquivando Log de Missão...\x1b[0m");
    println!("DADOS DO LOG: {}", log);
    // Guardião Financeiro: Exibindo valores monetários com integridade
    println!("CUSTO DA MISSÃO: R$ {}.{:02}", custo / 100, custo % 100);
    println!("\x1b[32m[SISTEMA]: Memória do log liberada com segurança.\x1b[0m");
}

fn main() {
    println!("===============================================");
    println!("     SKYRESCUE - CENTRAL DE OPERAÇÕES (SA-01)  ");
    println!("     REFATORAÇÃO DE ELITE - FANTASMA DO CPU    ");
    println!("===============================================");

    // 1. Configuração da Missão
    let id_drone = "RESCUE-X01";
    let mut status_atual = StatusDrone::Disponivel;
    let carga = PrioridadeCarga::Alta;
    let clima_adverso = true;
    
    // Guardião Financeiro: Custo em centavos (integridade bancária)
    let custo_base: u32 = 15000; // R$ 150,00

    println!("Drone Identificado: {}", id_drone);
    println!("Status Inicial: {:?}", status_atual);

    // 2. Triagem e Início de Missão
    if status_atual == StatusDrone::Disponivel {
        // Fantasma do CPU: Passagem de 'carga' por valor (Copy) evita indirection
        let eh_arriscado = analisar_risco(carga, clima_adverso);
        
        if eh_arriscado {
            println!("\x1b[31m[BLOQUEIO]: Missão abortada por alto risco climático.\x1b[0m");
        } else {
            println!("\x1b[32m[AUTORIZADO]: Iniciando Missão de Entrega Crítica.\x1b[0m");
            status_atual = StatusDrone::EmMissao;
            println!("Status da Missão: {:?}", status_atual);
            
            // 3. Simulação de Log de Missão (Ownership Tree)
            // Fantasma do CPU: Evitamos .clone() usando format! que cria uma nova String
            let log_missao = format!("Drone {} completou entrega de prioridade {:?} com sucesso.", id_drone, carga);
            
            // Enviamos o log para a central. O main perde a posse dele aqui.
            processar_relatorio(log_missao, custo_base);
            
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
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-01 (ELITE)
    ===============================================================

    1. OWNERSHIP TREE (Árvore de Posse):
       - A String 'log_missao' nasce no main, é movida para 
         'processar_relatorio' e morre lá. O Rust garante zero-leak.

    2. FANTASMA DO CPU (Otimização):
       - Uso estratégico do trait 'Copy' para Enums pequenos.
       - Passagem por valor para tipos primitivos, evitando 
         ponteiros desnecessários no registrador do processador.

    3. GUARDIÃO FINANCEIRO:
       - Implementação de centavos inteiros (u32) para evitar erros 
         de arredondamento de ponto flutuante (IEEE 754) em 
         missões humanitárias pagas.

    4. ASSUNTOS CORRELATOS:
       - Error Handling (Result/Option).
       - Structs e Métodos (impl).
       - Smart Pointers (Box, Rc).
    ===============================================================
*/
