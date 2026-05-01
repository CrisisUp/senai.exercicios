/**
 * @file Tanque.h
 * @brief Definição da classe Tanque para o Desafio Integrador SA-3.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef TANQUE_H
#define TANQUE_H

#include <string>
#include <iostream>
#include "../../level-04-elite/atividade-extra52/Medicao.h" // Reutilização da Atividade 52

namespace Refinaria {

    /**
     * @brief Classe que representa um tanque de armazenamento industrial.
     */
    class Tanque {
    private:
        std::string id;
        std::string produto;
        double volumeAtual;
        double capacidadeMax;

    public:
        /**
         * @brief Construtor do tanque.
         * @param _id Identificação do tanque.
         * @param _produto Tipo de combustível.
         * @param _cap Capacidade máxima (litros).
         */
        Tanque(std::string _id, std::string _produto, double _cap);

        // SOBRECARGA: Adiciona o conteúdo de outro tanque (Mesmo produto)
        Tanque operator+(const Tanque& outro) const;

        // SOBRECARGA: Compara qual tanque está com maior volume
        bool operator>(const Tanque& outro) const;

        // SOBRECARGA AMIGÁVEL: Impressão do status do tanque
        friend std::ostream& operator<<(std::ostream& os, const Tanque& t);

        // Métodos de Negócio
        bool carregar(double litros);
        void esvaziar();

        // Getters
        std::string getId() const { return id; }
        std::string getProduto() const { return produto; }
        double getVolume() const { return volumeAtual; }
    };
}

#endif // TANQUE_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
