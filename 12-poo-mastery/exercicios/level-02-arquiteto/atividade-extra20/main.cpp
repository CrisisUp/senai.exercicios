/**
 * @file main.cpp
 * @brief Desafio Integrador: Arquitetura Nexus Guardiana Blindada.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - std::vector<shared_ptr> (Heap): Orquestra o ciclo de vida da frota.
 * - Namespaces (Static): Segmentação lógica do sistema.
 * - Exceptions (Stack): Fluxo de erro resiliente.
 * - Templates (Static): Processamento genérico de telemetria.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <exception>

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

namespace NexusGuard {

    // 1. Sistema de Exceções
    class GuardianException : public std::exception {
        std::string msg;
    public:
        GuardianException(std::string m) : msg("ALERTA NEXUS: " + m) {}
        const char* what() const noexcept override { return msg.c_str(); }
    };

    // 2. Templates para Coordenadas
    template <typename T>
    struct Coordenada {
        T x, y;
        bool validar() const {
            return (x >= 0 && y >= 0); // Exemplo simplificado
        }
    };

    // 3. Classe Drone com Const-Correctness
    class Drone {
    private:
        std::string id;
        int bateria;
    public:
        Drone(std::string name) : id(name), bateria(100) {
            std::cout << GREEN << "[Sistema] " << id << " inicializado e integrado ao Nexus." << RESET << std::endl;
        }
        ~Drone() {
            std::cout << RED << "[Sistema] " << id << " removido e conexão encerrada." << RESET << std::endl;
        }

        void lancar(const Coordenada<float>& coord) {
            if (!coord.validar()) {
                throw GuardianException("Coordenadas negativas detectadas para " + id);
            }
            std::cout << CYAN << "[Voo] " << id << " decolando para [" << coord.x << ", " << coord.y << "]" << RESET << std::endl;
        }

        void logStatus() const {
            std::cout << YELLOW << "[Audit] " << id << ": Bateria " << bateria << "% | Status: OK" << RESET << std::endl;
        }
    };

    // 4. Auditoria Imutável
    void auditoriaFrota(const std::vector<std::shared_ptr<Drone>>& frota) {
        std::cout << MAGENTA << "\n--- Iniciando Auditoria de Segurança ---" << RESET << std::endl;
        for (const auto& drone : frota) {
            drone->logStatus();
        }
    }
}

int main() {
    using namespace NexusGuard;
    std::cout << "--- SkyCargo Nexus: Módulo Guardião Nível 20 ---" << std::endl;

    std::vector<std::shared_ptr<Drone>> frota;

    try {
        // Fase 1: Integração de Frota
        frota.push_back(std::make_shared<Drone>("Falcon-Guard-1"));
        frota.push_back(std::make_shared<Drone>("Falcon-Guard-2"));

        auditoriaFrota(frota);

        // Fase 2: Missão com Sucesso
        std::cout << "\nEnviando Missão Alpha..." << std::endl;
        Coordenada<float> alvoOk{150.5f, 300.2f};
        frota[0]->lancar(alvoOk);

        // Fase 3: Missão com Falha (Exceção)
        std::cout << "\nEnviando Missão Beta (Erro Proposital)..." << std::endl;
        Coordenada<float> alvoErro{-10.0f, 50.0f};
        frota[1]->lancar(alvoErro);

    } catch (const GuardianException& e) {
        std::cerr << RED << "\n[CRITICAL ERROR] " << e.what() << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }

    std::cout << "\nLimpando recursos do sistema..." << std::endl;
    frota.clear(); // Demonstração explícita de destruição

    std::cout << "\n--- Nexus Guard: Sistema Encerrado com Segurança ---" << std::endl;

    return 0;
}

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
