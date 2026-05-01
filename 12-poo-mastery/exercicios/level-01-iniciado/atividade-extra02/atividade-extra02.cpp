/**
 * @file atividade-extra02.cpp
 * @brief Implementação de Construtores e Destrutores (O Ciclo Vital)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: 'drone1' alocado na stack. 'drone2' alocado em bloco anônimo (stack).
 * - Heap: Alocação dinâmica de strings internamente pela std::string.
 */

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

class Drone {
public:
    std::string modelo;
    int bateria;

    /**
     * @brief Construtor parametrizado.
     * @param modelo Nome do modelo do drone.
     * @param bateria Percentual de bateria inicial.
     */
    Drone(std::string modelo, int bateria) {
        this->modelo = modelo; // Uso do this para diferenciar atributo de parâmetro
        this->bateria = bateria;
        std::cout << GREEN << "[NASCIMENTO] Drone " << BOLD << this->modelo << RESET << " inicializado no sistema." << std::endl;
    }

    /**
     * @brief Destrutor.
     * Chamado automaticamente quando o objeto sai de escopo.
     */
    ~Drone() {
        std::cout << RED << "[MORTE] Drone " << BOLD << modelo << RESET << " DESATIVADO (Limpando hangar...)" << std::endl;
    }

    void verStatus() {
        std::cout << "Status: " << modelo << " | Bateria: " << bateria << "%" << std::endl;
    }
};

int main() {
    std::cout << BOLD << YELLOW << "=== SKYCARGO NEXUS - CICLO DE VIDA ===" << RESET << std::endl << std::endl;

    // Criando objeto 1 no escopo principal
    Drone drone1("Vigia-01", 100);
    drone1.verStatus();

    std::cout << std::endl << "[SISTEMA] Entrando em bloco de teste de escopo..." << std::endl;
    {
        // Criando objeto 2 em escopo restrito
        Drone drone2("Explorador-X", 50);
        drone2.verStatus();
        std::cout << "[SISTEMA] Saindo do bloco de teste..." << std::endl;
    } // drone2 deve ser destruído aqui

    std::cout << std::endl << "[SISTEMA] Drone 1 ainda está vivo no main." << std::endl;
    drone1.verStatus();

    std::cout << std::endl << YELLOW << "[SISTEMA] Finalizando execução..." << RESET << std::endl;

    return 0;
} // drone1 será destruído aqui

/**
 * @section ResumoTeórico
 * Construtores inicializam o estado do objeto no momento da criação.
 * Destrutores garantem a limpeza de recursos quando o objeto deixa de existir.
 * O escopo (definido por {}) determina o tempo de vida de objetos alocados na stack.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
