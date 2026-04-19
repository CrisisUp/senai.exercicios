/**
 * @file atividade-extra27-templates-classe.cpp
 * @brief Gestão de Carga: Introdução a Class Templates.
 * 
 * Demonstra como criar classes genéricas que podem armazenar e processar
 * qualquer tipo de dado, simulando um container universal de logística.
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
    const string NEGRITO  = "\033[1m";
}

// --- 2. DEFINIÇÃO DA CLASS TEMPLATE (O CONCEITO ELITE) ---

template <typename T>
class UnidadeDeCarga {
private:
    string id;
    double pesoTotal;
    T conteudo; // O tipo T será decidido na criação do objeto

public:
    // Construtor
    UnidadeDeCarga(string _id, double _peso, T _conteudo) 
        : id(_id), pesoTotal(_peso), conteudo(_conteudo) {}

    // Método para atualizar o conteúdo
    void atualizarConteudo(T novoConteudo) {
        conteudo = novoConteudo;
    }

    // Exibição polimórfica (por tipo de dado)
    void exibirManifesto() const {
        cout << UI::CIANO << "MANIFESTO DE CARGA [" << id << "]" << UI::RESET << endl;
        cout << "Peso Bruto: " << pesoTotal << " kg" << endl;
        cout << "CONTEÚDO  : " << UI::AMARELO << conteudo << UI::RESET << endl;
        cout << "-----------------------------------------------" << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(2);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      LOGÍSTICA GLOBAL: CONTAINER ENGINE       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Cenário 1: Container de Sensores Eletrônicos (T = int)
    // Note a sintaxe <int> na criação
    UnidadeDeCarga<int> c1("BR-778", 150.0, 500); 
    cout << "[LOG]: Criando Unidade de Carga (Tipo: Unidades Inteiras)" << endl;
    c1.exibirManifesto();

    // Cenário 2: Container de Combustível (T = double)
    UnidadeDeCarga<double> c2("OIL-99", 5400.5, 450.75);
    cout << "[LOG]: Criando Unidade de Carga (Tipo: Volume Líquido)" << endl;
    c2.exibirManifesto();

    // Cenário 3: Container de Documentação (T = string)
    UnidadeDeCarga<string> c3("DOC-001", 12.0, "Contratos e Certidões de Exportação");
    cout << "[LOG]: Criando Unidade de Carga (Tipo: Texto/Documental)" << endl;
    c3.exibirManifesto();

    cout << UI::VERDE << "SISTEMA GENÉRICO VALIDADO COM SUCESSO!" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CLASS TEMPLATES
    ===============================================================

    1. FLEXIBILIDADE DE ESTRUTURA:
       - Enquanto Function Templates geram funções, Class Templates 
         permitem que uma CLASSE inteira seja genérica. Os atributos 
         e parâmetros de métodos se adaptam ao tipo 'T' escolhido.

    2. INSTANCIAÇÃO (<T>):
       - Ao criar o objeto, o programador DEVE informar o tipo 
         entre os sinais de menor/maior (ex: UnidadeDeCarga<int>). 
         A partir daí, aquele objeto específico só aceitará 'int'.

    3. REUTILIZAÇÃO EM LARGA ESCALA:
       - Este é o padrão usado pela biblioteca padrão do C++ (STL). 
         Sem isso, teríamos que escrever centenas de classes para 
         cada tipo de dado possível.

    4. COMPILAÇÃO:
       - O C++ usa um processo chamado 'Instanciação de Template'. 
         O código real para a classe 'UnidadeDeCarga<int>' só é 
         gerado quando você tenta usá-la no código.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Default Template Arguments: Definir um tipo padrão (ex: T=int).
    - Variadic Templates: Templates que aceitam um número infinito 
      de tipos de dados (C++11).
    - STL (Standard Template Library): O ápice do uso de templates.
    ===============================================================
*/
