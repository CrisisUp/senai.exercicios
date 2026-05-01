/**
 * @file main.cpp
 * @brief Programa principal para análise empírica da VTable e VPTR.
 * @author Gemini CLI
 * @date 30/04/2026
 * 
 * @section MemoryMap
 * - Stack: Instâncias 'vazia', 'comVirtual' e ponteiro 'base'.
 * - Heap: Instância de 'FilhaVirtual' alocada via new.
 * - Segmento de Dados/Texto: VTables das classes 'ComVirtual' e 'FilhaVirtual'.
 */

#include "VTableInternals.h"
#include <iostream>
#include <iomanip>

// Cores ANSI para UX profissional
#define RESET   "\033[0m"
#define BOLDCYAN "\033[1m\033[36m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDRED "\033[1m\033[31m"

void imprimirCabecalho() {
    std::cout << BOLDCYAN << "====================================================" << RESET << std::endl;
    std::cout << BOLDCYAN << "   ANALISADOR DE MEMÓRIA: MISTÉRIOS DA VTABLE       " << RESET << std::endl;
    std::cout << BOLDCYAN << "====================================================" << RESET << std::endl;
}

int main() {
    imprimirCabecalho();

    Vazia vazia;
    ComVirtual comVirtual;

    std::cout << BOLDYELLOW << "\n[1] Comparação de sizeof (Overhead do Polimorfismo)" << RESET << std::endl;
    std::cout << "Tamanho da classe Vazia:      " << BOLDGREEN << sizeof(vazia) << " byte(s)" << RESET << std::endl;
    std::cout << "Tamanho da classe ComVirtual: " << BOLDGREEN << sizeof(comVirtual) << " byte(s)" << RESET << std::endl;
    
    std::cout << "\nObservação: O aumento de " << sizeof(comVirtual) - sizeof(vazia) 
              << " bytes deve-se ao " << BOLDRED << "VPTR (Virtual Pointer)" << RESET << "." << std::endl;

    std::cout << BOLDYELLOW << "\n[2] Importância do Destrutor Virtual" << RESET << std::endl;
    std::cout << "Deletando uma FilhaVirtual através de um ponteiro da Base..." << std::endl;
    
    ComVirtual* base = new FilhaVirtual();
    delete base; // Se o destrutor da base não fosse virtual, o da filha nunca seria chamado.

    std::cout << BOLDCYAN << "\n====================================================" << RESET << std::endl;
    std::cout << BOLDYELLOW << "RESUMO TEÓRICO:" << RESET << std::endl;
    std::cout << "1. O que acontece se eu esquecer o 'virtual' no destrutor base?" << std::endl;
    std::cout << "   " << BOLDRED << "FALHA CRÍTICA:" << RESET << " Se o destrutor da classe base não for virtual, ao" << std::endl;
    std::cout << "   deletar um objeto da classe filha através de um ponteiro da classe" << std::endl;
    std::cout << "   base, apenas o destrutor da base será chamado. Isso causa um" << std::endl;
    std::cout << "   " << BOLDRED << "Memory Leak" << RESET << " se a classe filha tiver alocado recursos na Heap." << std::endl;
    std::cout << "\n2. Como a VTable resolve isso?" << std::endl;
    std::cout << "   O VPTR aponta para a VTable da classe REAL do objeto. Se o destrutor" << std::endl;
    std::cout << "   é virtual, ele está na VTable. O compilador então busca o endereço" << std::endl;
    std::cout << "   do destrutor correto em tempo de execução." << std::endl;
    std::cout << BOLDCYAN << "====================================================" << RESET << std::endl;

    return 0;
}
