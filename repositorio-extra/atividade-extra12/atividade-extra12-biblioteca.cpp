/**
 * @file atividade-extra12-biblioteca.cpp
 * @brief DESAFIO DE FASE: Sistema Integrado de Gestão Bibliotecária.
 * 
 * Versão 1.2: Implementação de Tratamento de Exceções e Robustez.
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

// --- 1. CLASSES DE EXCEÇÃO CUSTOMIZADAS ---

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
    ErroArquivo(string arquivo) : ErroBiblioteca("[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado ou ilegível.") {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca("[AVISO]: Entrada inválida. Digite apenas números.") {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(string titulo) : ErroBiblioteca("[ESTOQUE]: O livro '" + titulo + "' não está disponível.") {}
};

// --- 2. ESTRUTURAS DE DADOS ---

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

// --- 3. PROTÓTIPOS DAS FUNÇÕES ---

void exibirBanner();
void carregarCatalogo(vector<Livro> &catalogo);
string formatarData(time_t t);
void salvarRelatorio(stack<Emprestimo> s);
int lerInteiro(string prompt);

// --- 4. FUNÇÃO PRINCIPAL ---

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
            throw ErroBiblioteca("O catálogo está vazio. Impossível iniciar sistema.");
        }

        do {
            cout << "\n--- PAINEL DE CONTROLE ---" << endl;
            cout << "Leitores na Fila: " << filaLeitores.size() << " | ";
            cout << "Empréstimos na Sessão: " << historico.size() << endl;
            cout << "[1] Adicionar Leitor à Fila" << endl;
            cout << "[2] Atender Próximo Leitor (Empréstimo)" << endl;
            cout << "[3] Cancelar Último Empréstimo (DESFAZER)" << endl;
            cout << "[4] Salvar e Encerrar Expediente" << endl;
            
            try {
                opcao = lerInteiro("Escolha: ");

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    filaLeitores.push(nome);
                    cout << "[OK]: " << nome << " entrou na fila." << endl;
                }
                else if (opcao == 2) {
                    if (filaLeitores.empty()) {
                        cout << "[AVISO]: Fila de atendimento vazia." << endl;
                    } else {
                        string leitorAtual = filaLeitores.front();
                        
                        cout << "\n--- LIVROS DISPONÍVEIS ---" << endl;
                        cout << left << setw(4) << "ID" << setw(30) << "TÍTULO" << "ESTOQUE" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        for (int i = 0; i < (int)catalogo.size(); i++) {
                            cout << left << "[" << i << "] " 
                                 << setw(30) << (catalogo[i].titulo.length() > 28 ? catalogo[i].titulo.substr(0, 25) + "..." : catalogo[i].titulo)
                                 << (catalogo[i].estoque > 0 ? to_string(catalogo[i].estoque) : "ESGOTADO") << endl;
                        }
                        
                        int index = lerInteiro("\nEscolha o índice do livro para " + leitorAtual + " (ou -1 para cancelar): ");

                        if (index == -1) {
                            cout << "[AVISO]: Atendimento cancelado." << endl;
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
                            
                            cout << "[SUCESSO]: Empréstimo de '" << emp.livro.titulo << "' registrado!" << endl;
                        } else {
                            throw ErroBiblioteca("Índice de livro inexistente.");
                        }
                    }
                }
                else if (opcao == 3) {
                    if (historico.empty()) {
                        throw ErroBiblioteca("Nenhum empréstimo para desfazer.");
                    }
                    Emprestimo ultimo = historico.top();
                    catalogo[ultimo.indexCatalogo].estoque++;
                    cout << "[DESFEITO]: Livro '" << ultimo.livro.titulo << "' voltou ao estoque." << endl;
                    historico.pop();
                }
                else if (opcao != 4) {
                    cout << "[AVISO]: Opção inválida." << endl;
                }

            } catch (const ErroBiblioteca& e) {
                // Captura erros específicos da biblioteca sem encerrar o programa
                cout << e.what() << endl;
            }

        } while (opcao != 4);

        salvarRelatorio(historico);

    } catch (const exception& e) {
        // Captura erros fatais e encerra com segurança
        cerr << "\nFATAL: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// --- 5. IMPLEMENTAÇÃO DAS FUNÇÕES ---

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "      GESTÃO BIBLIOTECÁRIA INTEGRADA v1.2      " << endl;
    cout << "      (Módulo de Segurança e Exceções)         " << endl;
    cout << "===============================================" << endl;
}

/**
 * @brief Lê um inteiro do teclado com proteção contra caracteres.
 */
int lerInteiro(string prompt) {
    int valor;
    cout << prompt;
    while (!(cin >> valor)) {
        cin.clear(); // Limpa estado de erro
        cin.ignore(1000, '\n'); // Descarta caracteres inválidos
        throw ErroEntrada();
    }
    return valor;
}

void carregarCatalogo(vector<Livro> &catalogo) 
{
    ifstream arquivo("repositorio-extra/atividade-extra12/catalogo.txt");
    if (!arquivo.is_open()) {
        arquivo.open("catalogo.txt");
    }

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
            // Se uma linha estiver corrompida, ignora e pula para a próxima
            continue;
        }
    }
    arquivo.close();
    cout << "[SISTEMA]: " << catalogo.size() << " títulos carregados." << endl;
}

string formatarData(time_t t) {
    char buffer[20];
    struct tm * timeinfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}

void salvarRelatorio(stack<Emprestimo> s) {
    ofstream rel("repositorio-extra/atividade-extra12/relatorio_dia.txt", ios::trunc);
    if (!rel.is_open()) rel.open("relatorio_dia.txt", ios::trunc);

    if (!rel.is_open()) {
        throw ErroArquivo("relatorio_dia.txt");
    }

    rel << "--- RELATÓRIO DE SESSÃO ---\n";
    rel << "Data: " << formatarData(time(0)) << "\n\n";
    
    while (!s.empty()) {
        Emprestimo e = s.top();
        rel << "Leitor: " << e.leitor << " | Livro: " << e.livro.titulo << "\n";
        s.pop();
    }
    rel.close();
    cout << "[SISTEMA]: Relatório gerado com segurança." << endl;
}
