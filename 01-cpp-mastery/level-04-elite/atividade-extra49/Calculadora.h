#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Calculadora.h
 * @brief Interface do Motor de Cálculos Geométricos para Engenharia.
 * 
 * Atividade Extra 49 - Arquitetura Modular (Nível 11+).
 * Define as assinaturas das funções de cálculo estrutural.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Modular Layout)
 * - Código de Execução: Reside no CODE SEGMENT do binário final.
 * - Variáveis Locais: Alocadas na STACK durante a execução de cada método.
 * - Desacoplamento: O arquivo .h não consome RAM até que as funções sejam invocadas.
 */

#ifndef CALCULADORA_H
#define CALCULADORA_H

/**
 * @namespace CalculadoraEngenharia
 * @brief Agrupa algoritmos de cálculo para evitar conflitos de nomes (Global Pollution).
 */
namespace CalculadoraEngenharia {
    
    const double PI = 3.141592653589793;

    /**
     * @brief Calcula o volume de um cilindro (pilar/fundação).
     * @param raio Raio da base (metros).
     * @param altura Altura da estrutura (metros).
     * @return double Volume em m³.
     */
    double calcularVolumeCilindro(double raio, double altura);

    /**
     * @brief Calcula a área de um círculo.
     * @param raio Raio em metros.
     * @return double Área em m².
     */
    double calcularAreaCirculo(double raio);
}

#endif // CALCULADORA_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
