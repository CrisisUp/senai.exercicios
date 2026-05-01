/**
 * @file Logger.h
 * @author Cristiano
 * @date 2026
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

/**
 * @class Logger
 * @brief Responsável exclusivo pela saída de dados e interface (SRP: Visualização).
 */
class Logger {
public:
    static void logInfo(std::string msg);
    static void logSucesso(std::string msg);
    static void logAlerta(std::string msg);
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
