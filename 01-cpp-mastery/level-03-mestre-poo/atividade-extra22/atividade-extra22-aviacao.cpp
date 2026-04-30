/**
 * @file atividade-extra22-aviacao.cpp
 * @brief Controle de Voo: Polimorfismo Industrial e Funções Virtuais.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a Ligação Dinâmica (Dynamic Binding) e a importância do Destrutor Virtual.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (V-Table Layout)
 * - vptr (Virtual Pointer): Cada objeto aeronave na HEAP possui um ponteiro oculto para a V-TABLE.
 * - V-TABLE: Tabela estática na memória (Data Segment) que mapeia o endereço real de decolar().
 * - HEAP: Local onde os objetos AviaoComercial e Helicoptero são instanciados via 'new'.
 * - STACK: Armazena o std::vector de ponteiros que gerenciam os endereços da HEAP.
 */

#include <iostream>
#include <string>
#include <vector>

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

// --- 2. CLASSE BASE COM MÉTODOS VIRTUAIS ---

/**
 * @class Aeronave
 * @brief Classe base abstrata funcional para o ecossistema de voo.
 */
class Aeronave {
protected:
    string prefixo;

public:
    /**
     * @brief Construtor com Lista de Inicialização (Performance).
     */
    Aeronave(const string& _pref) : prefixo(_pref) {}
    
    /**
     * @brief Método Virtual: Permite que a função seja decidida no 'runtime'.
     */
    virtual void prepararParaDecolagem() {
        cout << UI::RESET << "[Aeronave " << prefixo << "]: " << UI::RESET << "Check-list de aviônica completo." << endl;
    }

    virtual void decolar() {
        cout << "[Aeronave " << prefixo << "]: Procedimento genérico de decolagem." << endl;
    }

    /**
     * @brief Destrutor Virtual: VITAL para evitar Memory Leaks em polimorfismo.
     */
    virtual ~Aeronave() {
        cout << UI::AMARELO << "[LIMPEZA]: Memória do Prefixo " << prefixo << " liberada." << UI::RESET << endl;
    }
};

// --- 3. CLASSES DERIVADAS (SOBRESCRITA) ---

/**
 * @class AviaoComercial
 * @brief Sobrescrita específica para aeronaves de asa fixa.
 */
class AviaoComercial : public Aeronave {
public:
    AviaoComercial(const string& _pref) : Aeronave(_pref) {}

    /**
     * @brief override: Garante que estamos sobrescrevendo o método virtual correto.
     */
    void decolar() override {
        cout << UI::VERDE << UI::NEGRITO << "[ASA FIXA " << prefixo << "]: " << UI::RESET 
             << UI::VERDE << "V1... VR... Decolagem de pista concluída!" << UI::RESET << endl;
    }
};

/**
 * @class Helicoptero
 * @brief Sobrescrita específica para aeronaves de asa rotativa.
 */
class Helicoptero : public Aeronave {
public:
    Helicoptero(const string& _pref) : Aeronave(_pref) {}

    void decolar() override {
        cout << UI::AZUL << UI::NEGRITO << "[ASA ROTATIVA " << prefixo << "]: " << UI::RESET 
             << UI::AZUL << "Passo coletivo aumentado... Decolagem Vertical concluída!" << UI::RESET << endl;
    }
};

// --- 4. EXECUÇÃO DA TORRE DE CONTROLE ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      SISTEMA DE TORRE DE CONTROLE (ATC v2.0)  " << endl;
    cout << "       (Elite Polymorphic Architecture)        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // A mágica do polimorfismo: Uma coleção da MÃE gerenciando diversas FILHAS.
    vector<Aeronave*> torreDeControle;

    // Alocação dinâmica na HEAP (Exige gestão manual ou Smart Pointers)
    torreDeControle.push_back(new AviaoComercial("PT-AIR"));
    torreDeControle.push_back(new Helicoptero("PP-HELI"));
    torreDeControle.push_back(new AviaoComercial("AZ-SKY"));

    cout << "\n" << UI::RESET << "[ATC]: Autorização concedida. Iniciando sequência de decolagem em massa..." << UI::RESET << "\n" << endl;

    // Loop de Telemetria (Fantasma do CPU: Aeronave* é apenas um endereço)
    for (const auto& aero : torreDeControle) {
        if (aero) { // Proteção contra ponteiros nulos (Cientista do Caos)
            aero->prepararParaDecolagem(); 
            aero->decolar();               
            cout << UI::RESET << "-----------------------------------------------" << UI::RESET << endl;
        }
    }

    // --- CICLO DE DESALOCAÇÃO RIGOROSA ---
    cout << "\n" << UI::RESET << "[SISTEMA]: Encerrando turno e liberando memória..." << UI::RESET << endl;
    for (auto& aero : torreDeControle) {
        delete aero; // Aciona o destrutor virtual correto (Mãe ou Filha)
        aero = nullptr; // Zera o ponteiro para evitar o uso após a morte (Dangling Pointer)
    }
    torreDeControle.clear();

    cout << UI::VERDE << "\nOperação ATC finalizada com Zero Vazamentos." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: POLIMORFISMO E DINÂMICA DE EXECUÇÃO
    ===============================================================

    1. LIGAÇÃO DINÂMICA (LATE BINDING):
       - Sem a palavra 'virtual', o C++ decide qual função chamar 
         na compilação (Early Binding). Com 'virtual', a decisão 
         é adiada para o momento em que o código roda, consultando 
         a V-Table do objeto real.

    2. A V-TABLE (VIRTUAL TABLE):
       - É o "mapa de endereços" que o polimorfismo usa. Cada classe 
         tem uma V-Table. Cada objeto tem um V-PTR apontando para 
         essa tabela. É o preço da flexibilidade (overhead mínimo).

    3. DESTRUTOR VIRTUAL (REGRA DE OURO):
       - Sempre que uma classe tiver UM método virtual, o seu 
         destrutor DEVE ser virtual. Isso garante que, ao destruir 
         um objeto filho por um ponteiro da mãe, o compilador 
         saiba limpar a memória extra da subclasse.

    4. SEGURANÇA DE PONTEIROS:
       - O uso de 'delete' seguido de 'nullptr' previne um dos 
         erros mais graves do C++: o acesso a memória já liberada.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - RTTI (Run-Time Type Information).
    - Pure Virtual Functions (= 0): Criando interfaces puras.
    - Abstract Base Classes (ABC).
    - Smart Pointers (std::unique_ptr): O fim do 'delete' manual.
    ===============================================================
*/
