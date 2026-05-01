#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file Aeronave.cpp
 * @brief Implementação das classes Aeronave, AviaoComercial e Helicoptero.
 */

#include "Aeronave.h"

using namespace std;

// --- Implementação Aeronave ---

Aeronave::Aeronave(const string& _pref) : prefixo(_pref) {}

Aeronave::~Aeronave() {
    cout << UI::AMARELO << "[LIMPEZA]: Memória do Prefixo " << prefixo << " liberada." << UI::RESET << endl;
}

void Aeronave::prepararParaDecolagem() {
    cout << UI::RESET << "[Aeronave " << prefixo << "]: " << UI::RESET << "Check-list de aviônica completo." << endl;
}

void Aeronave::decolar() {
    cout << "[Aeronave " << prefixo << "]: Procedimento genérico de decolagem." << endl;
}

// --- Implementação AviaoComercial ---

AviaoComercial::AviaoComercial(const string& _pref) : Aeronave(_pref) {}

void AviaoComercial::decolar() {
    cout << UI::VERDE << UI::NEGRITO << "[ASA FIXA " << prefixo << "]: " << UI::RESET 
         << UI::VERDE << "V1... VR... Decolagem de pista concluída!" << UI::RESET << endl;
}

// --- Implementação Helicoptero ---

Helicoptero::Helicoptero(const string& _pref) : Aeronave(_pref) {}

void Helicoptero::decolar() {
    cout << UI::AZUL << UI::NEGRITO << "[ASA ROTATIVA " << prefixo << "]: " << UI::RESET 
         << UI::AZUL << "Passo coletivo aumentado... Decolagem Vertical concluída!" << UI::RESET << endl;
}

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
