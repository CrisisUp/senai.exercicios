#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include "Sensor.h"

// Cores ANSI
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

/**
 * @class BateriaInvalidaException
 * @brief Exceção customizada para erros de energia (Atividade 17).
 */
class BateriaInvalidaException : public std::exception {
private:
    std::string mensagem;
public:
    BateriaInvalidaException(int valor) {
        mensagem = "ERRO CRÍTICO: Tentativa de configurar bateria em " + std::to_string(valor) + "%. Fora dos limites (0-100).";
    }
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

class Drone {
private:
    std::string modelo;
    int bateria;
    int idSeguranca;
    
    // Componente com Posse Exclusiva (Smart Pointer - Ativ 15)
    std::unique_ptr<Sensor> gps;

    static int totalDrones;

public:
    // Construtor Moderno
    Drone(std::string modelo, int bateria);
    
    // Construtor de Cópia de Elite (Deep Copy - Ativ 12)
    Drone(const Drone& outro);

    // Destrutor (Agora o unique_ptr limpa o Sensor sozinho!)
    ~Drone();

    // Setters com Exceções (Ativ 17)
    void setBateria(int b);
    
    // Métodos Const-Correctness (Ativ 11)
    int getBateria() const;
    std::string getModelo() const;
    void verStatus() const;

    // Comportamentos
    void decolar();
    void decolar(int altitude);

    static int getTotalDrones();

    friend class AuditoriaNexus;
};

#endif
