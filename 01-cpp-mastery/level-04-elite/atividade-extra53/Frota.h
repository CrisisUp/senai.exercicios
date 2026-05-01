#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Frota.h
 * @brief Interface para Gestão de Frota via Herança.
 * 
 * Atividade Extra 53 - Arquitetura Modular (Nível 21+).
 * Demonstra a hierarquia de classes e proteção de membros (protected).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Inheritance Layout)
 * - Objeto Caminhao: Alocado na STACK da main.
 * - Layout na RAM: Membros da Base (placa, marca, km) + Membros da Filha (capCarga).
 * - Cadeia de Iniciação: O construtor da Base é executado PRIMEIRO na Stack.
 * - Strings: Objetos na STACK, conteúdo textual alocado na HEAP.
 */

#ifndef FROTA_H
#define FROTA_H

#include <string>

namespace Logistica {

    /**
     * @class Veiculo
     * @brief Classe Base (Pai) contendo a fundação comum de qualquer transporte.
     */
    class Veiculo {
    protected:
        // Protected: Visível para classes filhas, escondido do resto do app.
        std::string placa;
        std::string marca;
        double odometro;

    public:
        /** @brief Construtor da Base (Performance por const ref). */
        Veiculo(const std::string& _placa, const std::string& _marca);

        /** @brief Incrementa a rodagem do veículo. */
        void viajar(double km);

        // Getters
        const std::string& getPlaca() const { return placa; }
        double getKM() const { return odometro; }
    };

    /**
     * @class Caminhao
     * @brief Classe Derivada (Filha) especializada em transporte de carga pesada.
     */
    class Caminhao : public Veiculo {
    private:
        double capacidadeCarga; // Em toneladas
        double cargaAtual;

    public:
        Caminhao(const std::string& _p, const std::string& _m, double cap);

        /** @brief Tenta carregar o veículo respeitando o limite físico. */
        bool carregar(double peso);

        /** @brief Gera relatório técnico consolidando dados da base e da filha. */
        std::string getRelatorioCaminhao() const;
    };

} // namespace Logistica

#endif // FROTA_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
