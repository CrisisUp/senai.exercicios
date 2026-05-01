#include <iostream>
#include <memory>
#include <string>

/**
 * @file main.cpp
 * @brief Implementação do Design Pattern Strategy para Inteligência de Voo.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Drone (Contexto - Stack): Mantém um smart pointer para a estratégia atual.
 * - Estratégias (Heap): Instanciadas dinamicamente conforme a necessidade do ambiente.
 */

// --- 1. INTERFACE ESTRATÉGIA (O Algoritmo) ---
class IFlightStrategy {
public:
    virtual ~IFlightStrategy() = default;
    virtual void executarManobra() const = 0;
    virtual std::string getNome() const = 0;
};

// --- 2. ESTRATÉGIAS CONCRETAS ---

class ModoEconomico : public IFlightStrategy {
public:
    std::string getNome() const override { return "Modo Eco-Voo"; }
    void executarManobra() const override {
        std::cout << "\033[32m[ECO] Rotação reduzida. Economizando 30% de bateria. Estabilidade: Máxima.\033[0m" << std::endl;
    }
};

class ModoEsportivo : public IFlightStrategy {
public:
    std::string getNome() const override { return "Modo Sport-Nexus"; }
    void executarManobra() const override {
        std::cout << "\033[33m[SPORT] Potência máxima nos 4 motores. Velocidade: 120km/h. Cuidado com o consumo!\033[0m" << std::endl;
    }
};

class ModoFurtivo : public IFlightStrategy {
public:
    std::string getNome() const override { return "Modo Stealth-Shadow"; }
    void executarManobra() const override {
        std::cout << "\033[35m[STEALTH] Luzes apagadas. Redução de ruído ativa. Invisível ao radar acústico.\033[0m" << std::endl;
    }
};

// --- 3. CONTEXTO (O Drone que usa a Inteligência) ---
class DroneNexus {
private:
    std::string id;
    std::unique_ptr<IFlightStrategy> inteligencia;

public:
    DroneNexus(std::string name) : id(name) {}

    // Injeção de Estratégia em tempo de execução
    void setInteligencia(std::unique_ptr<IFlightStrategy> novaInt) {
        std::cout << "\n[Sistema] Drone " << id << " carregando novo algoritmo: " << novaInt->getNome() << std::endl;
        inteligencia = std::move(novaInt);
    }

    void voar() {
        if (inteligencia) {
            std::cout << "[Voo] Executando comando via " << inteligencia->getNome() << ":" << std::endl;
            inteligencia->executarManobra();
        } else {
            std::cout << "[Erro] Drone " << id << " sem algoritmo de voo definido!" << std::endl;
        }
    }
};

// --- 4. EXECUÇÃO ---

int main() {
    std::cout << "--- SkyCargo Nexus: Inteligência Intercambiável (Strategy Pattern) ---" << std::endl;

    DroneNexus meuDrone("Falcon-X");

    // 1. Decolagem em Modo Econômico
    meuDrone.setInteligencia(std::make_unique<ModoEconomico>());
    meuDrone.voar();

    // 2. Mudança para Modo Esportivo (Situação de Emergência/Velocidade)
    meuDrone.setInteligencia(std::make_unique<ModoEsportivo>());
    meuDrone.voar();

    // 3. Mudança para Modo Furtivo (Área Restrita)
    meuDrone.setInteligencia(std::make_unique<ModoFurtivo>());
    meuDrone.voar();

    std::cout << "\n--- Missão Finalizada com Múltiplos Perfis de Voo ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * O padrão Strategy encapsula algoritmos relacionados e os torna intercambiáveis.
     * 
     * Benefícios:
     * 1. OCP: Podemos adicionar novas manobras (ex: 'ModoResgate') sem tocar na classe Drone.
     * 2. Troca em Runtime: O comportamento muda sem precisar de um novo 'new Drone()'.
     * 3. Limpeza: Elimina estruturas condicionais (switch/if) complexas dentro do contexto.
     */

    return 0;
}
