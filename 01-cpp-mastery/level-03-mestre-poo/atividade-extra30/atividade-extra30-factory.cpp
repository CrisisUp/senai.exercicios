/**
 * @file atividade-extra30-factory.cpp
 * @brief Cyber-Factory: Implementação do Design Pattern Factory Method.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a abstração de criação e o desacoplamento de instâncias polimórficas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Factory Pattern Layout)
 * - FabricaDeRobos (Static): Não ocupa espaço de instância. Seus métodos vivem no CODE SEGMENT.
 * - Frota (vector): O container de controle vive na STACK.
 * - Robôs (Drones/Androids): Alocados dinamicamente na HEAP pela Fábrica.
 * - Ciclo de Vida: A Fábrica entrega a posse do objeto para a main(), que se 
 *   torna responsável pela destruição final na HEAP.
 */

#include <iostream>
#include <string>
#include <vector>
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

// --- 2. PRODUTO ABSTRATO (CONTRATO) ---

/**
 * @class Robo
 * @brief Define a interface básica para qualquer unidade robótica.
 */
class Robo {
protected:
    string modelo;
public:
    virtual void executarTarefa() const = 0; 
    
    // FANTASMA DO CPU: Retorno por referência constante
    const string& getModelo() const { return modelo; }
    
    virtual ~Robo() {
        cout << UI::AMARELO << "[DESCARTE]: Hardware do " << modelo << " reciclado." << UI::RESET << endl;
    }
};

// --- 3. PRODUTOS CONCRETOS (ESPECIALIZAÇÕES) ---

class DroneVigilancia : public Robo {
public:
    DroneVigilancia() { modelo = "Drone-SkyEye v4"; }
    void executarTarefa() const override {
        cout << UI::VERDE << "[SCANNER]: " << modelo << " patrulhando perímetro via infravermelho." << UI::RESET << endl;
    }
};

class BracoRobotico : public Robo {
public:
    BracoRobotico() { modelo = "Arm-Titan X"; }
    void executarTarefa() const override {
        cout << UI::AZUL << "[SOLDAGEM]: " << modelo << " realizando união de precisão em chassis." << UI::RESET << endl;
    }
};

class AndroidLimpeza : public Robo {
public:
    AndroidLimpeza() { modelo = "CleanBot-9000"; }
    void executarTarefa() const override {
        cout << UI::AMARELO << "[HIGIENE]: " << modelo << " operando descontaminação química nível 4." << UI::RESET << endl;
    }
};

// --- 4. A FÁBRICA (FACTORY METHOD CORE) ---

/**
 * @class FabricaDeRobos
 * @brief Encapsula a lógica de criação. Isola a main() das classes concretas.
 */
class FabricaDeRobos {
public:
    /**
     * @brief Método Factory Estático.
     * @param tipo Identificador numérico da linha de produção.
     * @return Robo* Ponteiro polimórfico (O cliente não conhece a classe real).
     */
    static Robo* produzirRobo(int tipo) {
        // A main() não precisa de includes dos robôs específicos, apenas da fábrica
        switch (tipo) {
            case 1: return new DroneVigilancia();
            case 2: return new BracoRobotico();
            case 3: return new AndroidLimpeza();
            default: return nullptr;
        }
    }
};

// --- 5. EXECUÇÃO DA LINHA DE PRODUÇÃO ---

int main()
{
    int escolha = 0;
    vector<Robo*> frota;

    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      CYBER-FACTORY: GESTÃO DE PRODUÇÃO v2.0   " << endl;
    cout << "       (Elite Factory Design Pattern)          " << endl;
    cout << "===============================================" << UI::RESET << endl;

    do {
        cout << "\n" << UI::RESET << "LINHA DE MONTAGEM DISPONÍVEL:" << UI::RESET << endl;
        cout << "[1] Drone SkyEye  [2] Braço Titan  [3] Android CleanBot" << endl;
        cout << "[4] Testar Lote   [5] Desligar Planta" << endl;
        cout << UI::CIANO << "Solicitar Unidade: " << UI::RESET;
        
        if (!(cin >> escolha)) break;

        if (escolha >= 1 && escolha <= 3) {
            // PADRÃO FACTORY: O cliente pede "o que", mas não sabe "como" criar.
            Robo* novoRobo = FabricaDeRobos::produzirRobo(escolha);
            
            if (novoRobo) {
                cout << UI::VERDE << UI::NEGRITO << "[SUCESSO]: Unidade " << novoRobo->getModelo() << " pronta para despacho!" << UI::RESET << endl;
                frota.push_back(novoRobo);
            }
        } 
        else if (escolha == 4) {
            cout << "\n" << UI::NEGRITO << "--- TESTE DE FUNCIONALIDADE EM TEMPO REAL ---" << UI::RESET << endl;
            if (frota.empty()) cout << UI::VERMELHO << "ALERTA: Linha de produção vazia." << UI::RESET << endl;
            
            for (const auto* r : frota) {
                if (r) r->executarTarefa();
            }
        }

    } while (escolha != 5);

    // --- CICLO DE DESALOCAÇÃO INDUSTRIAL ---
    cout << "\n" << UI::RESET << "[SISTEMA]: Iniciando desligamento e limpeza de hardware..." << UI::RESET << endl;
    for (auto& r : frota) {
        delete r; 
        r = nullptr;
    }
    frota.clear();

    cout << UI::VERDE << UI::NEGRITO << "\nProdução finalizada. Fábrica em modo Stand-by." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESIGN PATTERNS (FACTORY METHOD)
    ===============================================================

    1. DESACOPLAMENTO (DECOUPLING):
       - É o maior ganho do Factory. A função main() nunca chama 
         'new DroneVigilancia'. Se o nome dessa classe mudar para 
         'DroneV5', apenas a fábrica precisa ser editada. O resto 
         do sistema permanece intacto.

    2. CENTRALIZAÇÃO DE REGRAS:
       - A fábrica pode conter regras complexas de criação (ex: 
         só criar Android se houver bateria em estoque), sem poluir 
         o código principal do sistema.

    3. PRINCÍPIO ABERTO-FECHADO (OCP):
       - O sistema está aberto para novas expansões (novos robôs) 
         e fechado para modificações que poderiam quebrar o 
         código estável da interface.

    4. GESTÃO DE MEMÓRIA EM DESIGN PATTERNS:
       - Embora o Factory crie o objeto, a RESPONSABILIDADE da 
         memória (ownership) é transferida para quem chamou a 
         fábrica. Em C++ moderno, usaríamos std::unique_ptr para 
         automatizar essa transferência de posse.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Abstract Factory: Quando os robôs precisam de peças de 
      diferentes fornecedores.
    - Prototype Pattern: Clonar robôs existentes ao invés de 
      criar do zero.
    - Smart Pointers: std::unique_ptr<Robo> Factory::criar().
    ===============================================================
*/
