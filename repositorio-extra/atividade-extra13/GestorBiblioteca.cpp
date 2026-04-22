/**
 * @file GestorBiblioteca.cpp
 * @brief Implementação da lógica de gestão da biblioteca.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "GestorBiblioteca.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

void GestorBiblioteca::carregarCatalogo() {
    ifstream arquivo("repositorio-extra/atividade-extra13/catalogo.txt");
    if (!arquivo.is_open()) arquivo.open("catalogo.txt");

    if (!arquivo.is_open()) {
        throw ErroArquivo("catalogo.txt");
    }

    string linha;
    while (getline(arquivo, linha)) {
        try {
            size_t pos1 = linha.find(';');
            size_t pos2 = linha.find(';', pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos) {
                Livro l;
                l.titulo = linha.substr(0, pos1);
                l.autor = linha.substr(pos1 + 1, pos2 - pos1 - 1);
                l.estoque = stoi(linha.substr(pos2 + 1));
                l.id = catalogo.size();
                catalogo.push_back(l);
            }
        } catch (...) {
            continue; 
        }
    }
    arquivo.close();
    cout << UI::CYAN << "[SISTEMA]: " << UI::RESET << "Catálogo carregado com sucesso." << endl;
}

void GestorBiblioteca::salvarRelatorio() {
    ofstream rel("repositorio-extra/atividade-extra13/relatorio_sessao.txt", ios::trunc);
    if (!rel.is_open()) rel.open("relatorio_sessao.txt", ios::trunc);

    if (!rel.is_open()) {
        throw ErroArquivo("relatorio_sessao.txt");
    }

    rel << "--- RELATÓRIO DE SESSÃO ---\n";
    rel << "Data: " << formatarData(time(0)) << "\n\n";
    
    stack<Emprestimo> temp = historico;
    while (!temp.empty()) {
        Emprestimo e = temp.top();
        rel << "Leitor: " << e.leitor << " | Livro: " << e.livro.titulo << "\n";
        temp.pop();
    }
    rel.close();
    cout << UI::CYAN << "[SISTEMA]: " << UI::RESET << "Relatório final gerado com sucesso." << endl;
}

void GestorBiblioteca::adicionarLeitor(const string& nome) {
    if (nome.empty()) throw ErroBiblioteca("Nome do leitor não pode ser vazio.");
    filaLeitores.push(nome);
    cout << UI::GREEN << "[OK]: " << UI::RESET << nome << " entrou na fila." << endl;
}

void GestorBiblioteca::registrarEmprestimo(int index) {
    if (index < 0 || index >= (int)catalogo.size()) {
        throw ErroBiblioteca("Índice fora do alcance do catálogo.");
    }

    if (catalogo[index].estoque <= 0) {
        throw ErroEstoque(catalogo[index].titulo);
    }

    string leitorAtual = filaLeitores.front();
    filaLeitores.pop();

    Emprestimo emp;
    emp.leitor = leitorAtual;
    emp.livro = catalogo[index];
    emp.indexCatalogo = index;

    time_t agora = time(0);
    time_t dev = agora + (7 * 24 * 60 * 60); 
    
    emp.dataEmp = formatarData(agora);
    emp.dataDev = formatarData(dev);

    catalogo[index].estoque--;
    historico.push(emp);
    
    cout << UI::GREEN << "[SUCESSO]: " << UI::RESET << "Empréstimo de '" << emp.livro.titulo << "' registrado!" << endl;
}

void GestorBiblioteca::cancelarUltimoEmprestimo() {
    if (historico.empty()) {
        throw ErroBiblioteca("Não há empréstimos para cancelar.");
    }
    Emprestimo ultimo = historico.top();
    catalogo[ultimo.indexCatalogo].estoque++;
    cout << UI::YELLOW << "[DESFEITO]: " << UI::RESET << "Livro '" << ultimo.livro.titulo << "' voltou ao estoque." << endl;
    historico.pop();
}

const string& GestorBiblioteca::getProximoLeitor() const {
    if (filaLeitores.empty()) {
        throw ErroBiblioteca("Fila vazia.");
    }
    return filaLeitores.front();
}

int GestorBiblioteca::lerInteiro(const string& prompt) {
    int valor;
    cout << prompt;
    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw ErroEntrada();
    }
    return valor;
}

void GestorBiblioteca::exibirBanner() {
    cout << "===============================================" << endl;
    cout << "      SISTEMA DE GESTÃO - ATIVIDADE 13         " << endl;
    cout << "      (Arquitetura Modular Refatorada)         " << endl;
    cout << "===============================================" << endl;
}
