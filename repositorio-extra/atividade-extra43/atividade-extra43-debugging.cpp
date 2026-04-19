/**
 * @file atividade-extra43-debugging.cpp
 * @brief Laboratório de Debugging: Encontre os 3 erros críticos.
 * 
 * ATENÇÃO: Este código contém falhas propositais de lógica, memória e 
 * validação para fins educacionais de "Bug Hunting".
 * 
 * @author SENAI - Engenheiro Júnior (Com Erros)
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- 1. CLASSE SEMÁFORO (BUG DE MEMÓRIA AQUI) ---

class Semaforo {
public:
    string local;
    Semaforo(string l) : local(l) {}
    void operar() { cout << "[SISTEMA]: Semáforo em " << local << " operando." << endl; }
};

// --- 2. GESTOR DE TRÁFEGO ---

class GestorTrafego {
private:
    vector<Semaforo*> rede;
public:
    void adicionarSemaforo(string loc) {
        rede.push_back(new Semaforo(loc));
    }

    void testarRede() {
        // BUG LÓGICO: O loop está correto? Olhe os limites.
        for (int i = 0; i <= rede.size(); i++) {
            cout << "Testando dispositivo " << i << "... ";
            rede[i]->operar();
        }
    }

    // BUG DE MEMÓRIA: O que falta no Destrutor para uma rede de ponteiros crus?
    ~GestorTrafego() {
        cout << "[SISTEMA]: Gestor encerrado." << endl;
    }
};

// --- 3. VALIDADOR (BUG DE SEGURANÇA AQUI) ---

class ValidadorSimple {
public:
    int lerOpcao() {
        int opt;
        cout << "Escolha (1-Produção / 2-Sair): ";
        cin >> opt; 
        // BUG DE SEGURANÇA: E se o usuário digitar uma letra? O buffer está protegido?
        return opt;
    }
};

// --- 4. MAIN ---

int main() {
    GestorTrafego gCity;
    ValidadorSimple val;

    gCity.adicionarSemaforo("Av. Central");
    gCity.adicionarSemaforo("Rua das Flores");

    int o = val.lerOpcao();
    if (o == 1) {
        gCity.testarRede();
    }

    return 0;
}

/* 
    ===============================================================
    MISSÃO: BUG HUNTING
    ===============================================================
    Existem 3 erros neste código que impediriam sua homologação.
    
    1. ERRO DE ACESSO (Crash): O loop na função testarRede() vai 
       causar um erro de 'Segmentation Fault'. Por quê?
    
    2. VAZAMENTO (Leak): A classe GestorTrafego aloca semáforos 
       usando 'new', mas onde eles são liberados?
    
    3. TRAVAMENTO (Freeze): O ValidadorSimple não limpa o buffer. 
       O que acontece se digitarmos 'X' no menu?

    ===============================================================
    RESUMO TEÓRICO (O que você deve aplicar na correção):
    - Limites de Vetores (0 a size-1).
    - RAII e Gerenciamento de Memória Dinâmica.
    - Robustez de Entrada (cin.clear/ignore).
    ===============================================================
*/
