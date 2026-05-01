/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file Aeronave.h
 * @brief Definições da classe base Aeronave e derivadas AviaoComercial e Helicoptero.
 */

#ifndef AERONAVE_H
#define AERONAVE_H

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

// --- 2. CLASSE BASE COM MÉTODOS VIRTUAIS ---
class Aeronave {
protected:
    std::string prefixo;

public:
    Aeronave(const std::string& _pref);
    virtual ~Aeronave();

    virtual void prepararParaDecolagem();
    virtual void decolar();
};

// --- 3. CLASSES DERIVADAS ---
class AviaoComercial : public Aeronave {
public:
    AviaoComercial(const std::string& _pref);
    void decolar() override;
};

class Helicoptero : public Aeronave {
public:
    Helicoptero(const std::string& _pref);
    void decolar() override;
};

#endif // AERONAVE_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
