#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief SA-04: Central de Comando e Controle Inteligente (Refatoração de Elite).
 * 
 * Integração robusta de Traits, Generics e Dynamic Dispatch para monitoramento de infraestrutura crítica.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 * 
 * @section MemoryMap Árvore de Ownership e Gerenciamento de Memória:
 * - central (Vec<Box<dyn Hardware>>): [STACK] Ponteiro p/ [HEAP] Vetor de [STACK] Fat Pointers p/ [HEAP] Objetos.
 * - DroneVoo/BaseCarregamento: [HEAP] Alocados via Box, cada um possui sua própria string de ID (Heap).
 * - falhas (Vec<String>): [STACK] Ponteiro p/ [HEAP] Novo vetor com cópias das strings de identificação.
 * 
 * @section FantasmadoCPU Fantasma do CPU (Performance e Segurança):
 * - Zero-copy: O uso de iteradores (.iter()) evita a duplicação dos objetos Hardware na memória.
 * - Referências: 'transmitir_emergencia(&T)' utiliza referências para passar o controle sem mover a posse.
 * - Lifetimes: O tempo de vida das referências dentro do loop é limitado ao escopo do loop, garantido pelo compilador.
 */

/// Define o contrato para qualquer hardware monitorado pela central.
trait Hardware {
    fn identificador(&self) -> String;
    fn analisar_seguranca(&self) -> Result<(), String>;
}

// -----------------------------------------------------------------------------
// HARDWARE: DRONE DE VOO
// -----------------------------------------------------------------------------
struct DroneVoo {
    id: String,
    bateria: f64,
}

impl Hardware for DroneVoo {
    fn identificador(&self) -> String {
        format!("DRONE:{}", self.id)
    }

    fn analisar_seguranca(&self) -> Result<(), String> {
        if self.bateria < 15.0 {
            Err(format!("Bateria crítica: {:.1}%", self.bateria))
        } else {
            Ok(())
        }
    }
}

// -----------------------------------------------------------------------------
// HARDWARE: ESTAÇÃO DE CARREGAMENTO
// -----------------------------------------------------------------------------
struct BaseCarregamento {
    setor: String,
    em_curto: bool,
}

impl Hardware for BaseCarregamento {
    fn identificador(&self) -> String {
        format!("BASE:{}", self.setor)
    }

    fn analisar_seguranca(&self) -> Result<(), String> {
        if self.em_curto {
            Err(String::from("Falha elétrica detectada (Curto-circuito)!"))
        } else {
            Ok(())
        }
    }
}

// -----------------------------------------------------------------------------
// FUNÇÃO GENÉRICA COM TRAIT BOUND
// -----------------------------------------------------------------------------
/**
 * Simula a transmissão de um alerta via rádio de alta potência.
 * O compilador gera código estático eficiente para cada tipo de Hardware.
 */
fn transmitir_emergencia<T: Hardware + ?Sized>(dispositivo: &T) {
    println!("\x1b[31m[ALERTA DE RÁDIO]:\x1b[0m Transmissão prioritária de {}", dispositivo.identificador());
    if let Err(msg) = dispositivo.analisar_seguranca() {
        println!(">> FALHA: {}", msg);
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - COMANDO CENTRAL (SA-04)        ");
    println!("===============================================");

    // 1. Criando a lista heterogênea de hardware (Dynamic Dispatch)
    // Box permite que tipos diferentes (Drones e Bases) vivam no mesmo vetor.
    let central: Vec<Box<dyn Hardware>> = vec![
        Box::new(DroneVoo { id: String::from("X-01"), bateria: 85.0 }),
        Box::new(DroneVoo { id: String::from("X-02"), bateria: 12.0 }), // Erro
        Box::new(BaseCarregamento { setor: String::from("HANGAR-A"), em_curto: false }),
        Box::new(BaseCarregamento { setor: String::from("HANGAR-B"), em_curto: true }), // Erro
    ];

    println!("Total de dispositivos monitorados: {}", central.len());

    // 2. Processamento Inteligente com Iteradores e Closures
    // Objetivo: Filtrar quem está com problema e extrair apenas os IDs para a manutenção.
    println!("\nAnalisando segurança da infraestrutura...");
    
    let falhas: Vec<String> = central.iter()
        .filter(|h| h.analisar_seguranca().is_err()) // Filtra apenas falhas
        .map(|h| h.identificador())                   // Transforma em String de ID
        .collect();

    if falhas.is_empty() {
        println!("\x1b[32m[STATUS]: Toda a infraestrutura está operando normalmente.\x1b[0m");
    } else {
        println!("\x1b[31m[CRÍTICO]: {} falhas encontradas!\x1b[0m", falhas.len());
        println!("Lista de envio para Manutenção:");
        for id in &falhas {
            println!("  - {}", id);
        }

        // 3. Demonstrando a transmissão genérica para o primeiro erro encontrado
        println!("\nAcionando canal de emergência para a primeira falha...");
        
        // Buscamos o primeiro objeto no vetor central que tenha falha
        if let Some(primeiro_erro) = central.iter().find(|h| h.analisar_seguranca().is_err()) {
            // Chamada da função genérica
            // Nota: Como 'primeiro_erro' é &Box<dyn Hardware>, o Rust faz a coerção automática.
            transmitir_emergencia(primeiro_erro.as_ref());
        }
    }

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS (Garantia de Qualidade SA-04)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_seguranca_drone_ok() {
        let d = DroneVoo { id: "1".to_string(), bateria: 50.0 };
        assert!(d.analisar_seguranca().is_ok());
    }

    #[test]
    fn test_seguranca_drone_erro() {
        let d = DroneVoo { id: "1".to_string(), bateria: 5.0 };
        assert!(d.analisar_seguranca().is_err());
    }

    #[test]
    fn test_seguranca_base_erro() {
        let b = BaseCarregamento { setor: "A".to_string(), em_curto: true };
        assert!(b.analisar_seguranca().is_err());
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-04 (REFATORAÇÃO DE ELITE)
    ===============================================================

    1. TRAITS E POLIMORFISMO:
       - O SA-04 prova que o aluno consegue arquitetar sistemas que 
         unem tipos distintos através de comportamentos comuns.

    2. DYNAMIC vs STATIC DISPATCH:
       - Vimos os dois mundos: 'Box<dyn Hardware>' (Dynamic) para a 
         lista da central e 'transmitir_emergencia<T>' (Static) 
         para eficiência máxima na transmissão de rádio.

    3. PIPELINES DE DADOS:
       - O uso de '.iter().filter().map().collect()' demonstra a 
         superioridade do Rust no processamento de dados seguro e 
         conciso.

    4. EVOLUÇÃO DO NÍVEL 22:
       - Este projeto encerra o nível 22, consolidando o aluno como 
         um desenvolvedor capaz de criar sistemas extensíveis e 
         prontos para a escala industrial.

    ASSUNTOS CORRELATOS PARA PESQUISA:
    - VTables (Como o Rust gerencia dynamic dispatch por baixo dos panos).
    - Trait Coercion (Como referências a objetos são transformadas).
    - Monomorfização (O processo de geração de código para generics).
    ===============================================================
*/

