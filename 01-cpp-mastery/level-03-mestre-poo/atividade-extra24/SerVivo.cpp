#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file SerVivo.cpp
 * @brief Implementação da hierarquia de seres vivos e UI.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Ecosystem Complex Layout)
 * - SerVivo/Planta/Animal: Instâncias alocadas dinamicamente na HEAP via 'new'.
 * - Membros Estáticos (populacaoAtiva): Alocados no DATA SEGMENT (Compartilhados).
 * - V-Table: Localizada no DATA SEGMENT, permitindo chamadas dinâmicas a agir().
 * - Stack: Armazena variáveis locais e ponteiros para objetos na Heap.
 */

#include "SerVivo.h"

using namespace std;

// --- UI ---
void UI::banner() {
    cout << UI::VERDE << UI::NEGRITO << "===============================================" << endl;
    cout << "      BIO-CPP v2.0: SIMULADOR DE VIDA          " << endl;
    cout << "       (Elite Computational Biology)           " << endl;
    cout << "===============================================" << UI::RESET << endl;
}

// --- EventoNatureza ---
EventoNatureza::EventoNatureza(string m) : msg(UI::AMARELO + "[EVENTO]: " + m + UI::RESET) {}
const char* EventoNatureza::what() const throw() { return msg.c_str(); }

// --- SerVivo ---
int SerVivo::populacaoAtiva = 0;

SerVivo::SerVivo(const string& _nome, const string& _esp, int _ene) 
    : nome(_nome), especie(_esp), energia(_ene), vivo(true) 
{
    populacaoAtiva++;
}

bool SerVivo::isVivo() const { return vivo; }
const string& SerVivo::getNome() const { return nome; }
const string& SerVivo::getEspecie() const { return especie; }
int SerVivo::getEnergia() const { return energia; }

void SerVivo::morrer() { 
    if(vivo) {
        vivo = false; 
        populacaoAtiva--;
    }
}

int SerVivo::getPopulacao() { return populacaoAtiva; }

SerVivo::~SerVivo() {
    if (vivo) populacaoAtiva--;
}

// --- Planta ---
Planta::Planta(const string& _nome) : SerVivo(_nome, "Planta", 30) {}

void Planta::agir() {
    if (!vivo) return;
    energia += 15;
    cout << UI::VERDE << "[FOTOSSÍNTESE]: " << nome << " sintetizou +15 de energia solar." << UI::RESET << endl;
}

// --- Animal ---
Animal::Animal(const string& _nome, const string& _esp, int _ene) 
    : SerVivo(_nome, _esp, _ene), fome(0) {}

void Animal::metabolizar() {
    fome += 5;
    energia -= 8;
    if (fome > 25 || energia <= 0) {
        morrer();
        throw EventoNatureza("Espécime '" + nome + "' faleceu por inanição.");
    }
}

// --- Herbivoro ---
Herbivoro::Herbivoro(const string& _nome) : Animal(_nome, "Herbívoro", 40) {}

void Herbivoro::agir() {
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

// --- Carnivoro ---
Carnivoro::Carnivoro(const string& _nome) : Animal(_nome, "Carnívoro", 55) {}

void Carnivoro::agir() {
    if (!vivo) return;
    try {
        metabolizar();
        cout << UI::VERMELHO << "[CAÇANDO]: " << nome << " realizou abate bem-sucedido (-12 energia de combate)." << UI::RESET << endl;
        energia -= 12;
        fome = 0;
        energia += 25;
    } catch (const exception& e) {
        cout << UI::VERMELHO << e.what() << UI::RESET << endl;
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ECOSSISTEMAS COMPUTACIONAIS E POO III
    ===============================================================

    1. ABSTRAÇÃO DE NÍVEIS: Hierarquia de SerVivo -> Animal -> Carnivoro.
    2. GESTÃO DE VIDA ÚTIL: Uso de destrutores virtuais para limpeza na Heap.
    3. POLIMORFISMO: Uso de vtables para chamadas dinâmicas de agir().
    4. RESILIÊNCIA: Uso de exceções para eventos de negócio (morte).
    ===============================================================
*/

