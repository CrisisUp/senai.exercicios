/**
 * @file main.cpp
 * @brief Demonstração de Classes Abstratas e Interfaces (O Contrato Sagrado).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - vtable (Static): Contém os endereços das implementações reais de executarProtocolo().
 * - DispositivoNexus* (Stack): Ponteiro para a abstração.
 * - Objeto Drone (Heap): A instância real que cumpre o contrato.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

// 1. Interface / Classe Abstrata (O Contrato)
class DispositivoNexus {
public:
    virtual ~DispositivoNexus() = default; // Destrutor virtual obrigatório

    // Função Virtual Pura: Define o contrato
    virtual void executarProtocolo() = 0;
    virtual std::string getTipo() const = 0;

    void statusEnergia() {
        std::cout << YELLOW << "[Status] Energia estável em 98%." << RESET << std::endl;
    }
};

// 2. Implementação Concreta (Drone)
class DroneNexus : public DispositivoNexus {
private:
    std::string id;
public:
    DroneNexus(std::string name) : id(name) {}

    void executarProtocolo() override {
        std::cout << GREEN << "[Drone " << id << "] Executando varredura aérea 360..." << RESET << std::endl;
    }

    std::string getTipo() const override { return "Aéreo"; }
};

// 3. Outra Implementação (Rover)
class RoverNexus : public DispositivoNexus {
private:
    std::string id;
public:
    RoverNexus(std::string name) : id(name) {}

    void executarProtocolo() override {
        std::cout << CYAN << "[Rover " << id << "] Analisando composição de solo superficial..." << RESET << std::endl;
    }

    std::string getTipo() const override { return "Terrestre"; }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Gestão de Contratos de Hardware ---" << std::endl;

    // Tentativa de instanciar classe abstrata (ERRO DE COMPILAÇÃO se descomentado)
    // DispositivoNexus d; // "Cannot instantiate abstract class"

    // Uso de Polimorfismo com a Interface
    std::vector<std::unique_ptr<DispositivoNexus>> frota;
    frota.push_back(std::make_unique<DroneNexus>("SkyWatcher-01"));
    frota.push_back(std::make_unique<RoverNexus>("GroundScout-01"));

    for (const auto& dispositivo : frota) {
        std::cout << "\nDispositivo Tipo: " << dispositivo->getTipo() << std::endl;
        dispositivo->statusEnergia();
        dispositivo->executarProtocolo();
    }

    std::cout << "\n--- Protocolos Finalizados com Sucesso ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * 1. Classe Abstrata: Serve como um blueprint para outras classes. Não pode ser instanciada.
     * 2. Função Virtual Pura (= 0): Define uma funcionalidade que deve ser implementada pelas filhas.
     * 3. DIP (Dependency Inversion Principle): O código principal depende da abstração (DispositivoNexus)
     *    e não das classes concretas (Drone/Rover). Isso torna o sistema expansível.
     */

    return 0;
}
