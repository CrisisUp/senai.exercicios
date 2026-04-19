/**
 * @file atividade-extra30-factory.cpp
 * @brief Fábrica de Robôs: Implementação do Design Pattern Factory Method.
 * 
 * Demonstra como centralizar a lógica de criação de objetos polimórficos,
 * promovendo o desacoplamento e a facilidade de expansão do sistema.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string NEGRITO  = "\033[1m";
}

// --- 2. PRODUTO ABSTRATO ---

class Robo {
protected:
    string modelo;
public:
    virtual void executarTarefa() = 0; // Contrato
    string getModelo() const { return modelo; }
    virtual ~Robo() {}
};

// --- 3. PRODUTOS CONCRETOS ---

class DroneVigilancia : public Robo {
public:
    DroneVigilancia() { modelo = "Drone-SkyEye v4"; }
    void executarTarefa() override {
        cout << UI::VERDE << "[ROBÔ]: " << modelo << " patrulhando perímetro via infravermelho." << UI::RESET << endl;
    }
};

class BracoRobotico : public Robo {
public:
    BracoRobotico() { modelo = "Arm-Titan X"; }
    void executarTarefa() override {
        cout << UI::AZUL << "[ROBÔ]: " << modelo << " realizando soldagem de precisão em chapa de aço." << UI::RESET << endl;
    }
};

class AndroidLimpeza : public Robo {
public:
    AndroidLimpeza() { modelo = "CleanBot-9000"; }
    void executarTarefa() override {
        cout << UI::AMARELO << "[ROBÔ]: " << modelo << " higienizando área laboratorial nível 4." << UI::RESET << endl;
    }
};

// --- 4. A FÁBRICA (O PADRÃO FACTORY METHOD) ---

class FabricaDeRobos {
public:
    /**
     * @brief Método Factory centralizado.
     * @param tipo String identificando o modelo.
     * @return Ponteiro para a classe base Robo (Polimorfismo).
     */
    static Robo* produzirRobo(int tipo) {
        switch (tipo) {
            case 1: return new DroneVigilancia();
            case 2: return new BracoRobotico();
            case 3: return new AndroidLimpeza();
            default: return nullptr;
        }
    }
};

// --- 5. FUNÇÃO PRINCIPAL ---

int main()
{
    int escolha = 0;
    vector<Robo*> frota;

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      CYBER-FACTORY: GESTÃO DE PRODUÇÃO        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    do {
        cout << "\n--- LINHA DE MONTAGEM ---" << endl;
        cout << "[1] Produzir Drone  [2] Produzir Braço  [3] Produzir Android" << endl;
        cout << "[4] Testar Frota Ativa  [5] Encerrar Produção" << endl;
        cout << "Escolha: ";
        cin >> escolha;

        if (escolha >= 1 && escolha <= 3) {
            // O cliente (main) não sabe quais classes existem, 
            // ele apenas pede para a FÁBRICA produzir.
            Robo* novoRobo = FabricaDeRobos::produzirRobo(escolha);
            
            if (novoRobo) {
                cout << UI::VERDE << "[SUCESSO]: " << novoRobo->getModelo() << " saiu da linha de montagem!" << UI::RESET << endl;
                frota.push_back(novoRobo);
            }
        } 
        else if (escolha == 4) {
            cout << "\n--- TESTE DE FUNCIONALIDADE EM LOTE ---" << endl;
            if (frota.empty()) cout << "(Nenhum robô na frota)" << endl;
            for (auto r : frota) {
                r->executarTarefa();
            }
        }

    } while (escolha != 5);

    // Limpeza (Poderíamos usar unique_ptr, mas aqui focamos na lógica manual para fixar)
    for (auto r : frota) delete r;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESIGN PATTERN FACTORY
    ===============================================================

    1. O PROBLEMA DO 'NEW':
       - Usar 'new' espalhado pelo código cria acoplamento forte. Se 
         o nome de uma classe mudar, você terá que alterar em dezenas 
         de lugares.

    2. A SOLUÇÃO FACTORY:
       - Centralizamos a criação em um único método. Isso "esconde" 
         a complexidade da instanciação. O código que usa o robô 
         só conhece a classe base 'Robo'.

    3. PRINCÍPIO ABERTO/FECHADO (SOLID):
       - O sistema está "Aberto para Extensão" (podemos criar 
         novos robôs) e "Fechado para Modificação" (não precisamos 
         mudar o loop de teste na main para o novo robô funcionar).

    4. QUANDO USAR:
       - Use quando o seu sistema não souber antecipadamente os 
         tipos exatos de objetos que deve criar, ou quando quiser 
         centralizar regras de criação (ex: bônus de jogo, tipos de 
         arquivos, métodos de criptografia).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Abstract Factory: Fábrica de Fábricas.
    - Singleton: Garantir que exista apenas uma instância da Fábrica.
    - Dependency Injection: Passar a fábrica para quem precisa dela.
    ===============================================================
*/
