#include <iostream>
#include <vector>
#include <memory>
#include "Drone.h"

int main() {
    std::cout << BOLD << YELLOW << "--- SKYCARGO NEXUS: PROTOCOLO GUARDIÃO ---" << RESET << std::endl << std::endl;

    // 1. Gestão Moderna com Shared Pointers (Ativ 16)
    std::vector<std::shared_ptr<Drone>> frota;

    try {
        std::cout << "[MISSAO] Inicializando frota de elite..." << std::endl;
        
        auto alpha = std::make_shared<Drone>("Alpha-707", 90);
        frota.push_back(alpha);
        
        // Teste de Deep Copy (Atividade 12)
        std::cout << "[SISTEMA] Solicitando backup para Alpha-707..." << std::endl;
        auto alphaClone = std::make_shared<Drone>(*alpha); // Chama o construtor de cópia
        frota.push_back(alphaClone);

        // 2. Teste de Resiliência e Exceções (Atividade 17)
        std::cout << std::endl << "[AVISO] Tentando configurar unidade com carga impossível..." << std::endl;
        alphaClone->setBateria(150); // Isso vai disparar a exceção!

    } catch (const BateriaInvalidaException& e) {
        std::cout << RED << BOLD << ">>> RESGATE DE ERRO: " << e.what() << RESET << std::endl;
        std::cout << YELLOW << "[SISTEMA] Protocolo de segurança ativado. Erro contido." << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erro genérico: " << e.what() << std::endl;
    }

    std::cout << std::endl << "[SISTEMA] Relatório de unidades sobreviventes:" << std::endl;
    for (const auto& d : frota) {
        d->verStatus();
    }

    std::cout << std::endl << YELLOW << "[SISTEMA] Finalizando hangar. Smart pointers assumem o controle..." << RESET << std::endl;
    
    // 3. O Fim do 'delete' manual (Ativ 15 e 16)
    frota.clear(); // Ao limpar o vetor, a contagem de shared_ptr cai para zero e o delete é automático.

    std::cout << std::endl << BOLD << YELLOW << "--- MISSÃO CONCLUÍDA: ZERO MEMORY LEAKS ---" << RESET << std::endl;

    return 0;
}
