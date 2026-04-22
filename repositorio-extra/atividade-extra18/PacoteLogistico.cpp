/**
 * @file PacoteLogistico.cpp
 * @brief Implementação dos métodos da classe PacoteLogistico.
 * 
 * Demonstra a separação entre interface e implementação.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "PacoteLogistico.h"
#include <iomanip>

using namespace std;

// --- CONSTRUTOR 1 (COMPLETO) ---
PacoteLogistico::PacoteLogistico(string cod, double p, string dest) 
    : codigoRastreio(cod), peso(p), destino(dest) 
{
    cout << UI::VERDE << "[SISTEMA]: Pacote COMPLETO registrado via Scanner." << UI::RESET << endl;
}

// --- CONSTRUTOR 2 (PARCIAL) ---
PacoteLogistico::PacoteLogistico(string cod) 
    : codigoRastreio(cod), peso(0.0), destino("A DEFINIR") 
{
    cout << UI::AMARELO << "[SISTEMA]: Pacote PARCIAL registrado via Cadastro Manual." << UI::RESET << endl;
}

// --- SETTERS ---
void PacoteLogistico::setPeso(double p) {
    if (p > 0) {
        peso = p;
        cout << "[OK]: Peso atualizado para " << p << "kg." << endl;
    } else {
        cout << "\033[31m[ERRO]: Peso inválido.\033[0m" << endl;
    }
}

void PacoteLogistico::setDestino(string dest) {
    if (!dest.empty()) {
        destino = dest;
        cout << "[OK]: Destino definido para: " << dest << endl;
    }
}

// --- EXIBIÇÃO ---
void PacoteLogistico::exibirEtiqueta() const {
    cout << "\n" << UI::CIANO << "===============================================" << endl;
    cout << "           ETIQUETA DE TRANSPORTE              " << endl;
    cout << "===============================================" << UI::RESET << endl;
    cout << "RASTREIO: " << UI::AZUL << codigoRastreio << UI::RESET << endl;
    cout << "PESO    : " << (peso > 0 ? to_string(peso) + " kg" : UI::AMARELO + "PENDENTE" + UI::RESET) << endl;
    cout << "DESTINO : " << destino << endl;
    cout << UI::CIANO << "-----------------------------------------------" << UI::RESET << endl;
}
