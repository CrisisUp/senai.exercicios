/**
 * @file Calculadora.h
 * @brief Definição (Declaração) da classe de cálculos de engenharia.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <cmath>

/**
 * @brief Classe que encapsula o "motor" matemático da aplicação.
 */
class CalculadoraEngenharia {
public:
    /**
     * @brief Calcula o volume de um cilindro.
     * @param raio Raio da base (metros).
     * @param altura Altura do cilindro (metros).
     * @return Volume em m³.
     */
    static double calcularVolumeCilindro(double raio, double altura);

    /**
     * @brief Calcula a área de um círculo.
     * @param raio Raio do círculo.
     * @return Área em m².
     */
    static double calcularAreaCirculo(double raio);
};

#endif // CALCULADORA_H
