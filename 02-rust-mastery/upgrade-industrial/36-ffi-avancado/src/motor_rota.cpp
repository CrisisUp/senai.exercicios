/**
 * @file motor_rota.cpp
 * @brief Implementação do motor de rotas C++.
 * @author Engenheiro de Elite
 */

#include "ffi-avancado/include/motor_rota.h"
#include <iostream>

namespace logispeed {

MotorRota::MotorRota(rust::String nome_config) 
    : config(std::string(nome_config)) {
    std::cout << "\x1b[1;32m[C++ MOTOR]\x1b[0m Instanciado com config: " << config << std::endl;
}

rust::String MotorRota::calcular_melhor_rota(rust::String origem, rust::String destino) const {
    std::string s_origem(origem);
    std::string s_destino(destino);
    
    // Simula processamento pesado
    std::string resultado = "ROTA-OTIMIZADA: " + s_origem + " -> [Ponto Central] -> " + s_destino;
    
    return rust::String(resultado);
}

double MotorRota::obter_distancia() const {
    return 42.5; // Exemplo de valor calculado
}

std::unique_ptr<MotorRota> novo_motor(rust::String config) {
    return std::make_unique<MotorRota>(config);
}

} // namespace logispeed
