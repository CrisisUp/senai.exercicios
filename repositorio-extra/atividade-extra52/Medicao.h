/**
 * @file Medicao.h
 * @brief Interface para a classe Medicao com Sobrecarga de Operadores.
 * 
 * Atividade Extra 52 - Arquitetura Modular (Nível 11+).
 * Demonstra como transformar classes em tipos numéricos naturais.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Operator Lifecycle)
 * - Objeto Medicao: Alocado na STACK da main (Valor e Unidade).
 * - Operador +: Cria um objeto temporário na STACK que é movido/copiado para o destino.
 * - Friend Operator <<: Acessa o fluxo de saída sem criar instâncias extras.
 */

#ifndef MEDICAO_H
#define MONITORAMENTO_H

#include <string>
#include <iostream>
#include <exception>

namespace IoT {

    /**
     * @class IncompatibilidadeUnidade
     * @brief Exceção para erros de soma física ilegal.
     */
    class IncompatibilidadeUnidade : public std::exception {
    public:
        const char* what() const throw() {
            return "Erro: Tentativa de operar com unidades físicas diferentes!";
        }
    };

    class Medicao {
    private:
        double valor;
        std::string unidade;

    public:
        Medicao(double v, const std::string& u);

        // --- SOBRECARGA DE OPERADORES BINÁRIOS ---
        
        /** @brief Soma duas medições se as unidades forem compatíveis. */
        Medicao operator+(const Medicao& outra) const;

        /** @brief Compara se o valor é menor. */
        bool operator<(const Medicao& outra) const;

        /** @brief Compara igualdade de valor e unidade. */
        bool operator==(const Medicao& outra) const;

        // --- SOBRECARGA DE ENTRADA/SAÍDA (FRIEND) ---
        friend std::ostream& operator<<(std::ostream& os, const Medicao& m);

        // Getters
        double getValor() const { return valor; }
        const std::string& getUnidade() const { return unidade; }
    };

} // namespace IoT

#endif // MEDICAO_H
