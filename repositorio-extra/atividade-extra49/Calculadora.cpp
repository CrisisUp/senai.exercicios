/**
 * @file Calculadora.cpp
 * @brief Implementação da Lógica de Cálculo de Engenharia.
 * 
 * Atividade Extra 49 - Arquitetura Modular (Nível 11+).
 * Isola a física e a matemática da interface de usuário.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Calculadora.h"
#include <cmath>

namespace CalculadoraEngenharia {

    double calcularAreaCirculo(double raio) {
        return PI * std::pow(raio, 2);
    }

    double calcularVolumeCilindro(double raio, double altura) {
        // Reuso de código interno do módulo
        return calcularAreaCirculo(raio) * altura;
    }

}
