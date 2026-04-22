/**
 * @file atividade-extra57-memoria.cpp
 * @brief Teste de gerenciamento manual de memória (Heap vs Stack).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <string>
#include "Buffer.h" // Nossa interface de memória manual

using namespace std;
using namespace Logistica;

void simularOperacaoEmCaminhao() {
    cout << "\n\033[36m--- INÍCIO DO CICLO DE OPERAÇÃO ---\033[0m" << endl;
    
    /**
     * OPERAÇÃO NA STACK:
     * O objeto 'meuBuffer' vive na STACK (pilha). 
     * Ele será destruído automaticamente assim que esta 
     * função terminar.
     */
    BufferLog meuBuffer(100); // 100 bytes na Heap controlados pela Stack

    meuBuffer.escrever("MOTOR_LIGADO");
    meuBuffer.escrever("GPS_ATIVO_LAT-23.5");
    meuBuffer.escrever("CARGA_OK");
    
    meuBuffer.despejar();
    
    cout << "Espaço restante no buffer: " << meuBuffer.getTamanhoDisponivel() << " bytes." << endl;
    cout << "\033[36m--- FIM DO CICLO DE OPERAÇÃO ---\033[0m" << endl;
    
    // O Destrutor ~BufferLog() será chamado AQUI automaticamente.
}

int main() {
    cout << "\033[36m===============================================\033[0m" << endl;
    cout << "     GERENCIAMENTO DE MEMÓRIA DINÂMICA (RAII)  " << endl;
    cout << "\033[36m===============================================\033[0m" << endl;

    // Executando o ciclo 2 vezes para provar o uso e limpeza da memória.
    cout << "Simulando Ciclo 1..." << endl;
    simularOperacaoEmCaminhao();

    cout << "\nSimulando Ciclo 2..." << endl;
    simularOperacaoEmCaminhao();

    cout << "\n\033[32m[RESULTADO]:\033[0m Ambos os ciclos foram concluídos com limpeza total da RAM." << endl;
    cout << "\033[36m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HEAP, STACK E RAII
    ===============================================================

    1. MEMÓRIA NA HEAP:
       - Memória alocada dinamicamente via 'new'. 
       - Se você não der 'delete', ela ficará "presa" mesmo 
         depois que a função terminar (Vazamento de Memória).

    2. O QUE É RAII (Resource Acquisition Is Initialization):
       - É o padrão de ouro do C++. Significa que a aquisição de um 
         recurso (memória) ocorre no construtor e sua liberação 
         ocorre no destrutor.
       - Garante que a memória esteja sempre limpa, independente 
         de como a função termina (mesmo com erros ou exceções).

    3. VANTAGEM DIDÁTICA:
       - O aluno sai do nível de "usuário de bibliotecas" e entra no 
         nível de "criador de sistemas eficientes". 
       - Ele entende o porquê de usar 'delete[]' para arrays em 
         vez de apenas 'delete'.

    4. POSICIONAMENTO EM CADEIA:
       - Este conhecimento é a base para entender como Ponteiros 
         Inteligentes (unique_ptr) funcionam por baixo do capô.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Smart Pointers (unique_ptr, shared_ptr).
    - Fragmentação de Memória na Heap.
    - Rule of Three (Construtor de Cópia e Atribuição).
    ===============================================================
*/
