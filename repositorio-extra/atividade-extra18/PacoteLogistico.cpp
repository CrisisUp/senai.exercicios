/**
 * @file PacoteLogistico.cpp
 * @brief Implementação dos métodos da classe PacoteLogistico.
 * 
 * Demonstra a separação entre interface e implementação e uso de Initializer Lists.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "PacoteLogistico.h"
#include <iomanip>

using namespace std;

/**
 * @brief Construtor 1 (COMPLETO) - Otimizado com Lista de Inicialização.
 */
PacoteLogistico::PacoteLogistico(const string& cod, double p, const string& dest) 
    : codigoRastreio(cod), peso(p), destino(dest) 
{
    cout << UI::VERDE << "[SISTEMA]: Pacote " << UI::NEGRITO << cod 
         << UI::RESET << UI::VERDE << " registrado via Scanner Automático." << UI::RESET << endl;
}

/**
 * @brief Construtor 2 (PARCIAL) - Otimizado com Lista de Inicialização.
 */
PacoteLogistico::PacoteLogistico(const string& cod) 
    : codigoRastreio(cod), peso(0.0), destino("A DEFINIR") 
{
    cout << UI::AMARELO << "[SISTEMA]: Pacote " << UI::NEGRITO << cod 
         << UI::RESET << UI::AMARELO << " registrado via Cadastro Manual." << UI::RESET << endl;
}

/**
 * @brief Setter para Peso com validação física.
 */
bool PacoteLogistico::setPeso(double p) {
    if (p > 0) {
        peso = p;
        cout << UI::VERDE << "[OK]: Peso atualizado para " << p << "kg." << UI::RESET << endl;
        return true;
    } else {
        cout << UI::VERMELHO << "[ERRO]: Peso inválido (" << p << "kg). Operação abortada." << UI::RESET << endl;
        return false;
    }
}

/**
 * @brief Setter para Destino com validação de presença.
 */
bool PacoteLogistico::setDestino(const string& dest) {
    if (!dest.empty()) {
        destino = dest;
        cout << UI::VERDE << "[OK]: Destino definido para: " << UI::NEGRITO << dest << UI::RESET << endl;
        return true;
    }
    return false;
}

/**
 * @brief Gera etiqueta de transporte com feedback visual profissional.
 */
void PacoteLogistico::exibirEtiqueta() const {
    cout << "\n" << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;
    cout << UI::CIANO << UI::NEGRITO << "           ETIQUETA DE TRANSPORTE              " << UI::RESET << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;
    
    cout << UI::BRANCO << "RASTREIO : " << UI::RESET << UI::AZUL << UI::NEGRITO << codigoRastreio << UI::RESET << endl;
    
    cout << UI::BRANCO << "PESO     : " << UI::RESET;
    if (peso > 0) {
        cout << fixed << setprecision(2) << peso << " kg" << endl;
    } else {
        cout << UI::AMARELO << UI::NEGRITO << "AGUARDANDO BALANÇA" << UI::RESET << endl;
    }

    cout << UI::BRANCO << "DESTINO  : " << UI::RESET;
    if (destino == "A DEFINIR") {
        cout << UI::AMARELO << UI::NEGRITO << "PENDENTE" << UI::RESET << endl;
    } else {
        cout << UI::NEGRITO << destino << UI::RESET << endl;
    }

    cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
}
