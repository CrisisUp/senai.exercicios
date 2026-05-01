const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 10: Protocolos de Hardware (Traits e Interfaces).
 * 
 * @section MemoryMap
 * - **V-Tables (Virtual Tables):** Ao usar `dyn Dispositivo`, o Rust utiliza uma vtable para resolver os métodos em tempo de execução.
 * - **Heap Allocation:** O uso de `Box<dyn Dispositivo>` coloca o objeto na Heap, pois o tamanho de diferentes implementações de Trait pode variar.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Define o contrato básico para qualquer hardware do drone.
trait Dispositivo {
    fn status(&self) -> String;
    fn reiniciar(&mut self);
}

// -----------------------------------------------------------------------------
// IMPLEMENTAÇÕES DE HARDWARE
// -----------------------------------------------------------------------------

struct SensorGPS {
    satelites: u8,
    ativo: bool,
}

impl Dispositivo for SensorGPS {
    fn status(&self) -> String {
        if self.ativo {
            format!("[GPS]: Ativo ({} satélites detectados)", self.satelites)
        } else {
            String::from("[GPS]: Inativo")
        }
    }

    fn reiniciar(&mut self) {
        println!("\x1b[33m[SISTEMA]:\x1b[0m Reiniciando módulo GPS...");
        self.ativo = true;
    }
}

struct Motor {
    rpm: u32,
    temperatura: f32,
}

impl Dispositivo for Motor {
    fn status(&self) -> String {
        format!("[MOTOR]: {} RPM | Temp: {:.1}°C", self.rpm, self.temperatura)
    }

    fn reiniciar(&mut self) {
        println!("\x1b[33m[SISTEMA]:\x1b[0m Calibrando motores...");
        self.rpm = 0;
    }
}

// -----------------------------------------------------------------------------
// FUNÇÃO DE DIAGNÓSTICO (DYNAMIC DISPATCH)
// -----------------------------------------------------------------------------

/**
 * Executa o diagnóstico de uma lista de dispositivos variados.
 * Usa referências constantes (&) - Fantasma do CPU: Evita cópias desnecessárias.
 */
fn diagnostico_geral(dispositivos: &Vec<Box<dyn Dispositivo>>) {
    println!("\n\x1b[36m--- INICIANDO DIAGNÓSTICO DE HARDWARE ---\x1b[0m");
    for (i, dispositivo) in dispositivos.iter().enumerate() {
        println!("Componente {}: {}", i + 1, dispositivo.status());
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - GESTÃO DE HARDWARE (TRAITS)    ");
    println!("===============================================");

    // 1. Criando a coleção de dispositivos (Polimorfismo com Box)
    let mut hardware_drone: Vec<Box<dyn Dispositivo>> = Vec::new();

    // Fantasma do CPU: Referências constantes seriam usadas se não precisássemos de Ownership no Vec
    hardware_drone.push(Box::new(SensorGPS { satelites: 8, ativo: true }));
    hardware_drone.push(Box::new(Motor { rpm: 12000, temperatura: 45.5 }));
    hardware_drone.push(Box::new(SensorGPS { satelites: 0, ativo: false }));

    // 2. Executando diagnóstico
    diagnostico_geral(&hardware_drone);

    // 3. Simulando reinicialização crítica
    println!("\n\x1b[31m[ALERTA]:\x1b[0m Falha detectada. Reiniciando todos os componentes...");
    for dispositivo in &mut hardware_drone {
        dispositivo.reiniciar();
    }

    // 4. Diagnóstico pós-reparo
    diagnostico_geral(&hardware_drone);

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_gps_status() {
        let gps = SensorGPS { satelites: 5, ativo: true };
        assert!(gps.status().contains("5 satélites"));
    }

    #[test]
    fn test_motor_reiniciar() {
        let mut motor = Motor { rpm: 5000, temperatura: 40.0 };
        motor.reiniciar();
        assert_eq!(motor.rpm, 0);
    }

    #[test]
    fn test_polimorfismo() {
        let mut list: Vec<Box<dyn Dispositivo>> = Vec::new();
        list.push(Box::new(SensorGPS { satelites: 1, ativo: true }));
        list.push(Box::new(Motor { rpm: 100, temperatura: 20.0 }));
        assert_eq!(list.len(), 2);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TRAITS (INTERFACES RUST)
    ===============================================================

    1. O QUE SÃO TRAITS?
       - São contratos que definem o comportamento de um tipo.

    2. DYNAMIC DISPATCH (dyn):
       - Permite que o programa escolha qual método executar em tempo 
         de execução através de uma vtable.

    3. BOX E HEAP:
       - Diferentes structs têm tamanhos diferentes. Para colocá-las em 
         um Vec, usamos Box (ponteiro inteligente) para que todos os 
         elementos tenham o mesmo tamanho de ponteiro na Stack.

    4. ASSUNTOS CORRELATOS:
       - Trait Objects Safety: Por que nem toda Trait pode ser usada com 'dyn'.
       - Associated Types: Uma forma avançada de generics dentro de traits.
       - Blanket Implementations: Implementar uma trait para qualquer tipo 
         que já implemente outra trait.
    ===============================================================
*/

