/**
 * @file main.cpp
 * @brief Gestão de Recursos Compartilhados com std::shared_ptr e std::weak_ptr.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - std::shared_ptr (Stack): Contém ponteiro para o objeto e para um "Control Block" na Heap.
 * - Control Block (Heap): Armazena a contagem de referências (strong e weak).
 * - Objeto Sensor (Heap): Destruído quando o 'strong count' atinge zero.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"

class Sensor {
private:
    std::string id;
public:
    Sensor(std::string name) : id(name) {
        std::cout << GREEN << "[Sensor] " << id << " inicializado na central." << RESET << std::endl;
    }
    ~Sensor() {
        std::cout << RED << "[Sensor] " << id << " desativado e removido da memória." << RESET << std::endl;
    }
    void lerDados() {
        std::cout << CYAN << "[Leitura] " << id << ": Capturando telemetria..." << RESET << std::endl;
    }
};

void operadorNexus(std::shared_ptr<Sensor> s, std::string nomeOp) {
    std::cout << YELLOW << "[Operador " << nomeOp << "] Conectado ao sensor. Referências atuais: " 
              << s.use_count() << RESET << std::endl;
    s->lerDados();
}

int main() {
    std::cout << "--- SkyCargo Nexus: Monitoramento de Recursos Compartilhados ---" << std::endl;

    // 1. Criando o recurso compartilhado
    std::shared_ptr<Sensor> sensorCentral = std::make_shared<Sensor>("GPS-Global-01");
    std::cout << "Contagem inicial: " << sensorCentral.use_count() << std::endl;

    {
        std::cout << "\n--- Iniciando Turno de Operação ---" << std::endl;
        std::shared_ptr<Sensor> op1 = sensorCentral;
        std::shared_ptr<Sensor> op2 = sensorCentral;

        std::cout << MAGENTA << "Posse compartilhada por 3 (Central + Op1 + Op2). Contagem: " 
                  << sensorCentral.use_count() << RESET << std::endl;

        operadorNexus(sensorCentral, "Silva");
    } // op1 e op2 saem de escopo aqui

    std::cout << "\n--- Fim do Turno ---" << std::endl;
    std::cout << "Contagem após saída de operadores: " << sensorCentral.use_count() << std::endl;

    // 2. Demonstração de weak_ptr (Observador)
    std::cout << "\n--- Configurando Observador Passivo (weak_ptr) ---" << std::endl;
    std::weak_ptr<Sensor> observador = sensorCentral;
    std::cout << "Contagem com weak_ptr (não incrementa): " << sensorCentral.use_count() << std::endl;

    if (auto obsLock = observador.lock()) {
        std::cout << GREEN << "[Observador] Recurso ainda existe. Acessando..." << RESET << std::endl;
        obsLock->lerDados();
    }

    std::cout << "\n--- Desativando Central ---" << std::endl;
    sensorCentral.reset(); // Força a liberação (ou apenas deixar sair de escopo)

    if (observador.expired()) {
        std::cout << RED << "[Observador] O sensor foi destruído. Acesso impossível." << RESET << std::endl;
    }

    std::cout << "\n--- Sistema Encerrado com Segurança ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * 1. std::shared_ptr: Permite múltiplos donos. Usa um 'Control Block' para contar referências.
     * 2. std::make_shared: Mais eficiente, pois aloca o objeto e o control block em um único bloco de memória.
     * 3. std::weak_ptr: Quebra ciclos de referência e permite observar um objeto sem mantê-lo vivo.
     */

    return 0;
}
