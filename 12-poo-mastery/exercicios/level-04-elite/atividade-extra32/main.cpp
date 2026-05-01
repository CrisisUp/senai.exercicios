#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

/**
 * @file main.cpp
 * @brief Implementação do Design Pattern Observer para Telemetria Nexus.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Sujeito (Drone): Mantém uma lista de ponteiros para as interfaces IObserver.
 * - Observadores (Heap): São instanciados e registrados dinamicamente.
 */

// --- 1. INTERFACE OBSERVADOR (O Contrato) ---
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(int bateria, std::string status) = 0;
    virtual std::string getNome() const = 0;
};

// --- 2. SUJEITO (O Emissor de Eventos) ---
class DroneSubject {
private:
    std::vector<IObserver*> observadores;
    int bateria = 100;
    std::string status = "Em Base";

public:
    void registrarObservador(IObserver* obs) {
        observadores.push_back(obs);
        std::cout << "[Subject] Novo observador registrado: " << obs->getNome() << std::endl;
    }

    void removerObservador(IObserver* obs) {
        observadores.erase(
            std::remove(observadores.begin(), observadores.end(), obs),
            observadores.end()
        );
        std::cout << "[Subject] Observador removido: " << obs->getNome() << std::endl;
    }

    void notificar() {
        for (auto obs : observadores) {
            obs->update(bateria, status);
        }
    }

    void setEstado(int novaBateria, std::string novoStatus) {
        this->bateria = novaBateria;
        this->status = novoStatus;
        std::cout << "\n[Drone] Estado Alterado -> Bateria: " << bateria << "% | Status: " << status << std::endl;
        notificar();
    }
};

// --- 3. OBSERVADORES CONCRETOS ---

class MonitorBateria : public IObserver {
public:
    std::string getNome() const override { return "Analista de Energia"; }
    
    void update(int bateria, std::string status) override {
        if (bateria < 20) {
            std::cout << "\033[31m[ALERTA - " << getNome() << "] Bateria Crítica: " << bateria << "%! Pouse imediatamente.\033[0m" << std::endl;
        } else {
            std::cout << "\033[32m[Monitor - " << getNome() << "] Nível de energia nominal: " << bateria << "%\033[0m" << std::endl;
        }
    }
};

class EstacaoSolo : public IObserver {
public:
    std::string getNome() const override { return "Estação Nexus-Central"; }

    void update(int bateria, std::string status) override {
        std::cout << "\033[36m[Log - " << getNome() << "] Telemetria Recebida -> Status de Missão: " << status << "\033[0m" << std::endl;
    }
};

// --- 4. EXECUÇÃO ---

int main() {
    std::cout << "--- SkyCargo Nexus: Radar Reativo (Observer Pattern) ---" << std::endl;

    DroneSubject meuDrone;

    // Criando observadores
    auto monitor = std::make_unique<MonitorBateria>();
    auto estacao = std::make_unique<EstacaoSolo>();

    // Registrando no drone
    meuDrone.registrarObservador(monitor.get());
    meuDrone.registrarObservador(estacao.get());

    // Simulando mudanças de estado
    meuDrone.setEstado(85, "Em Voo");
    meuDrone.setEstado(50, "Carga Coletada");
    
    // Prova de Elite: Removendo um observador
    std::cout << "\n--- Desconectando Monitor de Bateria para Manutenção ---" << std::endl;
    meuDrone.removerObservador(monitor.get());

    meuDrone.setEstado(15, "Retornando"); // Apenas a Estação Solo deve receber esta notificação

    /*
     * RESUMO TEÓRICO:
     * O padrão Observer define uma dependência um-para-muitos entre objetos.
     * 
     * Benefícios:
     * 1. Baixo Acoplamento: O Drone não precisa saber o que o MonitorBateria faz.
     * 2. Extensibilidade: Podemos adicionar um 'MonitorVento' ou 'LogArquivo' 
     *    sem alterar o código do Drone.
     * 3. Reatividade: O sistema reage aos eventos conforme eles acontecem (Push model).
     */

    return 0;
}
