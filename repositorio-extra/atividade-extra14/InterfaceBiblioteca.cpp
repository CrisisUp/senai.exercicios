/**
 * @file InterfaceBiblioteca.cpp
 * @brief Implementação da gestão de biblioteca com interface ANSI.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "InterfaceBiblioteca.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

void GestorEstilizado::carregarCatalogo() {
    ifstream arquivo("repositorio-extra/atividade-extra14/catalogo.txt");
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
    cout << Cor::VERDE << "[SISTEMA]: Catálogo colorido carregado com sucesso." << Cor::RESET << endl;
}

void GestorEstilizado::salvarRelatorio() {
    ofstream rel("repositorio-extra/atividade-extra14/relatorio_final.txt", ios::trunc);
    if (!rel.is_open()) rel.open("relatorio_final.txt", ios::trunc);

    if (!rel.is_open()) {
        throw ErroArquivo("relatorio_final.txt");
    }

    rel << "--- RELATÓRIO DE SESSÃO ESTILIZADA ---\n";
    rel << "Data: " << formatarData(time(0)) << "\n\n";
    
    stack<Emprestimo> temp = historico;
    while (!temp.empty()) {
        Emprestimo e = temp.top();
        rel << "Leitor: " << e.leitor << " | Livro: " << e.livro.titulo << "\n";
        temp.pop();
    }
    rel.close();
    cout << Cor::VERDE << "[SISTEMA]: Relatório gerado com sucesso." << Cor::RESET << endl;
}

void GestorEstilizado::adicionarLeitor(string nome) {
    if (nome.empty()) throw ErroBiblioteca(Cor::AMARELO + "[AVISO]: Nome do leitor vazio." + Cor::RESET);
    filaLeitores.push(nome);
    cout << Cor::VERDE << "[OK]: " << nome << " entrou na fila." << Cor::RESET << endl;
}

void GestorEstilizado::atenderLeitor(int index) {
    if (index < 0 || index >= (int)catalogo.size()) {
        throw ErroBiblioteca(Cor::VERMELHO + "[ERRO]: Índice de livro inválido." + Cor::RESET);
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
    
    cout << Cor::VERDE << "[SUCESSO]: Empréstimo de '" << emp.livro.titulo << "' registrado!" << Cor::RESET << endl;
}

void GestorEstilizado::desfazerUltimo() {
    if (historico.empty()) {
        throw ErroBiblioteca(Cor::AMARELO + "[AVISO]: Nenhum empréstimo para desfazer." + Cor::RESET);
    }
    Emprestimo ultimo = historico.top();
    catalogo[ultimo.indexCatalogo].estoque++;
    cout << Cor::AMARELO << "[DESFEITO]: Livro '" << ultimo.livro.titulo << "' voltou ao estoque." << Cor::RESET << endl;
    historico.pop();
}

string GestorEstilizado::formatarData(time_t t) {
    char buffer[20];
    struct tm * timeinfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}

int GestorEstilizado::lerInteiro(string prompt) {
    int valor;
    cout << prompt;
    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw ErroEntrada();
    }
    return valor;
}

void GestorEstilizado::exibirBanner() {
    cout << Cor::CIANO << "===============================================" << Cor::RESET << endl;
    cout << Cor::CIANO << Cor::NEGRITO << "      BIBLIOTECA DIGITAL v2.0 (ANSI UI)        " << Cor::RESET << endl;
    cout << Cor::CIANO << "      (Arquitetura Modular Refatorada)         " << Cor::RESET << endl;
    cout << Cor::CIANO << "===============================================" << Cor::RESET << endl;
}
