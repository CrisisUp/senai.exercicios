/**
 * @file atividade-extra59-smart.cpp
 * @brief Interface de Telemetria via Smart Pointers (Elite Memory).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a segurança absoluta da automação de memória moderna.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <memory> 
#include <vector>
#include <iomanip>
#include "SmartResource.h" 

using namespace std;
using namespace Logistica;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string VERMELHO = "\033[31m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

/**
 * @brief Demonstra a posse exclusiva do unique_ptr.
 */
void simularFrotaExclusiva() {
    cout << UI::NEGRITO << "\n--- TESTE 1: Posse Exclusiva (std::unique_ptr) ---" << UI::RESET << endl;
    
    // unique_ptr: Proprietário ÚNICO. Perfeito para hardware dedicado.
    auto gpsPrivado = make_unique<ModuloGPS>("TRUCK-777");
    
    gpsPrivado->atualizarCoordenadas(-23.123, -46.987);
    gpsPrivado->mostrarStatus();

    cout << UI::AMARELO << "[RAII]: O caminhão 777 sai de escopo e limpa sua própria RAM..." << UI::RESET << endl;
}

/**
 * @brief Demonstra a posse compartilhada via shared_ptr.
 */
void simularControleCompartilhado() {
    cout << UI::NEGRITO << "\n--- TESTE 2: Posse Compartilhada (std::shared_ptr) ---" << UI::RESET << endl;
    
    shared_ptr<ModuloGPS> terminalDiretoria;

    {
        cout << "[SISTEMA]: Inicializando GPS na central de triagem..." << endl;
        auto gpsSetorial = make_shared<ModuloGPS>("SECTOR-GLOBAL");
        
        // COMPARTILHAMENTO: A diretoria agora também observa este GPS
        terminalDiretoria = gpsSetorial; 
        
        cout << UI::BRANCO << " >> Contagem de donos: " << UI::NEGRITO << terminalDiretoria.use_count() << UI::RESET << endl;
        cout << "[SISTEMA]: Central de triagem encerrando turno (gpsSetorial morre)..." << endl;
    } 

    cout << UI::VERDE << "[CONTENÇÃO]: O GPS continua na RAM pois a diretoria ainda o usa!" << UI::RESET << endl;
    cout << UI::BRANCO << " >> Contagem de donos: " << UI::NEGRITO << terminalDiretoria.use_count() << UI::RESET << endl;
    terminalDiretoria->mostrarStatus();
}

int main() {
    UI::limparTela();
    
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-TRACK: TELEMETRIA AUTOMATIZADA v2.0    " << endl;
    cout << "       (Elite Smart Pointer Infrastructure)    " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    simularFrotaExclusiva();
    
    simularControleCompartilhado();

    cout << "\n" << UI::VERDE << UI::NEGRITO << "Logística de memória validada." << UI::RESET << endl;
    cout << "Todos os recursos foram purgados deterministicamente." << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SMART POINTERS (ELITE STANDARD)
    ===============================================================

    1. O FIM DO NEW/DELETE:
       - No C++ moderno, gerenciar memória manualmente é como 
         pilotar sem cinto de segurança. Smart Pointers transformam 
         o C++ em uma linguagem com segurança de memória nativa, sem 
         precisar de um Garbage Collector lento.

    2. std::unique_ptr (O Padrão):
       - É o substituto ideal para o ponteiro comum. Ele tem custo 
         ZERO de performance (Zero-overhead Abstraction). Ele é o 
         dono exclusivo e garante que a RAM seja limpa assim que 
         ele sair de cena.

    3. std::shared_ptr (O Observador):
       - Usa um 'Control Block' com um contador atômico. É útil para 
         objetos acessados por múltiplos sistemas (ex: um banco de 
         dados ou sensor global). O objeto só é deletado quando o 
         ÚLTIMO ponteiro sumir.

    4. RESILIÊNCIA FANTASMA:
       - Ao passar smart pointers para funções, prefira passar por 
         Referência Constante (const shared_ptr&) se você não for 
         compartilhar a posse. Isso evita que o contador atômico 
         seja incrementado/decrementado à toa, poupando CPU.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - std::weak_ptr: Para quebrar ciclos de shared_ptr.
    - Custom Deleters: Fechar arquivos ou sockets via Smart Pointers.
    - Move Semantics (std::move): Transferir a alma de um unique_ptr.
    ===============================================================
*/
