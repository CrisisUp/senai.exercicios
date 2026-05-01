#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Reserva.cpp
 * @brief Implementação da gestora da reserva.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Reserva.h"
#include <iostream>
#include <iomanip>

using namespace std;

Reserva::Reserva() : ciclo(0) {}

void Reserva::adicionar(SerVivo* s) { biota.push_back(s); }

void Reserva::evoluir() {
    ciclo++;
    cout << "\n" << UI::NEGRITO << ">>> PROCESSANDO CICLO VITAL #" << ciclo << UI::RESET << endl;
    
    for (auto s : biota) {
        if (s && s->isVivo()) s->agir();
    }
}

void Reserva::dashboard() const {
    cout << "\n" << UI::CIANO << UI::NEGRITO << "--- STATUS DA BIODIVERSIDADE ---" << UI::RESET << endl;
    cout << left << setw(15) << "NOME" << setw(12) << "ESPÉCIE" << setw(10) << "ENERGIA" << "VITALIDADE" << endl;
    cout << string(52, '-') << endl;
    
    for (const auto& s : biota) {
        if (s) {
            cout << left << setw(15) << s->getNome() 
                 << setw(12) << s->getEspecie() 
                 << setw(10) << s->getEnergia();
            if (s->isVivo()) cout << UI::VERDE << "ATIVO" << UI::RESET;
            else cout << UI::VERMELHO << "EXTINTO" << UI::RESET;
            cout << endl;
        }
    }
    cout << "\nPOPULAÇÃO ATIVA: " << UI::VERDE << SerVivo::getPopulacao() << UI::RESET << endl;
}

Reserva::~Reserva() { 
    for (auto s : biota) delete s; 
    biota.clear();
}

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
