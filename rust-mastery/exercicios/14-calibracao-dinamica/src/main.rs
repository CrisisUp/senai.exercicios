use std::cell::RefCell; // Para mutabilidade interior
use std::io::{self, Write};
/**
 * @file main.rs
 * @brief Atividade 14: Calibração Dinâmica (RefCell e Interatividade).
 *
 * Aprendizados: RefCell<T>, borrow(), borrow_mut(), Mutabilidade Interior.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::rc::Rc;

#[derive(Debug)]
struct SensorCalibragem {
    id: String,
    fator_correcao: f64,
}

impl SensorCalibragem {
    fn new(id: &str) -> Self {
        Self {
            id: id.to_string(),
            fator_correcao: 1.0, // Inicialmente sem correção
        }
    }
}

/**
 * Simula um sistema que apenas LÊ os dados.
 * Recebe um Rc imutável, mas consegue "espiar" dentro do RefCell.
 */
fn sistema_monitoramento(sensor: Rc<RefCell<SensorCalibragem>>) {
    // .borrow() cria uma referência imutável temporária.
    let s = sensor.borrow();
    println!(
        "\x1b[36m[MONITOR]:\x1b[0m Sensor {} lendo com fator: {:.2}",
        s.id, s.fator_correcao
    );
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - CALIBRAÇÃO DINÂMICA            ");
    println!("===============================================");

    // 1. Criando o sensor com Múltipla Propriedade (Rc) e Mutabilidade Interior (RefCell)
    let sensor_central = Rc::new(RefCell::new(SensorCalibragem::new("S-CORE-01")));

    // Criando clones para diferentes sistemas
    let sistema_a = Rc::clone(&sensor_central);
    let sistema_b = Rc::clone(&sensor_central);

    // 2. Status Inicial
    println!("Status Inicial:");
    sistema_monitoramento(Rc::clone(&sistema_a));

    // 3. Interação: Solicitar novo fator de calibração ao usuário
    print!("\nDigite o novo valor de calibração (ex: 1.25): ");
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Falha ao ler entrada");

    let novo_fator: f64 = input.trim().parse().unwrap_or(1.0);

    // 4. ALTERAÇÃO EM RUNTIME (borrow_mut)
    println!("\x1b[33m[SISTEMA]: Aplicando calibração...\x1b[0m");
    {
        // .borrow_mut() cria uma referência mutável exclusiva.
        // O escopo {} garante que a trava mutável seja liberada rapidamente.
        let mut s = sensor_central.borrow_mut();
        s.fator_correcao = novo_fator;
    }

    // 5. Provando que todos os sistemas enxergaram a mudança
    println!("\nVerificando sincronização dos sistemas:");
    sistema_monitoramento(sistema_a);
    sistema_monitoramento(sistema_b);

    println!(
        "\n\x1b[32m[SUCESSO]:\x1b[0m Todos os sistemas sincronizados com o novo fator de {:.2}.",
        novo_fator
    );
    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_mutabilidade_interior() {
        let sensor = Rc::new(RefCell::new(SensorCalibragem::new("T1")));

        {
            let mut s = sensor.borrow_mut();
            s.fator_correcao = 2.0;
        }

        assert_eq!(sensor.borrow().fator_correcao, 2.0);
    }

    #[test]
    #[should_panic] // Este teste prova que o RefCell protege contra concorrência de acesso
    fn test_protecao_borrow_checker_runtime() {
        let sensor = Rc::new(RefCell::new(SensorCalibragem::new("T1")));

        let _leitura = sensor.borrow();
        let _escrita = sensor.borrow_mut(); // Isso deve causar PANIC! (já existe um leitor ativo)
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: REFCELL E MUTABILIDADE INTERIOR
    ===============================================================

    1. O QUE É MUTABILIDADE INTERIOR?
       - É a habilidade de mutar um dado mesmo quando você tem apenas
         uma referência imutável (&) para o container dele.

    2. REFCELL<T>:
       - Ele move as regras do "Borrow Checker" do tempo de compilação
         para o tempo de execução.
       - Se você tentar dar .borrow_mut() enquanto alguém está dando
         .borrow(), o programa trava (panic) em vez de corromper dados.

    3. QUANDO USAR?
       - Quando você usa Rc<T> (que é imutável) mas precisa que o dado
         dentro dele mude conforme a necessidade do sistema.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende que o Rust oferece "válvulas de escape" seguras.
         Você pode burlar regras rígidas, mas ainda terá a proteção
         do sistema contra acessos simultâneos inválidos.
    ===============================================================
*/
