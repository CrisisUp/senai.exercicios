/**
 * @file atividade-extra59-smart.cpp
 * @brief Programa principal para testar Ponteiros Inteligentes (unique e shared).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <memory> // ESSENCIAL: Biblioteca de Smart Pointers
#include <vector>
#include "SmartResource.h" // Nossa interface modular de hardware

using namespace std;
using namespace Logistica;

/**
 * @brief Função que demonstra a exclusividade do unique_ptr.
 */
void testarUniquePtr() {
    cout << "\n\033[36m--- TESTE: unique_ptr (Propriedade Única) ---\033[0m" << endl;
    
    // Criando um GPS exclusivo para o Caminhão A.
    // make_unique é a forma recomendada (C++14).
    auto gpsA = make_unique<ModuloGPS>("CAM-A-01");
    
    gpsA->atualizarCoordenadas(-23.55, -46.63);
    gpsA->mostrarStatus();

    // Se você tentar dar `auto outro = gpsA;`, o compilador dará erro.
    // Propriedade única significa que não pode ser copiado, apenas MOVIDO.
    cout << "O GPS do Caminhão A será deletado automaticamente ao fim desta função..." << endl;
}

/**
 * @brief Função que demonstra o compartilhamento do shared_ptr.
 */
void testarSharedPtr() {
    cout << "\n\033[36m--- TESTE: shared_ptr (Propriedade Compartilhada) ---\033[0m" << endl;
    
    shared_ptr<ModuloGPS> gpsCentral;

    { // Escopo interno
        cout << "[SISTEMA]: Criando GPS compartilhado no escopo interno..." << endl;
        auto gpsPrincipal = make_shared<ModuloGPS>("CENTRAL-REFINARIA");
        
        // Compartilhando o recurso com o sistema central.
        // A contagem de referência aumenta para 2.
        gpsCentral = gpsPrincipal; 
        
        cout << "[SISTEMA]: Uso do GPS Central: " << gpsCentral.use_count() << endl;
    } // Aqui 'gpsPrincipal' sai de escopo, mas o objeto NÃO é deletado!

    cout << "[SISTEMA]: 'gpsPrincipal' morreu, mas 'gpsCentral' ainda vive." << endl;
    cout << "[SISTEMA]: Uso do GPS Central: " << gpsCentral.use_count() << endl;
    gpsCentral->mostrarStatus();

} // Agora sim, o último dono morre e o objeto é deletado.

int main() {
    cout << "\033[35m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE TELEMETRIA (SMART POINTERS)    " << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    testarUniquePtr();
    
    testarSharedPtr();

    cout << "\n\033[32m[LOGÍSTICA]:\033[0m Todos os recursos foram liberados de forma segura." << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SMART POINTERS (C++ MODERNO)
    ===============================================================

    1. O FIM DO 'DELETE':
       - Usar Smart Pointers implementa o padrão RAII de forma nativa.
       - Eles gerenciam o ciclo de vida do objeto na Heap 
         automaticamente.

    2. unique_ptr vs shared_ptr:
       - unique_ptr: Rápido e sem custo extra (zero-overhead). 
         Ideal para recursos que têm apenas um dono claro.
       - shared_ptr: Possui um pequeno custo extra (Control Block) 
         para manter a contagem de quem está usando o objeto.

    3. VANTAGEM DIDÁTICA:
       - O aluno percebe que o C++ evoluiu para ser uma linguagem 
         tão segura quanto Java/C#, mas mantendo o controle 
         total sobre QUANDO a memória é liberada.

    4. POSICIONAMENTO EM CADEIA:
       - Esta atividade fecha a lacuna entre a Memória Manual (Atividade 57)
         e a programação de sistemas de alta performance e seguros.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Semântica de Movimento (std::move).
    - weak_ptr (Para evitar referências circulares).
    - Performance: Stack vs Heap com Smart Pointers.
    ===============================================================
*/
