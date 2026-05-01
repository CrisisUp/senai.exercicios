#define ANSI_RESET "\033[0m"
#include "Interfaces.h"
#include <iostream>
#include <string>

/**
 * @file main.cpp
 * @brief Implementação da Atividade 28 - ISP (Interface Segregation Principle).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 */

// 1. Drone Entregador: Só precisa voar e carregar peso.
class DroneEntregador : public IVoador, public ICargueiro {
private:
    std::string id;
public:
    DroneEntregador(std::string name) : id(name) {}

    void decolar() override { std::cout << "[Voo] Entregador " << id << " decolando..." << std::endl; }
    void pousar() override { std::cout << "[Voo] Entregador " << id << " pousando no destino." << std::endl; }
    
    void carregarCarga(float peso) override { std::cout << "[Carga] " << peso << "kg acoplados ao " << id << std::endl; }
    void soltarCarga() override { std::cout << "[Carga] Encomenda entregue por " << id << std::endl; }
};

// 2. Drone Espião: Só precisa voar e capturar imagens.
class DroneEspiao : public IVoador, public ICamera {
private:
    std::string id;
public:
    DroneEspiao(std::string name) : id(name) {}

    void decolar() override { std::cout << "[Stealth] Espião " << id << " decolagem silenciosa..." << std::endl; }
    void pousar() override { std::cout << "[Stealth] Espião " << id << " retornando à base." << std::endl; }

    void tirarFoto() override { std::cout << "[Foto] Imagem infravermelha capturada por " << id << std::endl; }
    void gravarVideo() override { std::cout << "[Vídeo] Transmissão criptografada iniciada por " << id << std::endl; }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Segregação de Interfaces ISP ---" << std::endl;

    std::cout << "\n1. Operação de Entrega:" << std::endl;
    DroneEntregador entregador("Cargo-Alpha");
    entregador.decolar();
    entregador.carregarCarga(25.5);
    entregador.soltarCarga();
    entregador.pousar();

    std::cout << "\n2. Operação de Reconhecimento:" << std::endl;
    DroneEspiao espiao("Shadow-Eye");
    espiao.decolar();
    espiao.tirarFoto();
    espiao.gravarVideo();
    espiao.pousar();

    /*
     * RESUMO TEÓRICO:
     * O ISP (Interface Segregation Principle) afirma que clientes não devem ser 
     * forçados a depender de interfaces que não usam.
     * 
     * Ao dividir 'IDrone' (gorda) em 'IVoador', 'ICamera' e 'ICargueiro' (magras):
     * - O DroneEntregador não é forçado a ter métodos de câmera (o que geraria 
     *   implementações vazias ou erros).
     * - O código fica mais limpo, coeso e fácil de manter.
     */

    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */
