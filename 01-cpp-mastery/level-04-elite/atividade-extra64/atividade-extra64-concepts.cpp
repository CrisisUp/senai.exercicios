/**
 * @file atividade-extra64-concepts.cpp
 * @brief Implementação de C++20 Concepts para validação de Templates.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#include <iostream>
#include <concepts>
#include <string>
#include <vector>

/**
 * @concept Telemetrica
 * @brief Define os requisitos mínimos para um objeto de telemetria.
 * Exige: Atributo 'id' (convertível para int) e método 'serializar()' que retorna string.
 */
template <typename T>
concept Telemetrica = requires(T t) {
    { t.id } -> std::convertible_to<int>;
    { t.serializar() } -> std::same_as<std::string>;
};

// --- CLASSES QUE CUMPREM O CONTRATO ---

struct SensorGPS {
    int id;
    double lat, lon;
    std::string serializar() { return "GPS[" + std::to_string(id) + "]: " + std::to_string(lat); }
};

struct SensorMotor {
    int id;
    int rpm;
    std::string serializar() { return "MOTOR[" + std::to_string(id) + "]: " + std::to_string(rpm) + " RPM"; }
};

// --- CLASSE QUE VIOLA O CONTRATO (Não tem serializar) ---

struct SensorInvalido {
    int id;
    // Falta o método serializar()
};

/**
 * @brief Processador de Telemetria Genérico RESTRICTED por Concepts.
 */
template <Telemetrica T>
void processarSensor(T sensor) {
    std::cout << "\033[1;32m[VALIDADO]\033[0m Processando: " << sensor.serializar() << std::endl;
}

int main() {
    std::cout << "\033[1;36m=== LOGISPEED 4.0: VALIDAÇÃO VIA CONCEPTS (C++20) ===\033[0m\n" << std::endl;

    SensorGPS gps{101, -23.55, -46.63};
    SensorMotor motor{202, 3500};
    SensorInvalido bug{999};

    // Funciona perfeitamente: cumprem o concept 'Telemetrica'
    processarSensor(gps);
    processarSensor(motor);

    /**
     * @note DESCOMENTE A LINHA ABAIXO PARA VER O ERRO DE ELITE NO COMPILADOR:
     * O compilador dirá exatamente que 'SensorInvalido' não satisfaz 'Telemetrica'
     * porque não possui o método 'serializar'.
     */
    // processarSensor(bug); 

    std::cout << "\n\033[1;33m[ANÁLISE DE ELITE]\033[0m\n";
    std::cout << "A segurança agora é 'estática'. Se o objeto não serve, o sistema nem chega a existir." << std::endl;

    return 0;
}

/**
 * @section ResumoTeorico
 * 1. CONCEPTS: São predicados avaliados em tempo de compilação.
 * 2. REQUIRES: Define o corpo do teste de interface.
 * 3. TRAILING RETURN TYPE CHECK: '{ t.id } -> std::convertible_to<int>' verifica 
 *    não apenas a existência, mas se o tipo de retorno é compatível.
 */

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
