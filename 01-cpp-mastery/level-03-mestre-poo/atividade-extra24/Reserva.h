#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Reserva.h
 * @brief Gestora de biodiversidade e ciclo vital.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef RESERVA_H
#define RESERVA_H

#include <vector>
#include "SerVivo.h"

/**
 * @class Reserva
 * @brief Gestora da arquitetura do ecossistema.
 */
class Reserva {
private:
    std::vector<SerVivo*> biota;
    int ciclo;

public:
    Reserva();
    void adicionar(SerVivo* s);
    void evoluir();
    void dashboard() const;
    ~Reserva();
};

#endif // RESERVA_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
