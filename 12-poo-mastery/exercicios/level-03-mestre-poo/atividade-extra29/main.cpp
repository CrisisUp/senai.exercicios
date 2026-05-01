#define ANSI_RESET "\033[0m"
#include "IDrone.h"
#include <iostream>
#include <memory>

/**
 * @file main.cpp
 * @brief Implementação da Atividade 29 - DIP (Dependency Inversion Principle).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 */

// 1. Módulos de Baixo Nível (Implementações Concretas)
class DroneFalcon9 : public IDrone {
public:
    void executarMissao() override { std::cout << "[Falcon-9] Decolagem vertical e entrega rápida iniciada." << std::endl; }
    std::string getModelo() const override { return "SpaceX Falcon 9"; }
};

class DroneMQ9 : public IDrone {
public:
    void executarMissao() override { std::cout << "[MQ-9] Vigilância de longa duração e patrulha ativada." << std::endl; }
    std::string getModelo() const override { return "General Atomics MQ-9 Reaper"; }
};

// 2. Módulo de Alto Nível (Independente de implementação)
// DIP: CentralComando depende da abstração IDrone, não de classes concretas.
class CentralComando {
private:
    IDrone* drone; // Dependência injetada
public:
    // Injeção de Dependência via Construtor
    CentralComando(IDrone* d) : drone(d) {}

    void iniciarOperacao() {
        std::cout << "\n[Central] Iniciando operação com a unidade: " << drone->getModelo() << std::endl;
        drone->executarMissao();
    }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Inversão de Dependência DIP ---" << std::endl;

    // Criamos as implementações (Baixo Nível)
    DroneFalcon9 falcon;
    DroneMQ9 reaper;

    // 3. A mágica da Injeção:
    // Injetamos o Falcon na Central
    CentralComando nexusAlpha(&falcon);
    nexusAlpha.iniciarOperacao();

    // Injetamos o Reaper (MQ-9) na Central
    // A classe CentralComando NÃO mudou para aceitar um modelo diferente!
    CentralComando nexusBeta(&reaper);
    nexusBeta.iniciarOperacao();

    /*
     * RESUMO TEÓRICO:
     * O DIP (Dependency Inversion Principle) diz que módulos de alto nível não devem
     * depender de módulos de baixo nível. Ambos devem depender de ABSTRAÇÕES.
     * 
     * Sem DIP: CentralComando teria 'DroneFalcon9 falcon;' interno (Alto acoplamento).
     * Com DIP: CentralComando recebe 'IDrone*' (Baixo acoplamento).
     * 
     * Isso permite testar a Central com "Drones de Teste" (Mocks) e adicionar 
     * novos modelos de drones sem nunca alterar o código da Central.
     */

    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */
