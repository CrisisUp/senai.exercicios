/**
 * @file motor_rota.h
 * @brief Header do motor de rotas em C++.
 * @author Engenheiro de Elite
 */

#pragma once
#include <string>
#include <memory>
#include "rust/cxx.h"

namespace logispeed {

/**
 * @class MotorRota
 * @brief Simula um algoritmo complexo de otimização.
 */
class MotorRota {
public:
    MotorRota(rust::String nome_config);
    rust::String calcular_melhor_rota(rust::String origem, rust::String destino) const;
    double obter_distancia() const;

private:
    std::string config;
};

// Função factory para o Rust criar o objeto
std::unique_ptr<MotorRota> novo_motor(rust::String config);

} // namespace logispeed
