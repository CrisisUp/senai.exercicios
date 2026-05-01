const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 07: Controle de Motor Hidráulico (Structs e Métodos).
 * 
 * Aprendizados: Structs, blocos impl, self, &mut self, Encapsulamento.
 * 
 * @section MemoryMap
 * - **Ownership**: O 'main' possui o motor (motor_alfa).
 * - **Borrowing**: Os métodos 'status' e 'ajustar_pressao' pegam emprestado o motor.
 * - **Stack vs Heap**: A struct 'MotorHidraulico' vive na stack; referências (&str) apontam para a memória estática.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Representa um motor de drone de carga.
/// 'Fantasma do CPU': Uso de referências (&str) para evitar alocações desnecessárias na heap.
struct MotorHidraulico<'a> {
    id: u32,
    modelo: &'a str,
    ligado: bool,
    pressao_psi: f64,
}

impl<'a> MotorHidraulico<'a> {
    /**
     * Função Associada (Construtor).
     * Não recebe 'self', pois serve para criar o objeto.
     */
    fn new(id: u32, modelo: &'a str) -> Self {
        println!("\x1b[32m[MOTOR {} - {}]: Instalado com sucesso.\x1b[0m", id, modelo);
        Self {
            id,
            modelo,
            ligado: false,
            pressao_psi: 0.0,
        }
    }

    /// Liga o motor.
    fn ligar(&mut self) {
        self.ligado = true;
        println!("[MOTOR {}]: Motor LIGADO.", self.id);
    }

    /// Desliga o motor e zera a pressão.
    fn desligar(&mut self) {
        self.ligado = false;
        self.pressao_psi = 0.0;
        println!("[MOTOR {}]: Motor DESLIGADO.", self.id);
    }

    /**
     * Ajusta a pressão operacional com regras de segurança.
     * @return true se o ajuste foi aceito.
     */
    fn ajustar_pressao(&mut self, psi: f64) -> bool {
        if !self.ligado {
            println!("\x1b[31m[ERRO]: Não é possível ajustar pressão com motor desligado!\x1b[0m");
            return false;
        }

        if psi < 0.0 || psi > 5000.0 {
            println!("\x1b[31m[ALERTA]: Pressão de {:.1} PSI fora da margem de segurança!\x1b[0m", psi);
            false
        } else {
            self.pressao_psi = psi;
            println!("[MOTOR {}]: Pressão ajustada para {:.1} PSI.", self.id, psi);
            true
        }
    }

    /// Exibe o status atual (Referência de Leitura).
    fn status(&self) {
        let estado = if self.ligado { "LIGADO" } else { "DESLIGADO" };
        println!("-----------------------------------------------");
        println!("MOTOR: {} ({}) | ESTADO: {} | PRESSÃO: {:.1} PSI", 
                 self.id, self.modelo, estado, self.pressao_psi);
        println!("-----------------------------------------------");
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE PROPULSÃO           ");
    println!("===============================================");

    // 1. Instanciando o motor (Passando referência &str)
    let mut motor_alfa = MotorHidraulico::new(101, "HYDRA-MAX-500");

    // 2. Testando segurança (tentando ajustar pressão desligado)
    motor_alfa.ajustar_pressao(1500.0);
    motor_alfa.status();

    // 3. Operação normal
    motor_alfa.ligar();
    motor_alfa.ajustar_pressao(2200.0);
    motor_alfa.status();

    // 4. Testando limite de segurança
    motor_alfa.ajustar_pressao(6000.0);
    
    // 5. Encerrando
    motor_alfa.desligar();

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_motor_inicializacao() {
        let m = MotorHidraulico::new(1, "TEST");
        assert_eq!(m.ligado, false);
        assert_eq!(m.pressao_psi, 0.0);
    }

    #[test]
    fn test_motor_ligar() {
        let mut m = MotorHidraulico::new(1, "TEST");
        m.ligar();
        assert_eq!(m.ligado, true);
    }

    #[test]
    fn test_pressao_segura() {
        let mut m = MotorHidraulico::new(1, "TEST");
        m.ligar();
        let ok = m.ajustar_pressao(2500.0);
        assert!(ok);
        assert_eq!(m.pressao_psi, 2500.0);
    }

    #[test]
    fn test_pressao_insegura() {
        let mut m = MotorHidraulico::new(1, "TEST");
        m.ligar();
        let ok = m.ajustar_pressao(9999.0);
        assert!(!ok);
        assert_eq!(m.pressao_psi, 0.0); // Não deve ter mudado
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: STRUCTS E MÉTODOS
    ===============================================================

    1. ENCAPSULAMENTO DE COMPORTAMENTO:
       - No Rust, os dados (struct) e o comportamento (impl) são 
         definidos em blocos separados.
       - 'Fantasma do CPU': Ao usar referências (&str) em structs, 
         otimizamos a memória evitando alocações na Heap para textos 
         estáticos (literais).

    2. O CONCEITO DE SELF:
       - 'self': Toma a posse (Consome o objeto).
       - '&self': Empréstimo Imutável (Leitura).
       - '&mut self': Empréstimo Mutável (Escrita).

    3. LIFETIMES (VIVACIDADE):
       - O uso de <'a> indica que a struct não pode viver mais que 
         a referência que ela carrega (modelo).

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a modelar objetos com segurança de memória 
         e performance de CPU integradas desde o design da struct.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Lifetimes em Rust (O marcador <'a>).
    - String vs &str (Heap vs Static).
    - Padrão 'Newtype' para tipos fortes.
    - Traits de conversão: From e Into.
    ===============================================================
*/

