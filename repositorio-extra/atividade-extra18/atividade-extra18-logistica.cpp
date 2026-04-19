/**
 * @file atividade-extra18-logistica.cpp
 * @brief Rastreio de Logística: Sobrecarga de Construtores e Inicialização.
 * 
 * Demonstra como inicializar objetos de diferentes formas e a sintaxe
 * profissional de 'Initialization List' em C++.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSE COM CONCEITOS AVANÇADOS DE POO ---

class PacoteLogistico {
private:
    string codigoRastreio;
    double peso;
    string destino;

public:
    // --- CONSTRUTOR 1 (COMPLETO) ---
    // Uso de Lista de Inicialização (mais eficiente)
    PacoteLogistico(string cod, double p, string dest) 
        : codigoRastreio(cod), peso(p), destino(dest) 
    {
        cout << UI::VERDE << "[SISTEMA]: Pacote COMPLETO registrado via Scanner." << UI::RESET << endl;
    }

    // --- CONSTRUTOR 2 (PARCIAL - SOBRECARGA) ---
    PacoteLogistico(string cod) 
        : codigoRastreio(cod), peso(0.0), destino("A DEFINIR") 
    {
        cout << UI::AMARELO << "[SISTEMA]: Pacote PARCIAL registrado via Cadastro Manual." << UI::RESET << endl;
    }

    // --- SETTERS COM VALIDAÇÃO ---

    void setPeso(double p) {
        if (p > 0) {
            peso = p;
            cout << "[OK]: Peso atualizado para " << p << "kg." << endl;
        } else {
            cout << "\033[31m[ERRO]: Peso inválido.\033[0m" << endl;
        }
    }

    void setDestino(string dest) {
        if (!dest.empty()) {
            destino = dest;
            cout << "[OK]: Destino definido para: " << dest << endl;
        }
    }

    // --- EXIBIÇÃO ---
    void exibirEtiqueta() const {
        cout << "\n" << UI::CIANO << "===============================================" << endl;
        cout << "           ETIQUETA DE TRANSPORTE              " << endl;
        cout << "===============================================" << UI::RESET << endl;
        cout << "RASTREIO: " << UI::AZUL << codigoRastreio << UI::RESET << endl;
        cout << "PESO    : " << (peso > 0 ? to_string(peso) + " kg" : UI::AMARELO + "PENDENTE" + UI::RESET) << endl;
        cout << "DESTINO : " << destino << endl;
        cout << UI::CIANO << "-----------------------------------------------" << UI::RESET << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(2);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      LOGÍSTICA SMART WAREHOUSE v2.0           " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Cenário 1: Scanner Automático (Construtor Completo)
    PacoteLogistico pacoteEsteira("BR-12345-SCAN", 2.5, "São Paulo - SP");
    pacoteEsteira.exibirEtiqueta();

    // Cenário 2: Cadastro Manual (Construtor Parcial)
    cout << "\nCadastrando novo pacote manual..." << endl;
    PacoteLogistico pacoteManual("BR-99887-MAN");
    pacoteManual.exibirEtiqueta();

    // Atualizando o pacote manual posteriormente
    cout << "\nPesando o pacote manual na balança..." << endl;
    pacoteManual.setPeso(5.8);
    pacoteManual.setDestino("Curitiba - PR");
    
    pacoteManual.exibirEtiqueta();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CONSTRUTORES E INICIALIZAÇÃO PROFISSIONAL
    ===============================================================

    1. SOBRECARGA DE CONSTRUTORES (Constructor Overloading):
       - Uma classe pode ter vários construtores, desde que a lista 
         de parâmetros seja diferente. Isso permite flexibilidade 
         na criação do objeto, simulando fluxos de trabalho reais.

    2. LISTA DE INICIALIZAÇÃO (Member Initializer List):
       - Sintaxe: : atributo(valor), atributo2(valor2).
       - É mais performática do que fazer atribuições dentro das 
         chaves {}, pois inicializa o atributo diretamente no 
         momento da criação da memória do objeto, sem criar um 
         valor temporário antes.

    3. POLIMORFISMO DE TEMPO DE COMPILAÇÃO:
       - A sobrecarga é um tipo de polimorfismo ad-hoc. O 
         compilador decide qual construtor chamar baseando-se no 
         tipo e número de argumentos passados.

    4. GARANTIA DE VALORES PADRÃO:
       - Usar um construtor parcial permite que o programador 
         garanta que atributos não fiquem com "lixo de memória", 
         definindo valores como 0.0 ou "PENDENTE" explicitamente.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Construtor Padrão (Default Constructor): O que o C++ gera sozinho.
    - Construtor de Cópia (Copy Constructor): Clonagem de objetos.
    - Delegating Constructors: Um construtor chamando outro.
    - Explicit Keyword: Evitando conversões implícitas em construtores.
    ===============================================================
*/
