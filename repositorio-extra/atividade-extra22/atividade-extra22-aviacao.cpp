/**
 * @file atividade-extra22-aviacao.cpp
 * @brief Controle de Voo: Polimorfismo e Funções Virtuais.
 * 
 * Este programa demonstra como uma classe base pode comandar diferentes
 * tipos de aeronaves de forma genérica, executando a lógica específica
 * de cada uma em tempo de execução.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSE BASE COM MÉTODOS VIRTUAIS ---

class Aeronave {
protected:
    string prefixo;

public:
    Aeronave(string _pref) : prefixo(_pref) {}
    
    // Virtual: Permite que a função seja sobrescrita e decidida no 'runtime'
    virtual void prepararParaDecolagem() {
        cout << "[Aeronave " << prefixo << "]: Realizando check-list padrão..." << endl;
    }

    virtual void decolar() {
        cout << "[Aeronave " << prefixo << "]: Decolagem genérica iniciada." << endl;
    }

    // Destrutor virtual é OBRIGATÓRIO em classes com métodos virtuais
    virtual ~Aeronave() {}
};

// --- 3. CLASSES DERIVADAS (SOBRESCRITA) ---

class AviaoComercial : public Aeronave {
public:
    AviaoComercial(string _pref) : Aeronave(_pref) {}

    // override: Garante que estamos realmente sobrescrevendo um método virtual da mãe
    void decolar() override {
        cout << UI::VERDE << "[AVIÃO " << prefixo << "]: Acelerando turbinas na pista... V1... VR... Decolando!" << UI::RESET << endl;
    }
};

class Helicoptero : public Aeronave {
public:
    Helicoptero(string _pref) : Aeronave(_pref) {}

    void decolar() override {
        cout << UI::AZUL << "[HELI " << prefixo << "]: Girando rotores... Passo coletivo aumentado... Decolagem Vertical!" << UI::RESET << endl;
    }
};

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      SISTEMA DE TORRE DE CONTROLE (ATC)       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // A mágica do polimorfismo acontece aqui: 
    // Uma lista de ponteiros para a CLASSE MÃE guardando objetos das FILHAS.
    vector<Aeronave*> torreDeControle;

    torreDeControle.push_back(new AviaoComercial("PT-AAA"));
    torreDeControle.push_back(new Helicoptero("PP-HELI"));
    torreDeControle.push_back(new AviaoComercial("PT-BBB"));

    cout << "\n[TORRE]: Autorizando decolagem imediata para todas as aeronaves...\n" << endl;

    // O comando é o mesmo, mas a execução será diferente para cada item!
    for (Aeronave* aero : torreDeControle) {
        aero->prepararParaDecolagem(); // Chama o código da mãe (não sobrescrito)
        aero->decolar();               // Chama o código polimórfico (sobrescrito)
        cout << "-----------------------------------------------" << endl;
    }

    // Limpeza de memória (Ponteiros exigem delete)
    for (Aeronave* aero : torreDeControle) {
        delete aero;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: POLIMORFISMO (DYNAMIC BINDING)
    ===============================================================

    1. FUNÇÕES VIRTUAIS (virtual):
       - Quando marcamos um método como virtual na mãe, o C++ cria 
         uma tabela oculta (vtable). Isso permite que o programa 
         saiba, em tempo de execução, se deve chamar a função da 
         mãe ou a versão sobrescrita da filha.

    2. A PALAVRA-CHAVE override:
       - Introduzida no C++11, ela protege o programador. Se você 
         tentar sobrescrever um método que não existe na mãe ou 
         errar um parâmetro, o compilador gerará um erro.

    3. DESTRUTOR VIRTUAL:
       - Se você tem métodos virtuais, o seu destrutor DEVE ser 
         virtual. Caso contrário, ao deletar uma filha através de 
         um ponteiro da mãe, apenas a parte "mãe" será limpa, 
         causando vazamento de memória (Memory Leak).

    4. VANTAGEM ARQUITETURAL:
       - O polimorfismo permite que o sistema cresça sem mudar o 
         código da Torre de Controle. Se amanhã criarmos a classe 
         'Foguete', a torre continuará funcionando sem mudar uma 
         linha de código do 'for'.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - V-Table (Virtual Method Table): Como o C++ faz isso por baixo do pano.
    - Ponteiros vs Referências no Polimorfismo.
    - Classes Abstratas (Próxima atividade).
    - Upcasting e Downcasting (dynamic_cast).
    ===============================================================
*/
