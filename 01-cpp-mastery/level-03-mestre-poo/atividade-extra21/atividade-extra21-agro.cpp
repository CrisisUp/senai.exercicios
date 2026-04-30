/**
 * @file atividade-extra21-agro.cpp
 * @brief Gestão de Maquinário: Herança Profissional e Membros Protegidos.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra o reuso de código via hierarquia de classes e proteção de estado.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Inheritance Layout)
 * - Objeto Trator: Alocado na STACK. Seu layout contém primeiro os membros da 
 *   classe mãe (id, marca, combustivel) seguidos pelos membros da filha (capacidade).
 * - Cadeia de Construtores: A memória é reservada para o objeto total, mas o 
 *   construtor da mãe é executado PRIMEIRO para garantir a base sólida.
 * - Strings (id, marca): Ponteiros na STACK, dados reais na HEAP.
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

// --- 2. CLASSE BASE (MÃE) ---

/**
 * @class MaquinaAgricola
 * @brief Define a abstração básica para qualquer maquinário da fazenda.
 */
class MaquinaAgricola {
protected:
    // Protected: Permite que as classes filhas acessem, mas mantém o encapsulamento externo.
    string id;
    string marca;
    double combustivel; // Nível em %

public:
    /**
     * @brief Construtor da Base com Lista de Inicialização (Performance).
     */
    MaquinaAgricola(const string& _id, const string& _marca) 
        : id(_id), marca(_marca), combustivel(50.0) {}

    /**
     * @brief Abastece a máquina até o limite de segurança.
     */
    void abastecer() {
        combustivel = 100.0;
        cout << UI::VERDE << "[SISTEMA]: Máquina " << UI::NEGRITO << id << UI::RESET 
             << UI::VERDE << " totalmente abastecida (BioDiesel 100%)." << UI::RESET << endl;
    }

    void exibirBase() const {
        cout << UI::RESET << "ID      : " << UI::RESET << UI::CIANO << id << UI::RESET << endl;
        cout << UI::RESET << "MARCA   : " << UI::RESET << marca << endl;
        cout << UI::RESET << "TANQUE  : " << UI::RESET;
        if (combustivel < 20.0) cout << UI::VERMELHO << UI::NEGRITO;
        else cout << UI::VERDE;
        cout << combustivel << "%" << UI::RESET << endl;
    }
};

// --- 3. CLASSE DERIVADA (FILHA) ---

/**
 * @class Trator
 * @brief Especialização de MaquinaAgricola para operações de tração pesada.
 */
class Trator : public MaquinaAgricola {
private:
    double capacidadeReboque; // Em toneladas

public:
    /**
     * @brief Construtor do Trator: Delega a criação da base para a mãe.
     */
    Trator(const string& _id, const string& _marca, double _cap) 
        : MaquinaAgricola(_id, _marca), capacidadeReboque(_cap) {}

    /**
     * @brief Operação específica da subclasse.
     */
    void ararTerra() {
        if (combustivel >= 15.0) {
            combustivel -= 15.0; // Acesso direto ao membro protected da mãe
            cout << UI::AMARELO << UI::NEGRITO << "[OPERACIONAL]: Aragem concluída com sucesso (-15% combustível)." << UI::RESET << endl;
        } else {
            cout << UI::VERMELHO << UI::NEGRITO << "[ALERTA CRÍTICO]: Nível de combustível insuficiente para operação pesada!" << UI::RESET << endl;
        }
    }

    /**
     * @brief Exibição estendida (Base + Especialização).
     */
    void exibirStatus() const {
        cout << "\n" << UI::NEGRITO << "--- TELEMETRIA DO MAQUINÁRIO ---" << UI::RESET << endl;
        exibirBase(); // Reuso de método da mãe
        cout << UI::RESET << "REBOQUE : " << UI::RESET << capacidadeReboque << " Toneladas" << endl;
        cout << UI::NEGRITO << "--------------------------------" << UI::RESET << endl;
    }
};

// --- 4. EXECUÇÃO PRINCIPAL ---

int main()
{
    UI::limparTela();
    cout << fixed << setprecision(1);

    cout << UI::VERDE << UI::NEGRITO << "===============================================" << endl;
    cout << "      SISTEMA DE GESTÃO AGROTECH v2.0          " << endl;
    cout << "       (Elite Inheritance Module)              " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Instanciação na STACK
    Trator johnDeere("T-900", "John Deere", 18.5);

    int opt = 0;
    do {
        johnDeere.exibirStatus();
        cout << UI::RESET << "\nMENU DE COMANDO:" << UI::RESET << endl;
        cout << "[1] Arar Terra (Trabalho)" << endl;
        cout << "[2] Reabastecer Máquina" << endl;
        cout << "[3] Finalizar Turno" << endl;
        cout << UI::CIANO << "Escolha: " << UI::RESET;
        
        if (!(cin >> opt)) break;

        switch (opt) {
            case 1: johnDeere.ararTerra(); break;
            case 2: johnDeere.abastecer(); break;
            case 3: cout << UI::AMARELO << "Encerrando sistemas de bordo..." << UI::RESET << endl; break;
            default: cout << UI::VERMELHO << "Comando desconhecido." << UI::RESET << endl;
        }
    } while (opt != 3);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HERANÇA E REUSO ARQUITETURAL
    ===============================================================

    1. O PILAR DA HERANÇA:
       - Permite que classes compartilhem atributos e comportamentos. 
         No Agrotech, 'MaquinaAgricola' define o contrato básico de 
         existência (id, marca, abastecer), enquanto 'Trator' define 
         a utilidade específica.

    2. O MODIFICADOR 'PROTECTED':
       - É a chave para a herança saudável. Ele mantém os dados 
         escondidos do resto do sistema (como o private), mas abre 
         uma "porta de confiança" para que as classes filhas possam 
         manipular o estado interno da mãe sem intermediários.

    3. LISTA DE INICIALIZAÇÃO NA HERANÇA:
       - Note que o construtor do Trator chama explicitamente 
         'MaquinaAgricola(_id, _marca)'. Isso é OBRIGATÓRIO, pois a 
         parte mãe do objeto deve ser validada e criada antes que a 
         parte filha receba seus dados extras.

    4. PERFORMANCE (FANTASMA DO CPU):
       - Strings são passadas por 'const string&' para evitar que 
         o C++ faça cópias desnecessárias na transição entre os 
         construtores da filha e da mãe.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Sobrescrita (Overriding) vs Sobrecarga (Overloading).
    - Polimorfismo Dinâmico (Funções Virtuais).
    - Herança de Interface vs Herança de Implementação.
    ===============================================================
*/
