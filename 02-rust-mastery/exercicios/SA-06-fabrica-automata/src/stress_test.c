#include <stdio.h>

/**
 * Simula um teste de estresse no hardware do robô.
 * @return 1 se o teste passou, 0 se falhou.
 */
int realizar_stress_test_c(double carga)
{
    printf("[MUNDO C]: Iniciando stress test para carga de %.2f kg...\n", carga);
    if (carga > 100.0)
    {
        printf("[MUNDO C]: ALERTA! Carga excessiva para as juntas hidráulicas.\n");
        return 0;
    }
    printf("[MUNDO C]: Teste de integridade concluído com SUCESSO.\n");
    return 1;
}
