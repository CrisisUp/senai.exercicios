/**
 * @file main.rs
 * @brief Atividade 11: Transmissão Genérica (Generics e Trait Bounds).
 * 
 * Aprendizados: Generics <T>, Trait Bounds, Clausula where, Monomorfização.
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
    RESUMO TEÓRICO: GENERICS E TRAIT BOUNDS
    ===============================================================

    1. O QUE SÃO GENERICS?
       - Permitem escrever código abstrato. Em vez de 'int' ou 'struct', 
         usamos 'T'.

    2. TRAIT BOUNDS (T: Trait):
       - Generics puros não podem fazer nada. Se você tem um 'T', 
         não sabe se ele pode ser somado ou impresso. 
       - O Bound 'T: Transmissivel' garante que o compilador só 
         deixe passar tipos que tenham o método 'formatar_pacote'.

    3. MONOMORFIZAÇÃO (A mágica do Rust):
       - O Rust não usa polimorfismo de runtime por padrão para 
         generics. Ele gera o código para cada tipo em tempo de 
         compilação. 
       - Resultado: O código genérico é TÃO RÁPIDO quanto se você 
         tivesse escrito funções separadas para cada tipo.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a criar ferramentas reutilizáveis e 
         percebe como o Rust une a flexibilidade das linguagens 
         dinâmicas com a performance do C++.
    ===============================================================
*/
