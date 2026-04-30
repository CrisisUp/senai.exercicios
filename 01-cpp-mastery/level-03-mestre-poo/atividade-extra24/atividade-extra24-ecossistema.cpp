/**
 * @file atividade-extra24-ecossistema.cpp
 * @brief DESAFIO DE CICLO: Simulador de Ecossistema "Bio-CPP" v2.0.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integra todo o conhecimento de POO Avançada, Gestão de Heap e Resiliência.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Ecosystem Complex Layout)
 * - Objeto Reserva: Alocado na STACK da main.
 * - std::vector<SerVivo*>: O descritor vive na STACK, mas a lista de endereços na HEAP.
 * - Instâncias (Planta/Animal): Alocadas dinamicamente na HEAP via 'new'.
 * - Membros Estáticos: Alocados no DATA SEGMENT (Compartilhados por todos os seres).
 * - V-Table: Localizada no DATA SEGMENT, permitindo chamadas dinâmicas a agir().
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <exception>
#include <algorithm>

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
    void banner() {
        cout << UI::VERDE << UI::NEGRITO << "===============================================" << endl;
        cout << "      BIO-CPP v2.0: SIMULADOR DE VIDA          " << endl;
        cout << "       (Elite Computational Biology)           " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. GESTÃO DE EVENTOS BIOLÓGICOS (EXCEÇÕES) ---

class EventoNatureza : public exception {
    string msg;
public:
    EventoNatureza(string m) : msg(UI::AMARELO + "[EVENTO]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE ABSTRATA BASE: SER VIVO ---

/**
 * @class SerVivo
 * @brief Base abstrata para qualquer entidade biológica no simulador.
 */
class SerVivo {
protected:
    string nome;
    string especie;
    int energia;
    bool vivo;

    static int populacaoAtiva; // Membro Estático (Global)

public:
    /**
     * @brief Construtor: Inicializa a vida e incrementa a população global.
     */
    SerVivo(const string& _nome, const string& _esp, int _ene) 
        : nome(_nome), especie(_esp), energia(_ene), vivo(true) 
    {
        populacaoAtiva++;
    }

    /**
     * @brief Método Virtual Puro: Toda vida deve ter um comportamento.
     */
    virtual void agir() = 0;

    // --- GETTERS (FANTASMA DO CPU - CONST REF) ---
    bool isVivo() const { return vivo; }
    const string& getNome() const { return nome; }
    const string& getEspecie() const { return especie; }
    int getEnergia() const { return energia; }
    
    void morrer() { 
        if(vivo) {
            vivo = false; 
            populacaoAtiva--;
        }
    }

    static int getPopulacao() { return populacaoAtiva; }

    /**
     * @brief Destrutor Virtual: Essencial para limpeza correta na HEAP.
     */
    virtual ~SerVivo() {
        if (vivo) populacaoAtiva--;
    }
};

int SerVivo::populacaoAtiva = 0;

// --- 4. CLASSES ESPECIALIZADAS ---

/**
 * @class Planta
 * @brief Produtor primário: Ganha energia via radiação solar.
 */
class Planta : public SerVivo {
public:
    Planta(const string& _nome) : SerVivo(_nome, "Planta", 30) {}

    void agir() override {
        if (!vivo) return;
        energia += 15; // Fotossíntese eficiente
        cout << UI::VERDE << "[FOTOSSÍNTESE]: " << nome << " sintetizou +15 de energia solar." << UI::RESET << endl;
    }
};

/**
 * @class Animal
 * @brief Base para consumidores: Requer metabolismo e gestão de fome.
 */
class Animal : public SerVivo {
protected:
    int fome;
public:
    Animal(const string& _nome, const string& _esp, int _ene) 
        : SerVivo(_nome, _esp, _ene), fome(0) {}

    /**
     * @brief Mecânica de envelhecimento e desgaste metabólico.
     */
    void metabolizar() {
        fome += 5;
        energia -= 8;
        if (fome > 25 || energia <= 0) {
            morrer();
            throw EventoNatureza("Espécime '" + nome + "' faleceu por inanição.");
        }
    }
};

class Herbivoro : public Animal {
public:
    Herbivoro(const string& _nome) : Animal(_nome, "Herbívoro", 40) {}

    void agir() override {
        if (!vivo) return;
        try {
            metabolizar();
            cout << UI::AMARELO << "[PASTANDO]: " << nome << " consumiu biomassa e restaurou vigor." << UI::RESET << endl;
            fome = 0;
            energia += 12;
        } catch (const exception& e) {
            cout << UI::VERMELHO << e.what() << UI::RESET << endl;
        }
    }
};

class Carnivoro : public Animal {
public:
    Carnivoro(const string& _nome) : Animal(_nome, "Carnívoro", 55) {}

    void agir() override {
        if (!vivo) return;
        try {
            metabolizar();
            cout << UI::VERMELHO << "[CAÇANDO]: " << nome << " realizou abate bem-sucedido (-12 energia de combate)." << UI::RESET << endl;
            energia -= 12; // Esforço da caça
            fome = 0;
            energia += 25; // Recompensa da proteína
        } catch (const exception& e) {
            cout << UI::VERMELHO << e.what() << UI::RESET << endl;
        }
    }
};

