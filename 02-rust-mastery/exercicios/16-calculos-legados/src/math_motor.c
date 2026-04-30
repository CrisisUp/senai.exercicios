/**
 * @file math_motor.c
 * @brief Biblioteca legada de física industrial em C.
 */

#include <stdio.h>

/**
 * Realiza um cálculo complexo de torque baseado na aceleração.
 * Simula uma função que o Rust não conseguiria validar automaticamente.
 */
double calcular_torque_c(double aceleracao)
{
    // Cálculo legado (Aceleração * Constante de Inércia do Motor)
    return aceleracao * 9.81 * 1.5;
}
