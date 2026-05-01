/**
 * @file main.cpp
 * @brief Orquestração de Frota Heterogênea via Polimorfismo Dinâmico.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - std::vector (Stack): Armazena shared_ptrs para a classe base Drone.
 * - vtable (Static): Resolvida em runtime para cada chamada de decolar().
 * - Destrutor Virtual: Essencial para evitar Memory Leaks na destruição de classes derivadas.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

// 1. Classe Base com Destrutor Virtual
class Drone {
protected:
    std::string modelo;
public:
    Drone(std::string m) : modelo(m) {
        std::cout << "[LOG] Base " << modelo << " alocada." << std::endl;
    }

    // CRÍTICO: Destrutor virtual garante que filhas sejam deletadas corretamente
    virtual ~Drone() {
        std::cout << RED << "[LOG] Base " << modelo << " desalocada." << RESET << std::endl;
    }

    virtual void decolar() const {
        std::cout << GREEN << "Drone " << modelo << ": Decolagem Padrão." << RESET << std::endl;
    }
};

// 2. Especializações
class DroneVigilancia : public Drone {
public:
    DroneVigilancia(std::string m) : Drone(m) {}
    ~DroneVigilancia() { std::cout << RED << "[LOG] Especialização Vigilância removida." << RESET << std::endl; }

    void decolar() const override {
        std::cout << MAGENTA << "Drone " << modelo << " [Vigilância]: Decolagem silenciosa ativada." << RESET << std::endl;
    }
};

class DroneCarga : public Drone {
public:
    DroneCarga(std::string m) : Drone(m) {}
    ~DroneCarga() { std::cout << RED << "[LOG] Especialização Carga removida." << RESET << std::endl; }

    void decolar() const override {
        std::cout << CYAN << "Drone " << modelo << " [Carga]: Decolagem pesada com propulsão extra." << RESET << std::endl;
    }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Comando Central de Frota Polimórfica ---" << std::endl;

    // 3. Vetor Heterogêneo (Polimorfismo em Ação)
    std::vector<std::shared_ptr<Drone>> frota;

    frota.push_back(std::make_shared<DroneVigilancia>("Spy-007"));
    frota.push_back(std::make_shared<DroneCarga>("Hercules-01"));
    frota.push_back(std::make_shared<Drone>("Generic-X"));

    std::cout << "\nIniciando Sequência de Decolagem de Frota:" << std::endl;
    for (const auto& drone : frota) {
        // Chamada polimórfica: decide em tempo de execução
        drone->decolar();
    }

    std::cout << "\nEncerrando Missão e Limpando Memória..." << std::endl;
    frota.clear(); // Aqui o destrutor virtual entra em ação

    std::cout << "\n--- Operação Polimórfica Finalizada ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * 1. Polimorfismo Dinâmico: A capacidade de tratar objetos de diferentes tipos de forma uniforme.
     * 2. Requisito 1 (Herança): As classes devem estar na mesma hierarquia.
     * 3. Requisito 2 (Virtual): O método no pai deve ser virtual.
     * 4. Requisito 3 (Indireção): Deve-se usar ponteiros ou referências da classe base.
     * 5. Destrutor Virtual: Se o pai não tiver destrutor virtual, 'delete' via ponteiro de base
     *    NÃO chamará o destrutor da filha, causando vazamento de memória.
     */

    return 0;
}
