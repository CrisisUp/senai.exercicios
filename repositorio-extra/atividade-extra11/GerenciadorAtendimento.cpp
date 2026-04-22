/**
 * @file GerenciadorAtendimento.cpp
 * @brief Implementação dos métodos da classe GerenciadorAtendimento.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 24/04/2026
 */

#include "GerenciadorAtendimento.h"
#include <iostream>
#include <fstream>

using namespace std;

void GerenciadorAtendimento::carregarPacientes(const string& caminhoArquivo) {
    ifstream arquivo;
    string nome;
    
    cout << "\n" << UI::CYAN << "[SISTEMA]: " << UI::RESET << "Carregando lista de espera de: " << caminhoArquivo << "..." << endl;
    
    arquivo.open(caminhoArquivo);

    if (arquivo.is_open()) {
        while (getline(arquivo, nome)) {
            if (!nome.empty()) {
                filaAtendimento.push(nome);
            }
        }
        arquivo.close();
        cout << UI::GREEN << "[SUCESSO]: " << UI::RESET << "Lista carregada com sucesso!" << endl;
    } else {
        throw ArquivoCorrompidoException();
    }
}

void GerenciadorAtendimento::adicionarPaciente(const string& nome) {
    filaAtendimento.push(nome);
    cout << UI::GREEN << "[OK]: " << UI::RESET << nome << " entrou no final da fila." << endl;
}

string GerenciadorAtendimento::atenderProximo() {
    if (filaAtendimento.empty()) {
        throw FilaVaziaException();
    }
    
    string atendido = filaAtendimento.front();
    filaAtendimento.pop();
    return atendido;
}

const string& GerenciadorAtendimento::verProximo() const {
    if (filaAtendimento.empty()) {
        throw FilaVaziaException();
    }
    return filaAtendimento.front();
}

size_t GerenciadorAtendimento::totalFila() const {
    return filaAtendimento.size();
}

void GerenciadorAtendimento::exibirBanner() {
    cout << "===============================================" << endl;
    cout << "       SISTEMA DE TRIAGEM - CLÍNICA SENAI      " << endl;
    cout << "===============================================" << endl;
}
