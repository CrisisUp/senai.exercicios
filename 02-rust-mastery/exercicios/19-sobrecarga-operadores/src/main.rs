const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 19: Gestão de Energia (Sobrecarga de Operadores).
 *
 * @section Aprendizado
 * Traits de Operadores (Add, Sub), std::fmt::Display.
 *
 * @section MemoryMap
 * - A sobrecarga de operadores em Rust é compilada em chamadas de função direta.
 * - Não há overhead de runtime comparado a chamar um método como .add().
 * - A semântica de Move/Copy continua sendo aplicada rigorosamente.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::fmt;
use std::io::{self, Write};
use std::ops::{Add, Sub};

/// @section Fantasma do CPU: Performance
/// A beleza do Rust é que o açúcar sintático do '+' é resolvido em tempo de compilação.
/// O 'Fantasma do CPU' não vê diferença entre `a + b` e o código mais verboso,
/// pois o compilador inlina essas chamadas de trait agressivamente.

/// Representa um pack de bateria modular.
#[derive(Debug, Copy, Clone, PartialEq)]
struct PackBateria {
    capacidade_mah: f64,
}

// -----------------------------------------------------------------------------
// SOBRECARGA: OPERADOR + (Add)
// -----------------------------------------------------------------------------
impl Add for PackBateria {
    type Output = Self; // Define o tipo de retorno da operação

    fn add(self, other: Self) -> Self {
        Self {
            capacidade_mah: self.capacidade_mah + other.capacidade_mah,
        }
    }
}

// -----------------------------------------------------------------------------
// SOBRECARGA: OPERADOR - (Sub)
// -----------------------------------------------------------------------------
impl Sub for PackBateria {
    type Output = Self;

    fn sub(self, other: Self) -> Self {
        let nova_cap = if self.capacidade_mah > other.capacidade_mah {
            self.capacidade_mah - other.capacidade_mah
        } else {
            0.0 // Bateria não pode ser negativa
        };

        Self {
            capacidade_mah: nova_cap,
        }
    }
}

// -----------------------------------------------------------------------------
// INTERFACE VISUAL: Display
// -----------------------------------------------------------------------------
impl fmt::Display for PackBateria {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "[{} mAh]", self.capacidade_mah)
    }
}

fn pedir_valor(label: &str) -> f64 {
    print!("{}", label);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().parse().unwrap_or(0.0)
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - GESTOR DE ENERGIA MODULAR      ");
    println!("===============================================");

    // 1. Entrada do Usuário
    println!("Configurando Células de Energia:");
    let cap1 = pedir_valor("Capacidade do Pack A (mAh): ");
    let cap2 = pedir_valor("Capacidade do Pack B (mAh): ");

    let pack_a = PackBateria {
        capacidade_mah: cap1,
    };
    let pack_b = PackBateria {
        capacidade_mah: cap2,
    };

    println!("\nRecursos Disponíveis:");
    println!("  Pack A: {}", pack_a);
    println!("  Pack B: {}", pack_b);

    // 2. USO DA SOBRECARGA (+)
    // Graças ao Trait 'Add', podemos usar o símbolo '+' naturalmente!
    let total = pack_a + pack_b;
    println!("\x1b[32m[COMBINADO]:\x1b[0m Capacidade Total: {}", total);

    // 3. USO DA SOBRECARGA (-)
    println!("\nSimulando consumo de voo...");
    let consumo = pedir_valor("Quantidade consumida (mAh): ");
    let pack_consumo = PackBateria {
        capacidade_mah: consumo,
    };

    let restante = total - pack_consumo;
    println!("\x1b[33m[STATUS]:\x1b[0m Energia Restante: {}", restante);

    if restante.capacidade_mah == 0.0 {
        println!("\x1b[31m[ALERTA]: Energia esgotada!\x1b[0m");
    }

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_soma_baterias() {
        let p1 = PackBateria {
            capacidade_mah: 1000.0,
        };
        let p2 = PackBateria {
            capacidade_mah: 500.0,
        };
        let res = p1 + p2;
        assert_eq!(res.capacidade_mah, 1500.0);
    }

    #[test]
    fn test_subtracao_baterias() {
        let p1 = PackBateria {
            capacidade_mah: 1000.0,
        };
        let p2 = PackBateria {
            capacidade_mah: 300.0,
        };
        let res = p1 - p2;
        assert_eq!(res.capacidade_mah, 700.0);
    }

    #[test]
    fn test_bateria_nao_negativa() {
        let p1 = PackBateria {
            capacidade_mah: 100.0,
        };
        let p2 = PackBateria {
            capacidade_mah: 200.0,
        };
        let res = p1 - p2;
        assert_eq!(res.capacidade_mah, 0.0);
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: SOBRECARGA DE OPERADORES EM RUST (FASE ELITE)
    ===============================================================

    1. TRAITS std::ops:
       - No Rust, os operadores são apenas "açúcar sintático" para
         chamadas de métodos de Traits da biblioteca padrão.
       - Implementar 'Add' permite usar '+', 'Sub' permite '-',
         'Mul' permite '*', etc.

    2. SEGURANÇA E CLAREZA:
       - Diferente de algumas linguagens onde você pode fazer um
         operador '+' fazer qualquer coisa, em Rust a estrutura
         exige que você defina o tipo de retorno (type Output).
       - Isso evita ambiguidades e garante que a semântica seja
         preservada pelo sistema de tipos.

    3. ZERO OVERHEAD (MemoryMap):
       - O compilador Rust inlina essas chamadas de Traits. Usar
         'pack_a + pack_b' tem exatamente o mesmo desempenho que
         chamar uma função inline manual.

    4. DISPLAY vs DEBUG:
       - 'Debug' ({:?}) é para o programador (gerado via derive).
       - 'Display' ({}) é para o usuário final, e deve ser
         implementado manualmente para controle total da formatação.

    5. REFATORAÇÃO DE ELITE:
       - Um código de elite não apenas "funciona", ele é expressivo.
       - A sobrecarga de operadores deve ser usada apenas quando a
         operação matemática é intuitiva para o domínio de negócio.
    ===============================================================
*/


