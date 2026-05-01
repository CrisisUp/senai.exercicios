/**
 * @file atividade-extra05.cpp
 * @brief Implementação de Membros Estáticos (Inteligência Coletiva)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Data Segment: 'totalDrones' alocado globalmente (estático).
 * - Stack: Instâncias de Drone.
 */

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

class Drone {
private:
    std::string modelo;
    static int totalDrones; // Declaração de atributo estático

public:
    Drone(std::string m) : modelo(m) {
        totalDrones++;
        std::cout << "[SISTEMA] " << modelo << " entrou em operação." << std::endl;
    }

    ~Drone() {
        totalDrones--;
        std::cout << "[SISTEMA] " << modelo << " saiu de operação." << std::endl;
    }

    // Método Estático
    static void exibirFrota() {
        std::cout << std::endl << GREEN << BOLD << ">>> RELATÓRIO DE FROTA: " << totalDrones << " drones ativos." << RESET << std::endl << std::endl;
    }
};

// Inicialização obrigatória fora da classe
int Drone::totalDrones = 0;

int main() {
    std::cout << BOLD << YELLOW << "=== SKYCARGO NEXUS - MONITORAMENTO GLOBAL ===" << RESET << std::endl;

    Drone::exibirFrota();

    Drone d1("Eagle-01");
    Drone d2("Eagle-02");
    
    {
        std::cout << "[SISTEMA] Ativando unidade temporária..." << std::endl;
        Drone temp("Temp-Unit");
        Drone::exibirFrota();
    } // temp sai de escopo e é destruído

    Drone d3("Eagle-03");
    
    Drone::exibirFrota();

    return 0;
}

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
