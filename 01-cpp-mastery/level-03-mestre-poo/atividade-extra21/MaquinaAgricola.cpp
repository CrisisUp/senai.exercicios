#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file MaquinaAgricola.cpp
 * @brief Implementação das classes MaquinaAgricola e Trator.
 */

#include "MaquinaAgricola.h"
#include <iomanip>

using namespace std;

// --- Implementação MaquinaAgricola ---

MaquinaAgricola::MaquinaAgricola(const string& _id, const string& _marca) 
    : id(_id), marca(_marca), combustivel(50.0) {}

void MaquinaAgricola::abastecer() {
    combustivel = 100.0;
    cout << UI::VERDE << "[SISTEMA]: Máquina " << UI::NEGRITO << id << UI::RESET 
         << UI::VERDE << " totalmente abastecida (BioDiesel 100%)." << UI::RESET << endl;
}

void MaquinaAgricola::exibirBase() const {
    cout << UI::RESET << "ID      : " << UI::RESET << UI::CIANO << id << UI::RESET << endl;
    cout << UI::RESET << "MARCA   : " << UI::RESET << marca << endl;
    cout << UI::RESET << "TANQUE  : " << UI::RESET;
    if (combustivel < 20.0) cout << UI::VERMELHO << UI::NEGRITO;
    else cout << UI::VERDE;
    cout << combustivel << "%" << UI::RESET << endl;
}

// --- Implementação Trator ---

Trator::Trator(const string& _id, const string& _marca, double _cap) 
    : MaquinaAgricola(_id, _marca), capacidadeReboque(_cap) {}

void Trator::ararTerra() {
    if (combustivel >= 15.0) {
        combustivel -= 15.0;
        cout << UI::AMARELO << UI::NEGRITO << "[OPERACIONAL]: Aragem concluída com sucesso (-15% combustível)." << UI::RESET << endl;
    } else {
        cout << UI::VERMELHO << UI::NEGRITO << "[ALERTA CRÍTICO]: Nível de combustível insuficiente para operação pesada!" << UI::RESET << endl;
    }
}

void Trator::exibirStatus() const {
    cout << "\n" << UI::NEGRITO << "--- TELEMETRIA DO MAQUINÁRIO ---" << UI::RESET << endl;
    exibirBase();
    cout << UI::RESET << "REBOQUE : " << UI::RESET << capacidadeReboque << " Toneladas" << endl;
    cout << UI::NEGRITO << "--------------------------------" << UI::RESET << endl;
}

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
