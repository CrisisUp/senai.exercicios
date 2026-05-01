/**
 * @file main.cpp
 * @brief Tratamento de Erros Resiliente com Exceções Orientadas a Objetos.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Exceção (Stack): Objetos de exceção são geralmente criados na stack e capturados por referência.
 * - Fluxo de Controle: O stack unwinding ocorre automaticamente, limpando objetos locais até encontrar um catch.
 */

#include <iostream>
#include <exception>
#include <string>

// Cores ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

// 1. Definição de Exceção Customizada
class SkyCargoException : public std::exception {
protected:
    std::string mensagem;
public:
    SkyCargoException(std::string msg) : mensagem(msg) {}
    virtual const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

class BateriaCriticaException : public SkyCargoException {
public:
    BateriaCriticaException() : SkyCargoException("ERRO CRÍTICO: Bateria abaixo de 15%. Operação abortada!") {}
};

class CargaExcedidaException : public SkyCargoException {
public:
    CargaExcedidaException() : SkyCargoException("ERRO DE CARGA: Peso acima do limite estrutural do drone.") {}
};

// 2. Classe de Negócio
class DroneNexus {
private:
    std::string modelo;
    int bateria;
    float cargaAtual;

public:
    DroneNexus(std::string m) : modelo(m), bateria(100), cargaAtual(0) {}

    void setBateria(int valor) {
        if (valor < 0 || valor > 100) {
            throw SkyCargoException("VALOR INVÁLIDO: Bateria deve estar entre 0 e 100.");
        }
        bateria = valor;
    }

    void carregar(float peso) {
        if (peso > 50.0f) {
            throw CargaExcedidaException();
        }
        cargaAtual = peso;
        std::cout << GREEN << "[LOG] Carga de " << peso << "kg aceita." << RESET << std::endl;
    }

    void decolar() {
        std::cout << CYAN << "Verificando pré-requisitos de decolagem para " << modelo << "..." << RESET << std::endl;
        if (bateria < 15) {
            throw BateriaCriticaException();
        }
        std::cout << GREEN << "SISTEMAS OK. Drone " << modelo << " decolando!" << RESET << std::endl;
    }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Sistema de Resiliência de Voo ---" << std::endl;

    DroneNexus meuDrone("Falcon-09");

    // Cenário 1: Erro de Valor Inválido
    try {
        std::cout << "\nTentando configurar bateria inválida..." << std::endl;
        meuDrone.setBateria(150);
    } catch (const SkyCargoException& e) {
        std::cerr << RED << e.what() << RESET << std::endl;
    }

    // Cenário 2: Erro de Carga
    try {
        std::cout << "\nTentando carregar 80kg..." << std::endl;
        meuDrone.carregar(80.0f);
    } catch (const CargaExcedidaException& e) {
        std::cerr << YELLOW << "[Alerta de Engenharia] " << e.what() << RESET << std::endl;
    }

    // Cenário 3: Erro Fatal (Bateria Crítica)
    try {
        std::cout << "\nSimulando bateria fraca (10%) e decolagem..." << std::endl;
        meuDrone.setBateria(10);
        meuDrone.decolar();
    } catch (const BateriaCriticaException& e) {
        std::cerr << RED << "!!! RESGATE DE EMERGÊNCIA !!!\n" << e.what() << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro desconhecido: " << e.what() << std::endl;
    }

    std::cout << "\n--- O sistema encerrou as tentativas de voo com segurança ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * 1. RAII (Resource Acquisition Is Initialization): O C++ garante que ao lançar uma exceção,
     *    todos os objetos locais (stack) tenham seus destrutores chamados (stack unwinding).
     * 2. Captura por Referência: Sempre capture exceções por 'const exception&' para evitar
     *    cópias desnecessárias e o problema de 'object slicing'.
     * 3. noexcept: O método what() é marcado como noexcept porque não deve lançar exceções
     *    enquanto estamos tratando uma exceção.
     */

    return 0;
}
