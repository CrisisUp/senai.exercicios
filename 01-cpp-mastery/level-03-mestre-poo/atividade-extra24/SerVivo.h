/**
 * @file SerVivo.h
 * @brief Definições da hierarquia de seres vivos e eventos biológicos.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef SER_VIVO_H
#define SER_VIVO_H

#include <iostream>
#include <string>
#include <exception>

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
    void banner();
}

// --- 2. GESTÃO DE EVENTOS BIOLÓGICOS (EXCEÇÕES) ---
class EventoNatureza : public std::exception {
    std::string msg;
public:
    EventoNatureza(std::string m);
    const char* what() const throw() override;
};

// --- 3. CLASSE ABSTRATA BASE: SER VIVO ---
/**
 * @class SerVivo
 * @brief Base abstrata para qualquer entidade biológica no simulador.
 */
class SerVivo {
protected:
    std::string nome;
    std::string especie;
    int energia;
    bool vivo;

    static int populacaoAtiva; // Membro Estático (Global)

public:
    SerVivo(const std::string& _nome, const std::string& _esp, int _ene);
    virtual void agir() = 0;

    bool isVivo() const;
    const std::string& getNome() const;
    const std::string& getEspecie() const;
    int getEnergia() const;
    
    void morrer();
    static int getPopulacao();

    virtual ~SerVivo();
};

// --- 4. CLASSES ESPECIALIZADAS ---

class Planta : public SerVivo {
public:
    Planta(const std::string& _nome);
    void agir() override;
};

class Animal : public SerVivo {
protected:
    int fome;
public:
    Animal(const std::string& _nome, const std::string& _esp, int _ene);
    void metabolizar();
};

class Herbivoro : public Animal {
public:
    Herbivoro(const std::string& _nome);
    void agir() override;
};

class Carnivoro : public Animal {
public:
    Carnivoro(const std::string& _nome);
    void agir() override;
};

#endif // SER_VIVO_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
