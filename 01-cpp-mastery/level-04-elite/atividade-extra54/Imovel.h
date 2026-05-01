#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Imovel.h
 * @brief Interface Polimórfica para Gestão de Imóveis.
 * 
 * Atividade Extra 54 - Arquitetura Modular (Nível 21+).
 * Demonstra a ligação dinâmica (Late Binding) e destrutores virtuais.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Polymorphic Layout)
 * - vptr (Virtual Pointer): Cada instância (Casa/Apto) na RAM contém um ponteiro 
 *   para a V-TABLE (8 bytes).
 * - V-TABLE: Tabela no DATA SEGMENT mapeando o endereço real de calcularTotal().
 * - Heap/Stack: Objetos podem residir em ambos, mas o acesso polimórfico 
 *   costuma ocorrer via ponteiros para a Base na HEAP.
 */

#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>

namespace Imobiliaria {

    /**
     * @class Imovel
     * @brief Classe Base Polimórfica (O Contrato Imobiliário).
     */
    class Imovel {
    protected:
        std::string endereco;
        long long valorBaseCentavos; // Guardião Financeiro

    public:
        Imovel(const std::string& _end, double _valor);

        /**
         * @brief Método Virtual: Define comportamento redefinível pelas filhas.
         * @return double Valor total convertido para real (apenas na interface).
         */
        virtual double calcularTotal() const;

        /**
         * @brief DESTRUTOR VIRTUAL: REGRA DE OURO DA POO ELITE.
         * Garante que as classes filhas sejam limpas da RAM.
         */
        virtual ~Imovel();

        // Getters
        const std::string& getEndereco() const { return endereco; }
    };

    /**
     * @class Apartamento
     * @brief Especialização com regras de condomínio.
     */
    class Apartamento : public Imovel {
    private:
        long long taxaCondominioCentavos;

    public:
        Apartamento(const std::string& _e, double _v, double _condo);
        
        /** @brief Sobrescrita (Override) da lógica de cálculo. */
        double calcularTotal() const override;
        
        ~Apartamento() override;
    };

    /**
     * @class Casa
     * @brief Especialização com regras de manutenção predial.
     */
    class Casa : public Imovel {
    private:
        long long taxaJardimCentavos;

    public:
        Casa(const std::string& _e, double _v, double _jardim);
        
        double calcularTotal() const override;
        
        ~Casa() override;
    };

} // namespace Imobiliaria

#endif // IMOVEL_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
