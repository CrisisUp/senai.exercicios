/**
 * @file atividade-extra17-saude.cpp
 * @brief Monitoramento de UTI: Introdução a Classes e Encapsulamento.
 * 
 * Este programa demonstra a transição de 'struct' para 'class',
 * utilizando membros privados (private) para proteger a integridade
 * de dados médicos críticos através de métodos de validação (setters).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
}

// --- 2. DEFINIÇÃO DA CLASSE (O NOVO CONCEITO) ---

class PacienteMonitorado {
private:
    // Atributos privados: Ninguém fora da classe pode alterá-los diretamente.
    string nome;
    int bpm;
    double temperatura;
    int oxigenacao;

public:
    // Construtor: Inicializa o paciente com valores seguros
    PacienteMonitorado(string n) : nome(n), bpm(70), temperatura(36.5), oxigenacao(98) {}

    // --- MÉTODOS DE ACESSO (SETTERS COM VALIDAÇÃO) ---

    bool setBPM(int valor) {
        if (valor > 0 && valor < 250) {
            bpm = valor;
            return true;
        }
        return false; // Rejeitado se for absurdo
    }

    bool setTemperatura(double valor) {
        if (valor >= 30.0 && valor <= 45.0) {
            temperatura = valor;
            return true;
        }
        return false;
    }

    bool setOxigenacao(int valor) {
        if (valor >= 0 && valor <= 100) {
            oxigenacao = valor;
            return true;
        }
        return false;
    }

    // --- MÉTODOS DE LEITURA (GETTERS) ---
    string getNome() const { return nome; }
    int getBPM() const { return bpm; }
    double getTemperatura() const { return temperatura; }
    int getOxigenacao() const { return oxigenacao; }

    // --- LÓGICA DE NEGÓCIO: MONITORAMENTO ---
    void analisarEstado() {
        cout << "\n-----------------------------------------------" << endl;
        cout << "RELATÓRIO DE MONITORAMENTO: " << UI::CIANO << nome << UI::RESET << endl;
        cout << "Frequência Cardíaca: " << bpm << " BPM ";
        if (bpm > 100 || bpm < 50) cout << UI::VERMELHO << "[ALERTA]" << UI::RESET;
        else cout << UI::VERDE << "[NORMAL]" << UI::RESET;

        cout << "\nTemperatura        : " << temperatura << " °C ";
        if (temperatura > 37.5) cout << UI::VERMELHO << "[FEBRE]" << UI::RESET;
        else cout << UI::VERDE << "[NORMAL]" << UI::RESET;

        cout << "\nOxigenação         : " << oxigenacao << " % ";
        if (oxigenacao < 94) cout << UI::VERMELHO << "[CRÍTICO]" << UI::RESET;
        else cout << UI::VERDE << "[NORMAL]" << UI::RESET;
        cout << "\n-----------------------------------------------" << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(1);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "     SISTEMA DE MONITORAMENTO DE UTI v1.0      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando um objeto (instância) da classe
    PacienteMonitorado p1("João da Silva");

    int entradaBPM, entradaOxy;
    double entradaTemp;

    // Simulação de entrada de dados do monitor real
    cout << "Digite o BPM atual do paciente: ";
    cin >> entradaBPM;
    if (!p1.setBPM(entradaBPM)) {
        cout << UI::AMARELO << "AVISO: Valor de BPM inválido ignorado para segurança." << UI::RESET << endl;
    }

    cout << "Digite a Temperatura atual (°C): ";
    cin >> entradaTemp;
    if (!p1.setTemperatura(entradaTemp)) {
        cout << UI::AMARELO << "AVISO: Valor de Temperatura inválido ignorado." << UI::RESET << endl;
    }

    cout << "Digite a Oxigenação (%): ";
    cin >> entradaOxy;
    if (!p1.setOxigenacao(entradaOxy)) {
        cout << UI::AMARELO << "AVISO: Valor de Oxigenação inválido ignorado." << UI::RESET << endl;
    }

    // Análise segura dos dados encapsulados
    p1.analisarEstado();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: INTRODUÇÃO À ORIENTAÇÃO A OBJETOS (POO)
    ===============================================================

    1. O QUE É UMA CLASSE (class):
       - É o "molde" ou "planta baixa" de um objeto. Enquanto a 
         struct foca em AGRUPAR dados, a classe foca em PROTEGER 
         dados e em como eles se comportam.

    2. ENCAPSULAMENTO (O pilar da segurança):
       - private: Atributos que ninguém "de fora" pode tocar. 
         Garante que a saúde do paciente não seja alterada por 
         erros de outras partes do sistema.
       - public: A interface do objeto. São as funções que 
         permitem interagir com os dados de forma controlada.

    3. SETTERS (Validadores):
       - Funções como 'setBPM' agem como "seguranças na porta". 
         Elas recebem o dado, verificam se faz sentido (ex: BPM > 0) 
         e só então gravam na memória privada.

    4. CONSTRUTOR:
       - É a função PacienteMonitorado(string n). Ela garante que, 
         no momento em que o paciente é "criado", ele já comece 
         com valores vitais seguros, evitando lixo de memória.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Abstração: Representar apenas o essencial para o domínio.
    - Ocultamento de Dados (Information Hiding).
    - Métodos Const (getters que não alteram o objeto).
    ===============================================================
*/
