/**
 * @file main.cpp
 * @brief Especialização de Classes via Herança e modificador protected.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Objeto DroneCarga (Stack/Heap): Contém o layout da classe base + atributos da classe filha.
 * - protected (Acesso): Atributos visíveis na linhagem, mas encapsulados para o usuário.
 */

#include <iostream>
#include <string>

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

// 1. Classe Base (O Antepassado)
class Drone {
protected:
    std::string modelo;
    int bateria;

public:
    Drone(std::string mod) : modelo(mod), bateria(100) {}
    
    void decolar() {
        std::cout << GREEN << "[Drone] " << modelo << " decolagem padrão iniciada..." << RESET << std::endl;
    }

    void statusBateria() const {
        std::cout << YELLOW << "[Bateria] " << bateria << "%" << RESET << std::endl;
    }
};

// 2. Classe Derivada (A Especialização)
class DroneCarga : public Drone {
private:
    float cargaMaxima;
    float cargaAtual;

public:
    DroneCarga(std::string mod, float max) 
        : Drone(mod), cargaMaxima(max), cargaAtual(0.0f) {}

    void carregarSuprimento(float peso) {
        if (cargaAtual + peso <= cargaMaxima) {
            cargaAtual += peso;
            std::cout << CYAN << "[Carga] " << peso << "kg adicionados. Total: " 
                      << cargaAtual << "kg / " << cargaMaxima << "kg" << RESET << std::endl;
            
            // Acesso ao atributo 'bateria' da classe pai via 'protected'
            bateria -= 5; // Carregamento pesado consome energia
        } else {
            std::cout << MAGENTA << "[Alerta] Sobrecarga detectada! Operação abortada." << RESET << std::endl;
        }
    }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Gestão de Linhagens de Hardware ---" << std::endl;

    // Instanciando a especialização
    DroneCarga titan("Titan-V1", 500.0f);

    std::cout << "\n1. Testando Métodos Herdados:" << std::endl;
    titan.decolar();
    titan.statusBateria();

    std::cout << "\n2. Testando Métodos Especializados:" << std::endl;
    titan.carregarSuprimento(200.0f);
    titan.statusBateria();

    std::cout << "\n3. Tentativa de Sobrecarga:" << std::endl;
    titan.carregarSuprimento(400.0f);

    std::cout << "\n--- Evolução de Classe Concluída ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * 1. Herança (: public): Permite que uma classe herde a interface e o estado de outra.
     * 2. protected: Essencial para herança. Permite que classes filhas acessem membros internos
     *    sem expô-los ao resto do mundo (encapsulamento de linhagem).
     * 3. Especialização: A classe filha adiciona valor ao projeto original (DRY - Don't Repeat Yourself).
     */

    return 0;
}
