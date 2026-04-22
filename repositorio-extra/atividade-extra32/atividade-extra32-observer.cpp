/**
 * @file atividade-extra32-observer.cpp
 * @brief Meteo-Sens: Implementação do Design Pattern Observer de Elite.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a comunicação assíncrona lógica e o desacoplamento de telemetria.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Observer Pattern Layout)
 * - EstacaoClimatica (Subject): Objeto na STACK. Gerencia um vector de ponteiros na HEAP.
 * - Observadores (TV/App/Defesa): Podem estar na STACK (neste exemplo) ou HEAP.
 * - Polimorfismo: O Subject armazena apenas endereços de memória. A chamada 
 *   atualizar() desvia para o código específico via V-TABLE do observador.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string VERMELHO = "\033[31m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. INTERFACE DO OBSERVADOR (CONTRATO) ---

/**
 * @class IObservador
 * @brief Interface abstrata que define o comportamento de resposta a eventos climáticos.
 */
class IObservador {
public:
    virtual void atualizar(double temp, double umid) = 0;
    virtual ~IObservador() {}
};

// --- 3. O SUJEITO (ESTAÇÃO METEOROLÓGICA CORE) ---

class EstacaoClimatica {
private:
    vector<IObservador*> observadores; // Lista de assinantes (Loose Coupling)
    double temperatura;
    double umidade;

public:
    /**
     * @brief Registra um novo interessado no sinal climátido.
     */
    void registrarObservador(IObservador* obs) {
        if (obs) observadores.push_back(obs);
    }

    /**
     * @brief Remove a inscrição de um observador (Evita Dangling Pointers).
     */
    void removerObservador(IObservador* obs) {
        observadores.erase(remove(observadores.begin(), observadores.end(), obs), observadores.end());
    }

    /**
     * @brief Sincronização em massa via Polimorfismo.
     */
    void notificarTodos() {
        for (auto* obs : observadores) {
            if (obs) obs->atualizar(temperatura, umidade);
        }
    }

    /**
     * @brief Atualiza sensores e dispara notificações instantâneas.
     */
    void setMedicoes(double t, double u) {
        this->temperatura = t;
        this->umidade = u;
        cout << "\n" << UI::BRANCO << "[SENSORES]: " << UI::RESET 
             << "Nova Telemetria (T: " << fixed << setprecision(1) << t << "°C, U: " << u << "%)" << endl;
        
        notificarTodos(); // O Coração do Padrão Observer
    }
};

// --- 4. OBSERVADORES CONCRETOS (DISPOSITIVOS) ---

class DisplayTV : public IObservador {
public:
    void atualizar(double temp, double umid) override {
        cout << UI::CIANO << " >> [TV PÚBLICA]: " << UI::RESET << "Temp: " << temp << "°C | Umidade: " << umid << "%" << endl;
    }
};

class AppCelular : public IObservador {
private:
    string usuario;
public:
    AppCelular(const string& u) : usuario(u) {}
    
    void atualizar(double temp, double umid) override {
        cout << UI::VERDE << " >> [APP " << usuario << "]: " << UI::RESET << "Notificação: Clima atualizado em sua região." << endl;
    }
};

class AlertaDefesaCivil : public IObservador {
public:
    void atualizar(double temp, double umid) override {
        if (temp > 40.0 || umid < 20.0) {
            cout << UI::VERMELHO << UI::NEGRITO << " >> [DEFESA CIVIL]: ALERTA DE RISCO! Condições de Incêndio/Insolação." << UI::RESET << endl;
        }
    }
};

// --- 5. EXECUÇÃO DA REDE DE MONITORAMENTO ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      METEO-SENS v2.0: MONITORAMENTO GLOBAL    " << endl;
    cout << "       (Elite Observer Design Pattern)         " << endl;
    cout << "===============================================" << UI::RESET << endl;

    EstacaoClimatica satelite;

    // Instanciação na STACK (Segurança de memória automática)
    DisplayTV monitorPraça;
    AppCelular appCristiano("Cristiano");
    AlertaDefesaCivil quartelGeneral;

    // Fase de Assinatura (Subscription)
    satelite.registrarObservador(&monitorPraça);
    satelite.registrarObservador(&appCristiano);
    satelite.registrarObservador(&quartelGeneral);

    cout << UI::BRANCO << "[SISTEMA]: Rede de malha ativa com 3 terminais conectados." << UI::RESET << endl;

    // Ciclo 1: Estabilidade
    satelite.setMedicoes(28.5, 62.0);

    // Ciclo 2: Alerta Crítico
    satelite.setMedicoes(43.1, 12.5);

    // Ciclo 3: Desconexão de Cliente
    cout << "\n" << UI::AMARELO << "[SISTEMA]: Usuário Cristiano encerrou a sessão no App." << UI::RESET << endl;
    satelite.removerObservador(&appCristiano);

    // Ciclo 4: Mudança de Frente Fria
    satelite.setMedicoes(19.8, 88.0);

    cout << UI::VERDE << UI::NEGRITO << "\nMonitoramento concluído. Todos os observadores sincronizados." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESIGN PATTERN OBSERVER (ELITE)
    ===============================================================

    1. INVERSÃO DE DEPENDÊNCIA:
       - A Estação Climatica não depende do AppCelular. Ambas 
         dependem da abstração 'IObservador'. Isso permite que o 
         sistema cresça infinitamente sem recompilar o núcleo da 
         estação.

    2. MECÂNICA DE BROADCAST (PUSH):
       - Eliminamos o "Polling" (objetos perguntando se mudou). 
         A notificação ocorre apenas quando o estado do Subject 
         realmente sofre alteração, economizando CPU e Energia.

    3. GESTÃO DE ASSINATURAS:
       - O uso de uma lista de ponteiros permite que a relação 
         entre os objetos seja decidida em tempo de execução 
         (Runtime). Um objeto pode começar a ouvir e parar de 
         ouvir a estação a qualquer momento.

    4. SEGURANÇA FANTASMA DO CPU:
       - Embora o loop de notificação seja O(n), as chamadas 
         polimórficas são extremamente rápidas. O uso de const 
         nas interfaces garante que nenhum observador altere os 
         dados da estação durante a leitura.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Signal/Slots (Qt Framework).
    - RxCpp (Reactive Extensions for C++).
    - Middleware Message Queues (RabbitMQ/Kafka).
    ===============================================================
*/
