#include <iostream>
#include <string>
#include <memory>
#include <vector>

/**
 * @file main.cpp
 * @brief Implementação do Design Pattern Factory Method para a Nexus.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Interfaces (Static/VTable): Definem os contratos de criação e operação.
 * - Produtos Concretos (Heap): Criados pelas fábricas via std::unique_ptr.
 */

// --- PRODUTO (Interface) ---
class Veiculo {
public:
    virtual ~Veiculo() = default;
    virtual void operar() = 0;
};

// --- PRODUTOS CONCRETOS ---
class Drone : public Veiculo {
public:
    void operar() override { std::cout << "\033[36m[Drone] Hélices ativadas. Iniciando patrulha Nexus.\033[0m" << std::endl; }
};

class Rover : public Veiculo {
public:
    void operar() override { std::cout << "\033[33m[Rover] Tração 6x6 ativada. Analisando solo.\033[0m" << std::endl; }
};

// NOVO PRODUTO (Extensão sem mudar o código base)
class Satelite : public Veiculo {
public:
    void operar() override { std::cout << "\033[35m[Satelite] Órbita estabelecida. Link de dados ativo.\033[0m" << std::endl; }
};

// --- FÁBRICA (Interface / Creator) ---
class FabricaVeiculos {
public:
    virtual ~FabricaVeiculos() = default;
    
    // O Factory Method
    virtual std::unique_ptr<Veiculo> criar() const = 0;

    // Lógica que usa o Factory Method
    void prepararOperacao() const {
        std::cout << "[Fábrica] Preparando unidade para entrega..." << std::endl;
        auto v = criar();
        v->operar();
    }
};

// --- FÁBRICAS CONCRETAS ---
class FabricaDrones : public FabricaVeiculos {
public:
    std::unique_ptr<Veiculo> criar() const override { return std::make_unique<Drone>(); }
};

class FabricaRovers : public FabricaVeiculos {
public:
    std::unique_ptr<Veiculo> criar() const override { return std::make_unique<Rover>(); }
};

class FabricaSatelites : public FabricaVeiculos {
public:
    std::unique_ptr<Veiculo> criar() const override { return std::make_unique<Satelite>(); }
};

// --- CLIENTE (Desacoplado) ---
void gerenciarNexus(const FabricaVeiculos& f) {
    f.prepararOperacao();
}

int main() {
    std::cout << "--- SkyCargo Nexus: Linha de Montagem Factory Method ---" << std::endl;

    FabricaDrones fDrone;
    FabricaRovers fRover;
    FabricaSatelites fSatelite;

    std::cout << "\n1. Solicitando unidade aérea:" << std::endl;
    gerenciarNexus(fDrone);

    std::cout << "\n2. Solicitando unidade terrestre:" << std::endl;
    gerenciarNexus(fRover);

    std::cout << "\n3. Solicitando unidade orbital (Extensão OCP):" << std::endl;
    gerenciarNexus(fSatelite);

    std::cout << "\n--- Fábrica Finalizada com Sucesso ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * O Factory Method resolve o problema de criar objetos sem especificar a 
     * classe exata do objeto que será criado.
     * 
     * Por que usar?
     * 1. Desacoplamento: O código cliente (gerenciarNexus) só conhece as interfaces.
     * 2. Flexibilidade: Se criarmos um novo veículo (Satelite), só precisamos de 
     *    uma nova fábrica. O código cliente permanece INTACTO.
     * 3. SRP: A lógica de criação está centralizada na fábrica correspondente.
     */

    return 0;
}
