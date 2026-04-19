/**
 * @file atividade-extra24-ecossistema.cpp
 * @brief DESAFIO DE FECHAMENTO: Simulador de Ecossistema "Bio-CPP" (VERSÃO INTERATIVA).
 * 
 * Este projeto é a síntese de todo o conhecimento de POO Avançada:
 * - Abstração (Contratos de vida)
 * - Polimorfismo Dinâmico (Interações biológicas)
 * - Membros Estáticos (Ambiente Global)
 * - Gestão de Exceções (Eventos da Natureza)
 * - Painel Interativo de Gestão de Biodiversidade.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string VERMELHO = "\033[31m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTÃO DE EXCEÇÕES DA NATUREZA ---

class EventoNatureza : public exception {
    string msg;
public:
    EventoNatureza(string m) : msg(m) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE ABSTRATA BASE: SER VIVO ---

class SerVivo {
protected:
    string nome;
    string especie;
    int energia;
    bool vivo;

    static int populacaoTotal;

public:
    SerVivo(string _nome, string _esp, int _ene) 
        : nome(_nome), especie(_esp), energia(_ene), vivo(true) 
    {
        populacaoTotal++;
    }

    virtual void agir() = 0;

    bool isVivo() const { return vivo; }
    string getNome() const { return nome; }
    string getEspecie() const { return especie; }
    int getEnergia() const { return energia; }
    
    void morrer() { 
        if(vivo) {
            vivo = false; 
            populacaoTotal--;
        }
    }

    static int getPopulacao() { return populacaoTotal; }
    virtual ~SerVivo() {}
};

int SerVivo::populacaoTotal = 0;

// --- 4. CLASSES ESPECIALIZADAS ---

class Planta : public SerVivo {
public:
    Planta(string _nome) : SerVivo(_nome, "Planta", 30) {}

    void agir() override {
        if (!vivo) return;
        energia += 10; // Fotossíntese
        cout << UI::VERDE << "[FOTOSSÍNTESE]: " << nome << " (+10 energia)" << UI::RESET << endl;
    }
};

class Animal : public SerVivo {
protected:
    int fome;
public:
    Animal(string _nome, string _esp, int _ene) : SerVivo(_nome, _esp, _ene), fome(0) {}

    void envelhecer() {
        fome += 3;
        energia -= 5;
        if (fome > 15 || energia <= 0) {
            morrer();
            throw EventoNatureza("O espécime '" + nome + "' sucumbiu à natureza.");
        }
    }
};

class Herbivoro : public Animal {
public:
    Herbivoro(string _nome) : Animal(_nome, "Herbívoro", 40) {}

    void agir() override {
        if (!vivo) return;
        try {
            envelhecer();
            cout << UI::AMARELO << "[PASTANDO]: " << nome << " (Fome reduzida)" << UI::RESET << endl;
            fome = 0;
            energia += 5;
        } catch (const exception& e) {
            cout << UI::VERMELHO << "[MORTE]: " << e.what() << UI::RESET << endl;
        }
    }
};

class Carnivoro : public Animal {
public:
    Carnivoro(string _nome) : Animal(_nome, "Carnívoro", 60) {}

    void agir() override {
        if (!vivo) return;
        try {
            envelhecer();
            cout << UI::VERMELHO << "[CAÇANDO]: " << nome << " (Alto gasto energético)" << UI::RESET << endl;
            energia -= 10;
            fome = 0; // Se agiu, considera-se que comeu
        } catch (const exception& e) {
            cout << UI::VERMELHO << "[MORTE]: " << e.what() << UI::RESET << endl;
        }
    }
};

// --- 5. RESERVA NATURAL (GESTORA) ---

class Reserva {
private:
    vector<SerVivo*> seres;
    int ciclo;

public:
    Reserva() : ciclo(0) {}

    void adicionar(SerVivo* s) { seres.push_back(s); }

    void passarCiclo() {
        ciclo++;
        cout << "\n=== EXECUTANDO CICLO " << ciclo << " ===" << endl;
        for (auto s : seres) {
            if (s->isVivo()) s->agir();
        }
    }

    void mostrarStatus() {
        cout << "\n" << UI::CIANO << "--- DASHBOARD DA BIODIVERSIDADE ---" << UI::RESET << endl;
        cout << left << setw(15) << "NOME" << setw(12) << "ESPÉCIE" << setw(10) << "ENERGIA" << "STATUS" << endl;
        cout << "----------------------------------------------------" << endl;
        for (auto s : seres) {
            cout << left << setw(15) << s->getNome() 
                 << setw(12) << s->getEspecie() 
                 << setw(10) << s->getEnergia() 
                 << (s->isVivo() ? UI::VERDE + "VIVO" : UI::VERMELHO + "MORTO") << UI::RESET << endl;
        }
        cout << "População Total Ativa: " << SerVivo::getPopulacao() << endl;
    }

    ~Reserva() { for (auto s : seres) delete s; }
};

// --- 6. MAIN INTERATIVA ---

int main()
{
    Reserva reserva;
    int opcao = 0;

    do {
        UI::limparTela();
        cout << UI::CIANO << "===============================================" << endl;
        cout << "      LABORATÓRIO BIO-CPP: GESTÃO DE VIDA      " << endl;
        cout << "===============================================" << UI::RESET << endl;
        
        reserva.mostrarStatus();

        cout << "\n[1] Adicionar Planta  [2] Adicionar Herbívoro  [3] Adicionar Carnívoro" << endl;
        cout << "[4] Executar Ciclo Vital  [5] Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao >= 1 && opcao <= 3) {
            string nome;
            cout << "Dê um nome ao espécime: ";
            getline(cin >> ws, nome);
            
            if (opcao == 1) reserva.adicionar(new Planta(nome));
            else if (opcao == 2) reserva.adicionar(new Herbivoro(nome));
            else if (opcao == 3) reserva.adicionar(new Carnivoro(nome));
            
            cout << UI::VERDE << "[OK]: Vida gerada com sucesso!" << UI::RESET << endl;
            system("sleep 1");
        } 
        else if (opcao == 4) {
            reserva.passarCiclo();
            cout << "\nPressione ENTER para continuar...";
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (opcao != 5);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ECOSSISTEMA INTERATIVO (POO II)
    ===============================================================

    1. GESTÃO DE COLEÇÕES POLIMÓRFICAS:
       - O vetor armazena ponteiros 'SerVivo*', mas o menu decide 
         qual "tipo real" (new Planta, new Herbivoro) será criado. 
         Isso é a essência de sistemas extensíveis.

    2. MECÂNICA DE ENERGIA E MORTE:
       - Cada ciclo reduz energia dos animais (envelhecimento). 
         Se a energia chega a zero, o objeto entra no estado 
         "morto" e é removido da contagem estática.

    3. EXCEÇÕES COMO EVENTOS BIOLÓGICOS:
       - Usamos o throw para sinalizar a morte por inanição. Isso 
         separa a lógica de "viver" da lógica de "morrer", 
         facilitando a manutenção do simulador.

    4. VISUALIZAÇÃO DE ESTADO INTERNO:
       - O Dashboard demonstra que, embora o ponteiro seja genérico, 
         conseguimos acessar dados específicos e o comportamento 
         correto de cada objeto através da vtable (Virtual Table).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Garbage Collection vs Destrutores Manuais.
    - Padrão Factory: Criar objetos sem conhecer sua classe exata.
    - Simulação Monte Carlo: Usar aleatoriedade para os ciclos.
    ===============================================================
*/
