/**
 * @file main.cpp
 * @brief Demonstração de Gerenciamento de Memória Automático com std::unique_ptr.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - std::unique_ptr (Stack): Ocupa 8 bytes (em 64-bit), contendo o endereço da Heap.
 * - Objeto Drone (Heap): Alocado via std::make_unique.
 * - Destruição: Ocorre automaticamente quando o unique_ptr sai de escopo (RAII).
 */

#include <iostream>
#include <memory>
#include <string>

// Cores ANSI para UX profissional
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

class Drone {
private:
    std::string modelo;
public:
    Drone(std::string m) : modelo(m) {
        std::cout << GREEN << "[LOG] Drone " << modelo << " criado na Heap." << RESET << std::endl;
    }
    
    ~Drone() {
        std::cout << RED << "[LOG] Drone " << modelo << " destruído automaticamente da Heap." << RESET << std::endl;
    }
    
    void decolar() const {
        std::cout << CYAN << "Drone " << modelo << " decolando para missão Nexus..." << RESET << std::endl;
    }
};

void processarDrone(std::unique_ptr<Drone> d) {
    std::cout << YELLOW << "[Processando] Drone transferido para função..." << RESET << std::endl;
    d->decolar();
}

int main() {
    std::cout << "--- SkyCargo Nexus: Gestão Inteligente de Memória ---" << std::endl;

    {
        // 1. Criação segura com std::make_unique
        std::cout << "\n1. Criando Drone Alpha..." << std::endl;
        auto droneAlpha = std::make_unique<Drone>("Alpha-01");
        droneAlpha->decolar();

        // 2. Tentativa de cópia (Descomente para ver o erro de compilação)
        // std::unique_ptr<Drone> copia = droneAlpha; // ERRO: unique_ptr não permite cópia!
        
        // 3. Transferência de posse (Move Semantics)
        std::cout << "\n2. Transferindo posse do Alpha para processamento..." << std::endl;
        processarDrone(std::move(droneAlpha));

        if (!droneAlpha) {
            std::cout << YELLOW << "[Aviso] Variável 'droneAlpha' agora está nula após std::move." << RESET << std::endl;
        }
    } // Aqui o drone transferido para 'processarDrone' já foi destruído ao final da função,
      // e o escopo atual termina.

    std::cout << "\n--- Fim da Execução Segura ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * O std::unique_ptr é um "Smart Pointer" que implementa o conceito de Propriedade Exclusiva.
     * Ele garante que apenas UM ponteiro aponte para o recurso na Heap em um determinado momento.
     * 
     * Benefícios:
     * 1. Zero Overhead: Tem o mesmo tamanho e performance de um ponteiro cru.
     * 2. Segurança: Impede vazamentos de memória esquecidos.
     * 3. Semântica Clara: Deixa claro quem é o "dono" do objeto.
     */

    return 0;
}
