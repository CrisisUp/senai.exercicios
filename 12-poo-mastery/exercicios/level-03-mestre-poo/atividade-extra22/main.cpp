/**
 * @file main.cpp
 * @brief Especialização de Comportamento via Sobrescrita (Method Overriding).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - vtable (Static): Armazena os endereços dos métodos virtuais.
 * - override (Compile-time): Garante que a assinatura do método na filha coincide com a do pai.
 */

#include <iostream>
#include <string>

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

class Drone {
protected:
    std::string modelo;

public:
    Drone(std::string m) : modelo(m) {}

    // Método Virtual: Permite que filhas redefinam o comportamento
    virtual void decolar() {
        std::cout << GREEN << "[Drone] " << modelo << ": Iniciando propulsão padrão de 4 motores." << RESET << std::endl;
    }
};

class DroneVigilancia : public Drone {
public:
    DroneVigilancia(std::string m) : Drone(m) {}

    // Sobrescrita: Redefine a lógica para ser furtiva
    void decolar() override {
        std::cout << MAGENTA << "[Stealth] " << modelo << ": Ativando modo silencioso. Decolagem furtiva em progresso..." << RESET << std::endl;
    }
};

class DroneCarga : public Drone {
public:
    DroneCarga(std::string m) : Drone(m) {}

    void decolar() override {
        std::cout << CYAN << "[Heavy] " << modelo << ": Ativando propulsores auxiliares. Decolagem de carga pesada iniciada." << RESET << std::endl;
    }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Customização de Comportamento Tático ---" << std::endl;

    Drone base("Alpha-Gen1");
    DroneVigilancia spy("Shadow-X");
    DroneCarga heavy("Atlas-09");

    std::cout << "\n1. Testando Drone Base:" << std::endl;
    base.decolar();

    std::cout << "\n2. Testando Drone de Vigilância (Override):" << std::endl;
    spy.decolar();

    std::cout << "\n3. Testando Drone de Carga (Override):" << std::endl;
    heavy.decolar();

    std::cout << "\n--- Sobrescrita Verificada com Sucesso ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * 1. virtual: Cria uma entrada na VTable, permitindo a resolução dinâmica de chamadas.
     * 2. override: É um "especificador" que previne erros comuns (ex: errar o nome do método no pai).
     * 3. Late Binding: O compilador não decide qual função chamar no momento da compilação,
     *    mas sim no momento da execução, com base no tipo real do objeto.
     */

    return 0;
}
