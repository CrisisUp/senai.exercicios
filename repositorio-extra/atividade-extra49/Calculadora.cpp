/**
 * @file Calculadora.cpp
 * @brief Implementação (Lógica de Negócio) do motor matemático.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Calculadora.h"

// Implementação das funções estáticas declaradas no .h
double CalculadoraEngenharia::calcularVolumeCilindro(double raio, double altura) {
    return calcularAreaCirculo(raio) * altura;
}

double CalculadoraEngenharia::calcularAreaCirculo(double raio) {
    // M_PI está em cmath
    return M_PI * std::pow(raio, 2);
}
