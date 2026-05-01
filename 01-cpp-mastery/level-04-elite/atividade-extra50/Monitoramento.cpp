#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Monitoramento.cpp
 * @brief Implementação do Módulo IoT Industrial.
 * 
 * Isola a lógica de segurança de sensores do namespace global.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Monitoramento.h"

namespace IoT {

    SensorPressao::SensorPressao(const std::string& _id) 
        : id(_id), valor(0.0) {}

    bool SensorPressao::valorEhSeguro(double v) const {
        // Regra de Ouro: Margem de operação entre 0 e 100 psi
        return (v >= 0.0 && v <= 100.0);
    }

    bool SensorPressao::registrarLeitura(double v) {
        // O usuário do módulo nunca chama valorEhSeguro() diretamente
        if (valorEhSeguro(v)) {
            valor = v;
            return true;
        }
        return false;
    }

} // namespace IoT
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
