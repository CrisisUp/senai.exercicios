/**
 * @file atividade-extra32-observer.cpp
 * @brief Monitoramento Climático: Implementação do Design Pattern Observer.
 * 
 * Demonstra como criar um sistema de notificações em tempo real, onde
 * múltiplos objetos são atualizados automaticamente quando o estado de
 * um objeto principal muda.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
}

// --- 2. INTERFACE DO OBSERVADOR (CONTRATO) ---

class IObservador {
public:
    virtual void atualizar(double temp, double umid) = 0;
    virtual ~IObservador() {}
};

// --- 3. O SUJEITO (ESTAÇÃO METEOROLÓGICA) ---

class EstacaoClimatica {
private:
    vector<IObservador*> observadores;
    double temperatura;
    double umidade;

public:
    void registrarObservador(IObservador* obs) {
        observadores.push_back(obs);
    }

    void removerObservador(IObservador* obs) {
        observadores.erase(remove(observadores.begin(), observadores.end(), obs), observadores.end());
    }

    void notificarTodos() {
        for (IObservador* obs : observadores) {
            obs->atualizar(temperatura, umidade);
        }
    }

    void setMedicoes(double t, double u) {
        this->temperatura = t;
        this->umidade = u;
        cout << "\n[ESTAÇÃO]: Novas medições recebidas (T: " << t << "°C, U: " << u << "%)" << endl;
        notificarTodos(); // O "Pulo do Gato": Avisa a todos no momento da mudança
    }
};

// --- 4. OBSERVADORES CONCRETOS ---

class DisplayTV : public IObservador {
public:
    void atualizar(double temp, double umid) override {
        cout << UI::CIANO << " >> [TV PRAÇA]: Temperatura atual: " << temp << "°C | Umidade: " << umid << "%" << UI::RESET << endl;
    }
};

class AppCelular : public IObservador {
private:
    string usuario;
public:
    AppCelular(string u) : usuario(u) {}
    void atualizar(double temp, double umid) override {
        cout << UI::VERDE << " >> [CELULAR (" << usuario << ")]: Notificação Push! O clima mudou." << UI::RESET << endl;
    }
};

class AlertaDefesaCivil : public IObservador {
public:
    void atualizar(double temp, double umid) override {
        if (temp > 40.0 || umid < 20.0) {
            cout << "\033[31m >> [DEFESA CIVIL]: ALERTA CRÍTICO! Condições climáticas perigosas." << UI::RESET << endl;
        }
    }
};

// --- 5. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      CENTRAL METEOROLÓGICA METEO-SENS v1.0    " << endl;
    cout << "===============================================" << UI::RESET << endl;

    EstacaoClimatica estacao;

    // Criando os dispositivos (Observadores)
    DisplayTV tvPraca;
    AppCelular meuApp("Cristiano");
    AlertaDefesaCivil defesaCivil;

    // "Inscrição" no sistema de notificações
    estacao.registrarObservador(&tvPraca);
    estacao.registrarObservador(&meuApp);
    estacao.registrarObservador(&defesaCivil);

    cout << "[SISTEMA]: " << 3 << " dispositivos conectados via rádio." << endl;

    // Simulação 1: Dia ensolarado normal
    estacao.setMedicoes(28.5, 60.0);

    // Simulação 2: Onda de calor extrema
    estacao.setMedicoes(42.3, 15.0);

    // Cancelando uma inscrição
    cout << "\n[SISTEMA]: Usuário 'Cristiano' desconectou o App." << endl;
    estacao.removerObservador(&meuApp);

    // Simulação 3: Mudança de tempo
    estacao.setMedicoes(22.0, 85.0);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESIGN PATTERN OBSERVER
    ===============================================================

    1. O CONCEITO DE NOTIFICAÇÃO (Push):
       - Em vez de 1000 dispositivos ficarem perguntando "já mudou?" 
         para a estação (o que gastaria bateria e rede), a estação 
         fica em silêncio e apenas "empurra" a informação quando 
         ela realmente acontece.

    2. ACOPLAMENTO FRACO (Loose Coupling):
       - A classe 'EstacaoClimatica' não sabe NADA sobre TVs ou Apps. 
         Ela apenas tem uma lista de ponteiros 'IObservador'. Isso 
         permite adicionar novos tipos de observadores sem mudar 
         uma linha de código da estação.

    3. INTERFACE COMO CONTRATO:
       - O segredo é o método virtual puro 'atualizar()'. Ele 
         garante que qualquer objeto que queira ouvir a estação 
         saiba como reagir aos dados recebidos.

    4. QUANDO USAR:
       - Sempre que a mudança de estado em um objeto exigir a 
         mudança em outros, e você não souber quantos objetos 
         precisará mudar. (Base do modelo MVC - Model View Controller).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Pub/Sub (Publisher/Subscriber): Uma versão mais robusta usada 
      em sistemas distribuídos.
    - Event-Driven Programming: Programação baseada em eventos.
    - Ponteiros Inteligentes (shared_ptr): Para gerenciar a vida 
      dos observadores.
    ===============================================================
*/
