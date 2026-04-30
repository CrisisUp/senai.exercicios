/**
 * @file buffer_handler.c
 * @brief Manipulador de memória bruta em C.
 */

#include <stdio.h>

/**
 * Preenche um buffer de inteiros alocado pelo Rust.
 * Demonstra a escrita direta em memória compartilhada.
 */
void processar_buffer_c(int *buffer, int tamanho)
{
    printf("[MUNDO C]: Recebi um buffer de tamanho %d em %p\n", tamanho, (void *)buffer);

    for (int i = 0; i < tamanho; i++)
    {
        // Simula o processamento de sensores (índice * 10)
        buffer[i] = i * 10;
        printf("[MUNDO C]: Processando item %d -> Valor %d\n", i, buffer[i]);
    }
}
