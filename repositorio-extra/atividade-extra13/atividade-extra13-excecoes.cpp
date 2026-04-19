/**
 * @file atividade-extra13-excecoes.cpp
 * @brief ATIVIDADE 13: Robustez e Tratamento de Exceções.
 * 
 * Este programa demonstra como gerenciar erros de forma profissional:
 * 1. Exceções customizadas herdando de std::exception.
 * 2. Blocos try-catch para recuperação de erros de entrada.
 * 3. Validação de arquivos e estoque com lançamentos (throw).
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
    ErroArquivo(string arquivo) : ErroBiblioteca("[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado.") {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca("[AVISO]: Entrada inválida. Por favor, digite apenas números.") {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(string titulo) : ErroBiblioteca("[ESTOQUE]: O livro '" + titulo + "' esgotou. Escolha outro.") {}
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
            throw ErroBiblioteca("O catálogo está vazio. Impossível prosseguir.");
        }

        do {
            cout << "\n--- PAINEL DE CONTROLE (RESISTENTE A ERROS) ---" << endl;
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
                        
                        int index = lerInteiro("\nÍndice do livro para " + leitorAtual + " (ou -1): ");

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
                            throw ErroBiblioteca("Índice fora do alcance do catálogo.");
                        }
                    }
                }
                else if (opcao == 3) {
                    if (historico.empty()) {
                        throw ErroBiblioteca("Não há empréstimos para cancelar.");
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
                // Erros de lógica ou estoque que não param o sistema
                cout << e.what() << endl;
            }

        } while (opcao != 4);

        salvarRelatorio(historico);

    } catch (const exception& e) {
        // Erros fatais (como falta de arquivo) encerram com mensagem clara
        cerr << "\nFALHA NO SISTEMA: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// --- 5. IMPLEMENTAÇÃO DAS FUNÇÕES ---

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "      SISTEMA DE GESTÃO - ATIVIDADE 13         " << endl;
    cout << "      (Módulo de Robustez e Exceções)          " << endl;
    cout << "===============================================" << endl;
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
            continue; // Pula linha corrompida
        }
    }
    arquivo.close();
    cout << "[SISTEMA]: Catálogo carregado com sucesso." << endl;
}

string formatarData(time_t t) {
    char buffer[20];
    struct tm * timeinfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}

void salvarRelatorio(stack<Emprestimo> s) {
    ofstream rel("repositorio-extra/atividade-extra13/relatorio_sessao.txt", ios::trunc);
    if (!rel.is_open()) rel.open("relatorio_sessao.txt", ios::trunc);

    if (!rel.is_open()) {
        throw ErroArquivo("relatorio_sessao.txt");
    }

    rel << "--- RELATÓRIO DE SESSÃO ---\n";
    rel << "Data: " << formatarData(time(0)) << "\n\n";
    
    while (!s.empty()) {
        Emprestimo e = s.top();
        rel << "Leitor: " << e.leitor << " | Livro: " << e.livro.titulo << "\n";
        s.pop();
    }
    rel.close();
    cout << "[SISTEMA]: Relatório final gerado na pasta Atividade 13." << endl;
}
