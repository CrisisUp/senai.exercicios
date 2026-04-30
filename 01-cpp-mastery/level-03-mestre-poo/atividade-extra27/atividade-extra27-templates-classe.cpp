/**
 * @file atividade-extra27-templates-classe.cpp
 * @brief Gestão de Carga: Programação Genérica com Class Templates.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a criação de componentes universais e a otimização de performance genérica.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Class Template Instance)
 * - Objeto UnidadeDeCarga<T>: Alocado na STACK ou HEAP conforme a main().
 * - Atributo 'T conteudo': O espaço reservado depende do tipo T (int=4b, double=8b, string=32b).
 * - Polimorfismo Estático: Não há V-TABLE. O compilador gera classes físicas 
 *   separadas para cada T utilizado, garantindo performance de código nativo.
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. DEFINIÇÃO DA CLASS TEMPLATE (CONTEINER UNIVERSAL) ---

/**
 * @class UnidadeDeCarga
 * @brief Abstração genérica para armazenamento e transporte de qualquer tipo de dado.
 * @tparam T Tipo do conteúdo transportado (Pode ser primitivo ou objeto complexo).
 */
template <typename T>
class UnidadeDeCarga {
private:
    string id;
    double pesoTotal;
    T conteudo; // Memória reservada dinamicamente pelo compilador conforme o tipo T

public:
    /**
     * @brief Construtor Universal.
     * @param _conteudo Passagem por Referência Constante (FANTASMA DO CPU).
     */
    UnidadeDeCarga(const string& _id, double _peso, const T& _conteudo) 
        : id(_id), pesoTotal(_peso), conteudo(_conteudo) {}

    /**
     * @brief Atualiza o conteúdo genérico com proteção contra cópias pesadas.
     */
    void atualizarConteudo(const T& novoConteudo) {
        conteudo = novoConteudo;
    }

    /**
     * @brief Gera manifesto técnico baseado no tipo T instanciado.
     */
    void exibirManifesto() const {
        cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
        cout << UI::NEGRITO << "MANIFESTO DE CARGA [" << UI::CIANO << id << UI::RESET << UI::NEGRITO << "]" << UI::RESET << endl;
        cout << UI::RESET << "PESO BRUTO: " << UI::RESET << fixed << setprecision(2) << pesoTotal << " kg" << endl;
        cout << UI::RESET << "CONTEÚDO  : " << UI::RESET << UI::AMARELO << UI::NEGRITO << conteudo << UI::RESET << endl;
        cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
    }
};

// --- 3. EXECUÇÃO PRINCIPAL ---

int main()
{
    UI::limparTela();
    cout << fixed << setprecision(2);

    cout << UI::VERDE << UI::NEGRITO << "===============================================" << endl;
    cout << "      LOGÍSTICA GLOBAL: CONTAINER ENGINE v2.0  " << endl;
    cout << "       (Elite Class Template Instance)         " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // --- INSTÂNCIA 1: UNIDADES INTEIRAS (T = int) ---
    UnidadeDeCarga<int> c1("BR-778", 150.0, 500); 
    cout << UI::RESET << "[LOG]: Unidade Inteira (Sensores) configurada na STACK." << UI::RESET << endl;
    c1.exibirManifesto();

    // --- INSTÂNCIA 2: VOLUME LÍQUIDO (T = double) ---
    UnidadeDeCarga<double> c2("OIL-99", 5400.5, 450.75);
    cout << UI::RESET << "[LOG]: Unidade de Precisão (Volume) configurada na STACK." << UI::RESET << endl;
    c2.exibirManifesto();

    // --- INSTÂNCIA 3: CARGA DOCUMENTAL (T = string) ---
    UnidadeDeCarga<string> c3("DOC-001", 12.0, "CERTIFICADOS_EXPORT_A1.PDF");
    cout << UI::RESET << "[LOG]: Unidade de Texto (Log) configurada na STACK." << UI::RESET << endl;
    c3.exibirManifesto();

    cout << "\n" << UI::VERDE << UI::NEGRITO << "SISTEMA GENÉRICO HOMOLOGADO COM 100% DE TIPAGEM ESTÁTICA." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CLASS TEMPLATES E REUSO ESTRUTURAL
    ===============================================================

    1. TEMPLATES DE CLASSE (CONTAINERS):
       - Diferente dos templates de função, aqui a CLASSE INTEIRA 
         se torna um molde. É a base da Standard Template Library 
         (STL). Ao invés de criarmos 'VectorInt' e 'VectorFloat', 
         criamos 'Vector<T>'.

    2. FANTASMA DO CPU (ELITE PERFORMANCE):
       - Note o uso de 'const T&' em todos os parâmetros. Como não 
         sabemos se o usuário passará um 'int' (4 bytes) ou uma 
         'Struct de 1MB', usamos a referência constante para 
         garantir que o sistema nunca clone dados pesados.

    3. MONOMORFIZAÇÃO:
       - O compilador gera três classes físicas em código de 
         máquina neste programa. Isso significa que não há perda de 
         performance por "verificar o tipo" no runtime. O C++ é 
         tão rápido em código genérico quanto em código manual.

    4. SEGURANÇA ARQUITETURAL:
       - Templates forçam o programador a decidir o tipo no momento 
         da criação. Uma vez definido que o container 'c1' é <int>, 
         é impossível colocar uma string dentro dele, protegendo o 
         sistema contra corrupção de dados.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Template Meta-Programming (TMP).
    - Policy-based Design.
    - Explicit Template Instantiation: Para reduzir tempo de build.
    ===============================================================
*/
