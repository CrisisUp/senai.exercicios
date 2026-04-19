/**
 * @file atividade-extra31-validacao.cpp
 * @brief Terminal Cyber-Guard: Validação de Dados e Padrão Singleton.
 * 
 * Implementa um sistema de entrada blindado que utiliza o padrão Singleton
 * e templates para garantir que o programa nunca trave por entradas
 * inválidas do usuário.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSE VALIDADOR (PADRÃO SINGLETON) ---

class Validador {
private:
    // Construtor privado: Ninguém pode dar 'new' nesta classe.
    Validador() {}

    // Impede cópia do objeto para manter a unicidade.
    Validador(const Validador&) = delete;
    void operator=(const Validador&) = delete;

public:
    // Ponto de acesso global ao Singleton.
    static Validador& getInstancia() {
        static Validador instancia;
        return instancia;
    }

    /**
     * @brief Template que blinda a leitura de dados do teclado.
     * Limpa o buffer automaticamente em caso de erro de tipo.
     */
    template <typename T>
    T lerDado(string mensagem) {
        T dado;
        while (true) {
            cout << mensagem;
            if (cin >> dado) {
                // Entrada bem-sucedida
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa sobra do Enter
                return dado;
            } else {
                // Falha de tipo (Ex: digitou letra onde era número)
                cout << UI::VERMELHO << " [ERRO]: Entrada inválida. Tente novamente." << UI::RESET << endl;
                cin.clear(); // Limpa o estado de erro do cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta o "lixo" no buffer
            }
        }
    }

    /**
     * @brief Valida se um valor está dentro de uma faixa permitida.
     */
    bool validarFaixa(double valor, double min, double max) {
        return (valor >= min && valor <= max);
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    // Acessando o validador único do sistema
    Validador& v = Validador::getInstancia();

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      TERMINAL DE DEFESA CYBER-GUARD v1.0      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    cout << "\n[SISTEMA]: Inicializando protocolos de segurança..." << endl;

    // 1. Validação de Inteiro (Nível de Acesso)
    int nivel;
    while (true) {
        nivel = v.lerDado<int>("Digite seu Nível de Acesso (1-10): ");
        if (v.validarFaixa(nivel, 1, 10)) break;
        cout << UI::AMARELO << " [AVISO]: O nível deve estar entre 1 e 10." << UI::RESET << endl;
    }

    // 2. Validação de Double (Frequência de Encriptação)
    double frequencia;
    while (true) {
        frequencia = v.lerDado<double>("Digite a Frequência de Encriptação (GHz): ");
        if (v.validarFaixa(frequencia, 0.1, 5.0)) break;
        cout << UI::AMARELO << " [AVISO]: Frequência deve ser entre 0.1 e 5.0 GHz." << UI::RESET << endl;
    }

    // 3. Validação de String (Nome codificado)
    string codinome = v.lerDado<string>("Digite seu Codinome de Operador: ");

    // Conclusão
    cout << "\n" << UI::VERDE << "===============================================" << endl;
    cout << "      ACESSO AUTORIZADO: PROTOCOLO ATIVO       " << endl;
    cout << "===============================================" << UI::RESET << endl;
    cout << "Operador   : " << codinome << endl;
    cout << "Nível      : " << nivel << endl;
    cout << "Encriptação: " << fixed << setprecision(2) << frequencia << " GHz" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: VALIDAÇÃO PROFISSIONAL E SINGLETON
    ===============================================================

    1. O ESTADO DE FALHA DO CIN:
       - Quando o cin recebe um dado de tipo errado, ele "trava" 
         (fail state). Se você não chamar cin.clear(), o programa 
         nunca mais lerá nada do teclado. O método lerDado() 
         resolve isso para sempre.

    2. LIMPEZA DE BUFFER (numeric_limits):
       - cin.ignore() é usado para descartar caracteres que ficaram 
         "sobrando" no teclado, como o caractere de Nova Linha (\n) 
         do Enter. Isso evita que o próximo campo seja pulado.

    3. PADRÃO SINGLETON:
       - Garante que exista apenas uma instância da classe Validador. 
         Em sistemas grandes, ter múltiplos validadores pode causar 
         conflitos de sincronização no buffer de entrada.

    4. ROBUSTEZ (MEDALHA CÓDIGO BLINDADO):
       - Um software robusto é aquele que não quebra sob pressão 
         ou erro do usuário. Esta técnica é a base para criar 
         aplicativos de console profissionais.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Expressões Regulares (std::regex): Para validar formatos 
      complexos como E-mails ou CPFs.
    - Sanitização de Strings: Remover comandos SQL ou Script de entradas.
    - IOStreams avançado: Customizando manipulators.
    ===============================================================
*/
