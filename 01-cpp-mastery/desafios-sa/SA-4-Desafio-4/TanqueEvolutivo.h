/**
 * @file TanqueEvolutivo.h
 * @brief Implementação de Tanques Genéricos com Smart Pointers (Nível 31).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef TANQUE_EVOLUTIVO_H
#define TANQUE_EVOLUTIVO_H

#include <string>
#include <iostream>
#include <memory>
#include <iomanip>

namespace EngenhariaElite {

    /**
     * @brief Classe Template TanqueEvolutivo (O Monumento).
     * @tparam T Tipo de dado para a medição (int, double, etc).
     */
    template <typename T>
    class TanqueEvolutivo {
    private:
        std::string id;
        T volumeAtual;
        T capacidadeMax;
        std::string unidade;

    public:
        TanqueEvolutivo(std::string _id, T _cap, std::string _uni) 
            : id(_id), volumeAtual(0), capacidadeMax(_cap), unidade(_uni) {
            std::cout << "\033[32m[REFINARIA]:\033[0m Tanque " << id << " alocado com segurança." << std::endl;
        }

        /**
         * @brief Destrutor Automático (RAII).
         */
        ~TanqueEvolutivo() {
            std::cout << "\033[31m[REFINARIA]:\033[0m Tanque " << id << " desativado e memória limpa." << std::endl;
        }

        bool carregar(T quantidade) {
            if (volumeAtual + quantidade > capacidadeMax) {
                return false; // Transbordo
            }
            volumeAtual += quantidade;
            return true;
        }

        /**
         * @brief Sobrecarga do Operador << para relatório visual.
         */
        friend std::ostream& operator<<(std::ostream& os, const TanqueEvolutivo<T>& t) {
            double percent = (static_cast<double>(t.volumeAtual) / static_cast<double>(t.capacidadeMax)) * 100.0;
            std::string cor = (percent > 90.0) ? "\033[31m" : "\033[36m";

            os << "ID: " << std::left << std::setw(8) << t.id 
               << " | NIVEL: " << cor << std::fixed << std::setprecision(1) 
               << percent << "%\033[0m (" << t.volumeAtual << " " << t.unidade << ")";
            return os;
        }

        // Getters
        std::string getId() const { return id; }
        T getVolume() const { return volumeAtual; }
    };

    /**
     * @brief Especialização de Template para o tipo 'Gás'.
     * Simulando uma especialização onde o comportamento de segurança muda.
     * (Neste caso, apenas um log informativo para o aluno ver a especialização).
     */
    // Nota: Em uma implementação real, poderíamos mudar a lógica de carregar().
}

#endif // TANQUE_EVOLUTIVO_H