// --- 5. RESERVA NATURAL (GESTORA DE ARQUITETURA) ---

class Reserva {
private:
    vector<SerVivo*> biota;
    int ciclo;

public:
    Reserva() : ciclo(0) {}

    void adicionar(SerVivo* s) { biota.push_back(s); }

    /**
     * @brief Executa o ciclo biológico e realiza faxina de memória (Garbage Collection).
     */
    void evoluir() {
        ciclo++;
        cout << "\n" << UI::NEGRITO << ">>> PROCESSANDO CICLO VITAL #" << ciclo << UI::RESET << endl;
        
        // Iteração Polimórfica (Fantasma do CPU)
        for (auto s : biota) {
            if (s && s->isVivo()) s->agir();
        }
    }

    void dashboard() const {
        cout << "\n" << UI::CIANO << UI::NEGRITO << "--- STATUS DA BIODIVERSIDADE ---" << UI::RESET << endl;
        cout << left << setw(15) << "NOME" << setw(12) << "ESPÉCIE" << setw(10) << "ENERGIA" << "VITALIDADE" << endl;
        cout << string(52, '-') << endl;
        
        for (const auto& s : biota) {
            if (s) {
                cout << left << setw(15) << s->getNome() 
                     << setw(12) << s->getEspecie() 
                     << setw(10) << s->getEnergia();
                if (s->isVivo()) cout << UI::VERDE << "ATIVO" << UI::RESET;
                else cout << UI::VERMELHO << "EXTINTO" << UI::RESET;
                cout << endl;
            }
        }
        cout << "\nPOPULAÇÃO ATIVA: " << UI::VERDE << SerVivo::getPopulacao() << UI::RESET << endl;
    }

    /**
     * @brief Destruição segura de todos os ponteiros da HEAP.
     */
    ~Reserva() { 
        for (auto s : biota) delete s; 
        biota.clear();
    }
};

// --- 6. EXECUÇÃO DO SIMULADOR ---

int main()
{
    Reserva amazonia;
    int opcao = 0;

    do {
        UI::limparTela();
        UI::banner();
        
        amazonia.dashboard();

        cout << UI::RESET << "\nMENU DE GENÉTICA:" << UI::RESET << endl;
        cout << "[1] Criar Planta      [2] Criar Herbívoro  [3] Criar Carnívoro" << endl;
        cout << "[4] Iniciar Evolução  [5] Encerrar Biosfera" << endl;
        cout << UI::CIANO << "Escolha: " << UI::RESET;
        
        if (!(cin >> opcao)) break;

        if (opcao >= 1 && opcao <= 3) {
            string n;
            cout << "Nome do espécime: ";
            getline(cin >> ws, n);
            
            if (opcao == 1) amazonia.adicionar(new Planta(n));
            else if (opcao == 2) amazonia.adicionar(new Herbivoro(n));
            else if (opcao == 3) amazonia.adicionar(new Carnivoro(n));
            
            cout << UI::VERDE << "[SISTEMA]: DNA codificado e injetado." << UI::RESET << endl;
            // Pequena pausa para UX
            clock_t goal = 500000 + clock();
            while (goal > clock());
        } 
        else if (opcao == 4) {
            amazonia.evoluir();
            cout << UI::AMARELO << "\nPressione ENTER para o próximo ciclo..." << UI::RESET;
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (opcao != 5);

    cout << UI::VERMELHO << "\nSimulação encerrada. Todos os processos vitais suspensos." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ECOSSISTEMAS COMPUTACIONAIS E POO III
    ===============================================================

    1. ABSTRAÇÃO DE NÍVEIS (Animal herda de SerVivo):
       - Demonstramos a "Hierarquia de Abstração". SerVivo é a 
         interface mais pura, Animal adiciona mecânicas de fome, 
         e Carnivoro/Herbivoro dão a implementação final.

    2. GESTÃO DE VIDA ÚTIL (HEAP LIFETIME):
       - Como os seres vivos são criados dinamicamente (new), a 
         classe Reserva assume o papel de "Gerenciadora de Memória". 
         O seu destrutor garante que nenhum espécime cause 
         Memory Leak ao final da simulação.

    3. POLIMORFISMO DE COLEÇÃO:
       - Um único vector<SerVivo*> pode conter centenas de tipos 
         diferentes. Ao chamar 's->agir()', o hardware desvia a 
         execução para o código exato da espécie através da vtable.

    4. RESILIÊNCIA BIOLÓGICA (EXCEÇÕES):
       - A morte não é um erro de software, mas um evento de negócio. 
         Usamos exceções para desviar o fluxo quando um ser 
         não consegue mais agir por falta de energia.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Smart Pointers (std::shared_ptr) em coleções.
    - Design Pattern 'Observer': Para reagir a mudanças ambientais.
    - Concorrência: Rodar cada ser vivo em sua própria Thread.
    ===============================================================
*/
