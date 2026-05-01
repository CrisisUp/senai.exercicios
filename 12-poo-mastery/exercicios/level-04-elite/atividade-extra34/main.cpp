#include <iostream>
#include <string>
#include <memory>

/**
 * @file main.cpp
 * @brief Implementação do Design Pattern Decorator para Upgrades de Drone.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Componente Original (Heap): O objeto base Drone.
 * - Decoradores (Heap): Cada decorador envolve o objeto anterior, criando uma "cebola" de funcionalidades.
 * - Memória: Gerenciada via std::shared_ptr para garantir limpeza segura da cadeia.
 */

// --- 1. COMPONENTE (Interface) ---
class IDrone {
public:
    virtual ~IDrone() = default;
    virtual std::string getDescricao() const = 0;
    virtual double getPreco() const = 0;
};

// --- 2. COMPONENTE CONCRETO ---
class DroneBasico : public IDrone {
public:
    std::string getDescricao() const override { return "Drone Nexus-Alpha [Básico]"; }
    double getPreco() const override { return 1200.00; }
};

// --- 3. DECORADOR BASE ---
class DroneDecorator : public IDrone {
protected:
    std::shared_ptr<IDrone> droneEnvolvido;
public:
    DroneDecorator(std::shared_ptr<IDrone> drone) : droneEnvolvido(drone) {}
    
    std::string getDescricao() const override { return droneEnvolvido->getDescricao(); }
    double getPreco() const override { return droneEnvolvido->getPreco(); }
};

// --- 4. DECORADORES CONCRETOS ---

class BlindagemReforcada : public DroneDecorator {
public:
    BlindagemReforcada(std::shared_ptr<IDrone> drone) : DroneDecorator(drone) {}

    std::string getDescricao() const override {
        return droneEnvolvido->getDescricao() + " + Blindagem de Titânio";
    }

    double getPreco() const override {
        return droneEnvolvido->getPreco() + 450.00;
    }
};

class SensorLongoAlcance : public DroneDecorator {
public:
    SensorLongoAlcance(std::shared_ptr<IDrone> drone) : DroneDecorator(drone) {}

    std::string getDescricao() const override {
        return droneEnvolvido->getDescricao() + " + Sensor LiDAR Pro";
    }

    double getPreco() const override {
        return droneEnvolvido->getPreco() + 780.00;
    }
};

// --- 5. EXECUÇÃO ---

int main() {
    std::cout << "--- SkyCargo Nexus: Customização de Unidades (Decorator) ---" << std::endl;

    // Criando um drone básico
    std::shared_ptr<IDrone> meuDrone = std::make_shared<DroneBasico>();
    std::cout << "\n[Unit] " << meuDrone->getDescricao() << " | Preço: $" << meuDrone->getPreco() << std::endl;

    // Decorando com Blindagem
    std::cout << "--- Instalando Upgrade: Blindagem ---" << std::endl;
    meuDrone = std::make_shared<BlindagemReforcada>(meuDrone);
    std::cout << "[Unit] " << meuDrone->getDescricao() << " | Preço: $" << meuDrone->getPreco() << std::endl;

    // Decorando com Sensor (Note que ele já está blindado!)
    std::cout << "--- Instalando Upgrade: Radar Especial ---" << std::endl;
    meuDrone = std::make_shared<SensorLongoAlcance>(meuDrone);
    
    std::cout << "\n\033[32m[FINAL] Unidade Pronta para Missão:\033[0m" << std::endl;
    std::cout << "\033[36mDescrição: " << meuDrone->getDescricao() << "\033[0m" << std::endl;
    std::cout << "\033[33mInvestimento Total: $" << meuDrone->getPreco() << "\033[0m" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * O padrão Decorator permite anexar responsabilidades extras a um objeto de forma dinâmica.
     * 
     * Diferença da Herança:
     * - Herança: Estática (em tempo de compilação). Você decide o tipo no código.
     * - Decorator: Dinâmica (em tempo de execução). Você decide os upgrades durante o uso.
     * 
     * SRP: Cada decorador foca em apenas uma funcionalidade extra.
     */

    return 0;
}
