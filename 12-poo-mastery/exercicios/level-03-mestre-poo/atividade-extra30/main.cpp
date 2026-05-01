#define ANSI_RESET "\033[0m"
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

/**
 * @file main.cpp
 * @brief Implementação da Atividade 30 - Design Pattern: Singleton.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - FleetManager Instance (Static Data): Alocada uma única vez no início ou no primeiro uso.
 * - getFleet() (Heap): Retorna referência para os dados compartilhados.
 */

// --- Design Pattern: Singleton ---
class FleetManager {
private:
    std::vector<std::string> frotaAtiva;

    // 1. Construtor Privado: Impede instancimento externo
    FleetManager() {
        std::cout << "[SISTEMA] FleetManager inicializado. Ponto de acesso único estabelecido." << std::endl;
    }

    // Desativar cópia e atribuição (Fundamental para Singleton)
    FleetManager(const FleetManager&) = delete;
    FleetManager& operator=(const FleetManager&) = delete;

public:
    // 2. Ponto de Acesso Global (Meyers' Singleton - C++11 em diante é Thread-Safe por padrão)
    static FleetManager& getInstance() {
        static FleetManager instance; // Criada na primeira chamada
        return instance;
    }

    void registrarDrone(std::string modelo) {
        frotaAtiva.push_back(modelo);
        std::cout << "[Fleet] Unidade '" << modelo << "' registrada no radar global." << std::endl;
    }

    void listarFrota() const {
        std::cout << "\n--- Relatório de Frota Ativa ---" << std::endl;
        for (const auto& d : frotaAtiva) {
            std::cout << " > " << d << std::endl;
        }
    }
};

// Simulando uma função em outra parte do sistema
void moduloLogistica() {
    std::cout << "\n[Logística] Acessando gerenciador de frota..." << std::endl;
    FleetManager::getInstance().registrarDrone("Logistics-Unit-04");
}

int main() {
    std::cout << "--- SkyCargo Nexus: Gestão Soberana via Singleton ---" << std::endl;

    // 3. Tentativa de instanciar diretamente (ERRO DE COMPILAÇÃO se descomentado)
    // FleetManager meuManager; // Erro: 'FleetManager::FleetManager()' is private

    // 4. Obtendo a instância única
    FleetManager& central = FleetManager::getInstance();
    central.registrarDrone("Falcon-01");
    central.registrarDrone("Reaper-02");

    // 5. Chamando outro módulo que usa o MESMO Singleton
    moduloLogistica();

    // 6. Verificando que os dados foram unificados
    FleetManager::getInstance().listarFrota();

    /*
     * RESUMO TEÓRICO:
     * O Singleton garante que uma classe tenha apenas uma instância e fornece um 
     * ponto de acesso global a ela.
     * 
     * Vantagens:
     * - Economia de recursos (apenas um objeto na memória).
     * - Coordenação centralizada (evita que dois gerenciadores tentem usar a mesma porta serial, ex).
     * 
     * Cuidados:
     * - Pode dificultar testes unitários (estado global).
     * - Viola o SRP se o Singleton gerenciar o ciclo de vida E a lógica de negócio.
     */

    return 0;
}
