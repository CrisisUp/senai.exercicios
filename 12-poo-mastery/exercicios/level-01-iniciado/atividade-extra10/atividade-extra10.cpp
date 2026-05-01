#define ANSI_RESET "\033[0m"
/**
 * @file atividade-extra10.cpp
 * @brief Implementação/Componente atividade-extra10.cpp
 * @author Cristiano
 * @date 2026
 */
#include <iostream>
#include <string>

class Drone {
private:
    int idSecreto;
    std::string modelo;
    friend class AuditoriaNexus; // Amizade!

public:
    Drone(std::string m, int id) : modelo(m), idSecreto(id) {}
};

class AuditoriaNexus {
public:
    void inspecionar(const Drone& d) {
        std::cout << "[AUDITORIA] Acessando ID secreto do " << d.modelo << ": " << d.idSecreto << std::endl;
    }
};

int main() {
    Drone d1("Stealth-01", 999888);
    AuditoriaNexus auditor;
    
    // std::cout << d1.idSecreto; // ERRO: idSecreto is private
    
    auditor.inspecionar(d1);
    
    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
