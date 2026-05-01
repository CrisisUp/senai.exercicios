#define ANSI_RESET "\033[0m"
#include "VeiculoAutonomo.h"
#include "Interfaces.h"
#include <vector>
#include <memory>

/**
 * @file main.cpp
 * @brief Implementação da Atividade 27 - LSP (Liskov Substitution Principle).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 */

// 1. Drone: É um veículo autônomo e SABE voar
class Drone : public VeiculoAutonomo, public VeiculoVoador {
public:
    Drone(std::string id) : VeiculoAutonomo(id) {}
    
    void decolar() override {
        std::cout << "[Voo] Drone " << id << " decolando verticalmente..." << std::endl;
    }
};

// 2. Rover: É um veículo autônomo e SABE andar em solo (Mas NÃO voa)
class Rover : public VeiculoAutonomo, public VeiculoTerrestre {
public:
    Rover(std::string id) : VeiculoAutonomo(id) {}

    void acelerar() override {
        std::cout << "[Solo] Rover " << id << " tracionando 6 rodas no terreno..." << std::endl;
    }
};

// 3. Sistema de Controle de Tráfego Aéreo
// SRP: Responsável apenas por gerenciar quem VOA.
// LSP: Aceita qualquer VeiculoVoador e garante que todos sabem decolar.
class ControleTrafegoAereo {
public:
    void autorizarDecolagem(VeiculoVoador* v) {
        std::cout << "\n[Torre] Autorizando decolagem para unidade voadora..." << std::endl;
        v->decolar();
    }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Sistema de Integridade LSP ---" << std::endl;

    ControleTrafegoAereo torre;

    auto meuDrone = std::make_shared<Drone>("Falcon-LSP");
    auto meuRover = std::make_shared<Rover>("GroundScout-LSP");

    // Cenário Correto: Drone é um VeiculoVoador
    torre.autorizarDecolagem(meuDrone.get());

    // Cenário de Erro Evitado:
    // Se tentarmos passar o meuRover para a torre, o COMPILADOR impedirá.
    // torre.autorizarDecolagem(meuRover.get()); // ERRO: Rover não é VeiculoVoador

    std::cout << "\nTestando capacidades individuais:" << std::endl;
    meuRover->acelerar();

    /*
     * RESUMO TEÓRICO:
     * O LSP (Liskov Substitution Principle) afirma que objetos de uma superclasse 
     * devem ser substituíveis por objetos de uma subclasse sem quebrar o sistema.
     * 
     * Se tivéssemos colocado 'virtual void voar()' na base 'VeiculoAutonomo', 
     * o Rover herdaria algo que não pode fazer, violando o LSP e gerando 
     * erros em tempo de execução. 
     * 
     * A solução foi separar as capacidades em Interfaces. Agora, a Torre de Controle 
     * só aceita quem realmente assina o contrato de 'VeiculoVoador'.
     */

    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */
