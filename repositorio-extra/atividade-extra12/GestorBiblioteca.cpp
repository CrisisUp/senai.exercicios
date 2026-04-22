/**
 * @file GestorBiblioteca.cpp
 * @brief Implementação dos métodos da classe GestorBiblioteca.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 24/04/2026
 */

#include "GestorBiblioteca.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

void GestorBiblioteca::carregarCatalogo(const string& caminho) {
    ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        throw ErroArquivo(caminho);
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
    cout << "[SISTEMA]: " << catalogo.size() << " títulos carregados." << endl;
}

void GestorBiblioteca::adicionarLeitor(const string& nome) {
    filaLeitores.push(nome);
    cout << "[OK]: " << nome << " entrou na fila." << endl;
}

void GestorBiblioteca::realizarEmprestimo(int index) {
    if (filaLeitores.empty()) {
        throw ErroBiblioteca("Fila de atendimento vazia.");
    }
    
    if (index >= 0 && index < (int)catalogo.size()) {
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
        
        cout << "[SUCESSO]: Empréstimo de '" << emp.livro.titulo << "' registrado!" << endl;
    } else {
        throw ErroBiblioteca("Índice de livro inexistente.");
    }
}

void GestorBiblioteca::desfazerEmprestimo() {
    if (historico.empty()) {
        throw ErroBiblioteca("Nenhum empréstimo para desfazer.");
    }
    Emprestimo ultimo = historico.top();
    catalogo[ultimo.indexCatalogo].estoque++;
    cout << "[DESFEITO]: Livro '" << ultimo.livro.titulo << "' voltou ao estoque." << endl;
    historico.pop();
}

void GestorBiblioteca::salvarRelatorio(const string& caminho) {
    ofstream rel(caminho, ios::trunc);

    if (!rel.is_open()) {
        throw ErroArquivo(caminho);
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
    cout << "[SISTEMA]: Relatório gerado com segurança em " << caminho << endl;
}

void GestorBiblioteca::exibirBanner() {
    cout << "===============================================" << endl;
    cout << "      GESTÃO BIBLIOTECÁRIA INTEGRADA v1.2      " << endl;
    cout << "      (Módulo de Segurança e Exceções)         " << endl;
    cout << "===============================================" << endl;
}

string GestorBiblioteca::formatarData(time_t t) {
    char buffer[20];
    struct tm * timeinfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}
