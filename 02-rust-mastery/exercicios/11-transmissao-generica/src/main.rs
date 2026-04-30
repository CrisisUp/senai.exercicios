/**
 * @file main.rs
 * @brief Atividade 11: Transmissão Genérica (Generics e Trait Bounds).
 * 
 * @section MemoryMap
 * - Heap profunda: O uso de String dentro de MensagemVoo implica em alocações na Heap para armazenar o conteúdo textual dinâmico.
 * - Monomorfização: O compilador gera instâncias específicas de transmitir_via_radio para cada tipo T utilizado, garantindo performance de Static Dispatch.
 * - Stack: Dados primitivos como f64 e metadados das structs residem na Stack até serem movidos.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Define o comportamento de objetos que podem ser enviados pelo rádio.
trait Transmissivel {
    fn formatar_pacote(&self) -> String;
}

// -----------------------------------------------------------------------------
// IMPLEMENTAÇÕES
// -----------------------------------------------------------------------------

#[derive(Debug)]
struct MensagemVoo {
    texto: String,
    prioridade: u8,
}

impl Transmissivel for MensagemVoo {
    fn formatar_pacote(&self) -> String {
        format!("[MSG|PRIO:{}]: {}", self.prioridade, self.texto)
    }
}

struct DadosGPS {
    lat: f64,
    lon: f64,
}

impl Transmissivel for DadosGPS {
    fn formatar_pacote(&self) -> String {
        format!("[GPS]: {:.4}, {:.4}", self.lat, self.lon)
    }
}

// -----------------------------------------------------------------------------
// FUNÇÃO GENÉRICA (STATIC DISPATCH)
// -----------------------------------------------------------------------------

/**
 * Transmite qualquer dado que siga o protocolo Transmissivel.
 * O compilador criará versões específicas desta função para cada tipo usado.
 */
fn transmitir_via_radio<T: Transmissivel>(dado: T) {
    println!("\x1b[34m[RÁDIO]:\x1b[0m Transmitindo pacote...");
    let pacote = dado.formatar_pacote();
    println!(">> Conteúdo: {}", pacote);
    println!("\x1b[32m[OK]:\x1b[0m Pacote enviado com sucesso.\n");
}

/**
 * Exemplo usando a sintaxe 'where', recomendada para casos com muitos limites.
 */
fn enviar_multiplos<T>(dado1: T, dado2: T) 
where 
    T: Transmissivel + std::fmt::Debug 
{
    println!("\x1b[33m[LOTE]:\x1b[0m Enviando par de dados...");
    transmitir_via_radio(dado1);
    transmitir_via_radio(dado2);
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - TRANSMISSÃO GENÉRICA           ");
    println!("===============================================");

    // 1. Enviando uma mensagem (String)
    let msg = MensagemVoo {
        texto: String::from("Carga entregue no ponto B"),
        prioridade: 1,
    };
    transmitir_via_radio(msg);

    // 2. Enviando coordenadas GPS (f64)
    let gps = DadosGPS {
        lat: -23.5505,
        lon: -46.6333,
    };
    transmitir_via_radio(gps);

    // 3. Demonstrando que o Ownership foi transferido (Monomorfização)
    // Se tentássemos usar 'msg' aqui, daria erro, pois 'transmitir_via_radio' tomou a posse.
    println!("[INFO]: Dados transmitidos e limpos da memória.");

    // 4. Enviando múltiplos dados do mesmo tipo
    let msg1 = MensagemVoo {
        texto: String::from("Mensagem lote 1"),
        prioridade: 2,
    };
    let msg2 = MensagemVoo {
        texto: String::from("Mensagem lote 2"),
        prioridade: 3,
    };

    enviar_multiplos(msg1, msg2);

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_formatacao_mensagem() {
        let msg = MensagemVoo { texto: "Ola".to_string(), prioridade: 3 };
        assert_eq!(msg.formatar_pacote(), "[MSG|PRIO:3]: Ola");
    }

    #[test]
    fn test_formatacao_gps() {
        let gps = DadosGPS { lat: 1.0, lon: 2.0 };
        assert_eq!(gps.formatar_pacote(), "[GPS]: 1.0000, 2.0000");
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: GENERICS E TRAIT BOUNDS (Fase 2)
    ===============================================================

    1. O QUE SÃO GENERICS?
       - Permitem escrever código abstrato e reutilizável. Em vez de tipos concretos,
         usamos parâmetros de tipo (como 'T').

    2. TRAIT BOUNDS (T: Trait):
       - Garantem que o tipo genérico possua as capacidades necessárias. 
       - O Bound 'T: Transmissivel' assegura que 'formatar_pacote' exista.

    3. MONOMORFIZAÇÃO:
       - Processo onde o compilador substitui tipos genéricos por tipos concretos
         em tempo de compilação, gerando código otimizado (Static Dispatch).

    4. FANTASMA DO CPU (OTIMIZAÇÃO):
       - Evitamos o uso de 'dyn Trait' (Dynamic Dispatch) quando a performance é
         crítica, pois ele impede o inline e adiciona custos de vtable.
    ===============================================================

    ASSUNTOS CORRELATOS:
    - Zero-Cost Abstractions em Rust.
    - Especialização de Traits (Nightly feature).
    - Blanked Implementations (implementar trait para qualquer tipo que siga outro trait).
    - PhantomData para marcação de tipos em generics complexos.
*/
