/**
 * @file atividade-extra14-estilos.cpp
 * @brief ATIVIDADE 14: Estilo Visual e Cores ANSI no Terminal.
 * 
 * Este programa demonstra como colorir e estilizar uma aplicação CLI:
 * 1. Namespace Cor para organização de constantes de escape.
 * 2. Banner estilizado com cores.
 * 3. Feedback visual em Exceções e Mensagens de Sucesso.
 * 4. Destaque de estoque (Vermelho para Esgotado).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE CORES (ANSI ESCAPE CODES) ---

namespace Cor {
    const string RESET   = "\033[0m";
    const string NEGRITO = "\033[1m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";
}

// --- 2. CLASSES DE EXCEÇÃO CUSTOMIZADAS ---

class ErroBiblioteca : public exception {
protected:
    string mensagem;
public:
    ErroBiblioteca(string msg) : mensagem(msg) {}
    virtual const char* what() const throw() {
        return mensagem.c_str();
    }
};

class ErroArquivo : public ErroBiblioteca {
public:
    ErroArquivo(string arquivo) : ErroBiblioteca(Cor::VERMELHO + "[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado." + Cor::RESET) {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca(Cor::AMARELO + "[AVISO]: Entrada inválida. Digite apenas números." + Cor::RESET) {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(string titulo) : ErroBiblioteca(Cor::VERMELHO + "[ESTOQUE]: O livro '" + titulo + "' esgotou." + Cor::RESET) {}
};

// --- 3. ESTRUTURAS DE DADOS ---

struct Livro {
    string titulo;
    string autor;
    int estoque;
    int id;
};

struct Emprestimo {
    string leitor;
    Livro livro;
    string dataEmp;
    string dataDev;
    int indexCatalogo;
};

// --- 4. PROTÓTIPOS DAS FUNÇÕES ---

void exibirBanner();
void carregarCatalogo(vector<Livro> &catalogo);
string formatarData(time_t t);
void salvarRelatorio(stack<Emprestimo> s);
int lerInteiro(string prompt);

// --- 5. FUNÇÃO PRINCIPAL ---

int main()
{
    vector<Livro> catalogo;
    queue<string> filaLeitores;
    stack<Emprestimo> historico;
    int opcao = 0;

    exibirBanner();

    try {
        carregarCatalogo(catalogo);

        if (catalogo.empty()) {
            throw ErroBiblioteca(Cor::VERMELHO + "Catálogo vazio. Sistema encerrado." + Cor::RESET);
        }

        do {
            cout << "\n" << Cor::CIANO << Cor::NEGRITO << "--- PAINEL DE CONTROLE (BIBLIOTECA COLORIDA) ---" << Cor::RESET << endl;
            cout << "Leitores na Fila: " << Cor::AZUL << filaLeitores.size() << Cor::RESET << " | ";
            cout << "Empréstimos na Sessão: " << Cor::VERDE << historico.size() << Cor::RESET << endl;
            cout << Cor::BRANCO << "[1] Adicionar Leitor à Fila" << endl;
            cout << "[2] Atender Próximo Leitor (Empréstimo)" << endl;
            cout << "[3] Cancelar Último Empréstimo (DESFAZER)" << endl;
            cout << "[4] Salvar e Encerrar Expediente" << Cor::RESET << endl;
            
            try {
                opcao = lerInteiro(Cor::NEGRITO + "Escolha: " + Cor::RESET);

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    filaLeitores.push(nome);
                    cout << Cor::VERDE << "[OK]: " << nome << " entrou na fila." << Cor::RESET << endl;
                }
                else if (opcao == 2) {
                    if (filaLeitores.empty()) {
                        cout << Cor::AMARELO << "[AVISO]: Fila vazia." << Cor::RESET << endl;
                    } else {
                        string leitorAtual = filaLeitores.front();
                        
                        cout << "\n" << Cor::NEGRITO << "--- LIVROS DISPONÍVEIS ---" << Cor::RESET << endl;
                        cout << left << setw(4) << "ID" << setw(30) << "TÍTULO" << "ESTOQUE" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        for (int i = 0; i < (int)catalogo.size(); i++) {
                            cout << left << "[" << i << "] " 
                                 << setw(30) << (catalogo[i].titulo.length() > 28 ? catalogo[i].titulo.substr(0, 25) + "..." : catalogo[i].titulo);
                            
                            if (catalogo[i].estoque <= 0) {
                                cout << Cor::VERMELHO << "ESGOTADO" << Cor::RESET << endl;
                            } else {
                                cout << Cor::VERDE << catalogo[i].estoque << Cor::RESET << endl;
                            }
                        }
                        
                        int index = lerInteiro("\nÍndice para " + Cor::NEGRITO + leitorAtual + Cor::RESET + " (ou -1): ");

                        if (index == -1) {
                            cout << Cor::AMARELO << "[AVISO]: Cancelado." << Cor::RESET << endl;
                        } else if (index >= 0 && index < (int)catalogo.size()) {
                            if (catalogo[index].estoque <= 0) {
                                throw ErroEstoque(catalogo[index].titulo);
                            }

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
                        } else {
                            throw ErroBiblioteca(Cor::VERMELHO + "Índice inválido." + Cor::RESET);
                        }
                    }
                }
                else if (opcao == 3) {
                    if (historico.empty()) {
                        throw ErroBiblioteca(Cor::AMARELO + "Nada para desfazer." + Cor::RESET);
                    }
                    Emprestimo ultimo = historico.top();
                    catalogo[ultimo.indexCatalogo].estoque++;
                    cout << Cor::AMARELO << "[DESFEITO]: Livro '" << ultimo.livro.titulo << "' voltou ao estoque." << Cor::RESET << endl;
                    historico.pop();
                }
                else if (opcao != 4) {
                    cout << Cor::AMARELO << "[AVISO]: Opção inválida." << Cor::RESET << endl;
                }

            } catch (const ErroBiblioteca& e) {
                cout << e.what() << endl;
            }

        } while (opcao != 4);

        salvarRelatorio(historico);

    } catch (const exception& e) {
        cerr << "\n" << Cor::VERMELHO << Cor::NEGRITO << "FALHA CRÍTICA: " << e.what() << Cor::RESET << endl;
        return 1;
    }

    return 0;
}

// --- 6. IMPLEMENTAÇÃO DAS FUNÇÕES ---

void exibirBanner() {
    cout << Cor::CIANO << "===============================================" << Cor::RESET << endl;
    cout << Cor::CIANO << Cor::NEGRITO << "      BIBLIOTECA DIGITAL v2.0 (ANSI UI)        " << Cor::RESET << endl;
    cout << Cor::CIANO << "      (Módulo de Interface e Estilos)          " << Cor::RESET << endl;
    cout << Cor::CIANO << "===============================================" << Cor::RESET << endl;
}

int lerInteiro(string prompt) {
    int valor;
    cout << prompt;
    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw ErroEntrada();
    }
    return valor;
}

void carregarCatalogo(vector<Livro> &catalogo) 
{
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
    cout << Cor::VERDE << "[SISTEMA]: Catálogo colorido carregado." << Cor::RESET << endl;
}

string formatarData(time_t t) {
    char buffer[20];
    struct tm * timeinfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}

void salvarRelatorio(stack<Emprestimo> s) {
    ofstream rel("repositorio-extra/atividade-extra14/relatorio_final.txt", ios::trunc);
    if (!rel.is_open()) rel.open("relatorio_final.txt", ios::trunc);

    if (!rel.is_open()) {
        throw ErroArquivo("relatorio_final.txt");
    }

    rel << "--- RELATÓRIO DE SESSÃO ESTILIZADA ---\n";
    rel << "Data: " << formatarData(time(0)) << "\n\n";
    
    while (!s.empty()) {
        Emprestimo e = s.top();
        rel << "Leitor: " << e.leitor << " | Livro: " << e.livro.titulo << "\n";
        s.pop();
    }
    rel.close();
    cout << Cor::VERDE << "[SISTEMA]: Relatório gerado com sucesso." << Cor::RESET << endl;
}
