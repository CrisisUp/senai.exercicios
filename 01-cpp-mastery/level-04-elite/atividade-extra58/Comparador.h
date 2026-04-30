/**
 * @file Comparador.h
 * @brief Interface Genérica com Especialização para Análise de Sensores.
 * 
 * Atividade Extra 58 - Programação Genérica II (Nível 31+).
 * Demonstra a resolução de tipos em compile-time e polimorfismo estático.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Static Resolve)
 * - Templates: Não ocupam RAM.
 * - Código Gerado: O compilador cria instâncias físicas no CODE SEGMENT.
 * - Escolha de Rota: A decisão entre a versão genérica e a especializada é 
 *   feita 100% no compile-time (Zero Runtime Penalty).
 */

#ifndef COMPARADOR_H
#define COMPARADOR_H

#include <string>

namespace IoT {

    /** @struct LeituraSensor: Exemplo de dado complexo. */
    struct LeituraSensor {
        int id;
        double valor;

        // OBRIGATÓRIO: Operador < para o template genérico funcionar
        bool operator<(const LeituraSensor& outra) const {
            return this->valor < outra.valor;
        }
    };

    /**
     * @brief TEMPLATE GENÉRICO (FANTASMA DO CPU).
     * Usa referências constantes para evitar cópia de T.
     */
    template <typename T>
    const T& obterMaior(const T& a, const T& b) {
        return (a < b) ? b : a;
    }

    /**
     * @brief ESPECIALIZAÇÃO EXPLÍCITA PARA STRING.
     * Regra de Negócio: Compara comprimento em vez de ordem alfabética.
     */
    template <>
    const std::string& obterMaior<std::string>(const std::string& a, const std::string& b) {
        return (a.length() < b.length()) ? b : a;
    }

} // namespace IoT

#endif // COMPARADOR_H
