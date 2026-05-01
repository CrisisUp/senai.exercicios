#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Monitoramento.h
 * @brief Interface para o Módulo de Telemetria IoT Industrial.
 * 
 * Atividade Extra 50 - Arquitetura Modular (Nível 11+).
 * Demonstra a organização de sistemas via Namespaces.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (IoT Module Layout)
 * - Objeto SensorPressao: Alocado na STACK durante o ciclo da main.
 * - Atributos de Classe (id, valor): Localizados na STACK dentro da instância.
 * - Namespace IoT: Representa uma barreira de escopo lógica, sem custo adicional de RAM.
 */

#ifndef MONITORAMENTO_H
#define MONITORAMENTO_H

#include <string>

/**
 * @namespace IoT
 * @brief Isola os drivers de sensores da camada de lógica de negócios.
 */
namespace IoT {

    class SensorPressao {
    private:
        std::string id;
        double valor;

        /**
         * @brief Método Privado Auxiliar (Encapsulamento Interno).
         * @return true se o valor estiver na faixa 0-100 psi.
         */
        bool valorEhSeguro(double v) const;

    public:
        /**
         * @brief Construtor de inicialização.
         */
        SensorPressao(const std::string& _id);

        /**
         * @brief Tenta registrar uma leitura no sistema.
         * @return true se a leitura for validada e salva.
         */
        bool registrarLeitura(double v);

        // Getters (FANTASMA DO CPU)
        const std::string& getId() const { return id; }
        double getValor() const { return valor; }
    };

} // namespace IoT

#endif // MONITORAMENTO_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
