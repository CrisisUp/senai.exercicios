/**
 * @file atividade-extra21-agro.cpp
 * @brief Gestão de Maquinário: Introdução à Herança e Membros Protegidos.
 * 
 * Este programa demonstra como reaproveitar código criando uma classe base
 * (MaquinaAgricola) e uma classe especializada (Trator).
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

// --- 2. CLASSE BASE (MÃE) ---

class MaquinaAgricola {
protected:
    // Protected: Filhas acessam, o mundo externo não.
    string id;
    string marca;
    double combustivel; // Porcentagem 0-100

public:
    MaquinaAgricola(string _id, string _marca) 
        : id(_id), marca(_marca), combustivel(50.0) {} // Inicia com meio tanque

    void abastecer() {
        combustivel = 100.0;
        cout << UI::VERDE << "[SISTEMA]: Máquina " << id << " totalmente abastecida." << UI::RESET << endl;
    }

    void exibirBase() const {
        cout << "ID: " << id << " | Marca: " << marca 
             << " | Tanque: " << combustivel << "%" << endl;
    }
};

// --- 3. CLASSE DERIVADA (FILHA) ---

// Sintaxe de Herança: class NomeFilha : public NomeMae
class Trator : public MaquinaAgricola {
private:
    double capacidadeReboque; // Atributo exclusivo do Trator

public:
    // O construtor da filha deve chamar o construtor da mãe
    Trator(string _id, string _marca, double _cap) 
        : MaquinaAgricola(_id, _marca), capacidadeReboque(_cap) {}

    void ararTerra() {
        if (combustivel >= 10.0) {
            combustivel -= 10.0; // Acessando membro 'protected' da mãe
            cout << UI::AMARELO << "[TRATOR]: Operação de aragem concluída (-10% diesel)." << UI::RESET << endl;
        } else {
            cout << "\033[31m[ALERTA]: Combustível insuficiente para arar!\033[0m" << endl;
        }
    }

    void exibirTrator() const {
        cout << "\n--- STATUS DO TRATOR ---" << endl;
        exibirBase(); // Chamando método da mãe
        cout << "Capacidade de Reboque: " << capacidadeReboque << " toneladas" << endl;
        cout << "------------------------" << endl;
    }
};

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(1);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      SISTEMA DE GESTÃO AGROTECH v1.0          " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando um objeto da classe filha
    Trator meuTrator("T-900", "John Deere", 15.5);

    int opt = 0;
    do {
        meuTrator.exibirTrator();
        cout << "[1] Arar Terra | [2] Abastecer | [3] Sair" << endl;
        cout << "Escolha: ";
        cin >> opt;

        switch (opt) {
            case 1: meuTrator.ararTerra(); break;
            case 2: meuTrator.abastecer(); break;
        }
    } while (opt != 3);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HERANÇA (INHERITANCE)
    ===============================================================

    1. O CONCEITO "É UM" (IS-A):
       - A herança modela relações onde uma classe filha é uma 
         especialização da mãe. Ex: Um Trator É UMA Máquina Agrícola.

    2. MEMBROS PROTEGIDOS (protected):
       - É o meio termo entre private e public. Atributos protected 
         podem ser lidos e alterados diretamente pelas classes 
         filhas, mas continuam invisíveis para o código fora da 
         hierarquia.

    3. REUTILIZAÇÃO DE CÓDIGO:
       - O método abastecer() foi escrito apenas na MaquinaAgricola, 
         mas o objeto Trator pode usá-lo livremente. Isso evita 
         duplicação e bugs.

    4. CONSTRUTORES NA HERANÇA:
       - A classe filha não herda o construtor da mãe. Ela deve 
         chamar explicitamente o construtor da mãe em sua lista de 
         inicialização para garantir que a parte "mãe" do objeto 
         seja criada corretamente.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Herança Múltipla (C++ permite, mas exige cuidado).
    - Sobrescrita de Métodos (Overriding).
    - Composição vs Herança (Princípio de Design).
    - Tipos de Herança (public, protected, private inheritance).
    ===============================================================
*/
