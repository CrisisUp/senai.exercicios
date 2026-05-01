/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file MaquinaAgricola.h
 * @brief Definições da classe base MaquinaAgricola e derivada Trator.
 */

#ifndef MAQUINA_AGRICOLA_H
#define MAQUINA_AGRICOLA_H

#include <iostream>
#include <string>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { std::cout << "\033[2J\033[1;1H"; }
}

// --- 2. CLASSE BASE (MÃE) ---
class MaquinaAgricola {
protected:
    std::string id;
    std::string marca;
    double combustivel;

public:
    MaquinaAgricola(const std::string& _id, const std::string& _marca);
    void abastecer();
    void exibirBase() const;
};

// --- 3. CLASSE DERIVADA (FILHA) ---
class Trator : public MaquinaAgricola {
private:
    double capacidadeReboque;

public:
    Trator(const std::string& _id, const std::string& _marca, double _cap);
    void ararTerra();
    void exibirStatus() const;
};

#endif // MAQUINA_AGRICOLA_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
