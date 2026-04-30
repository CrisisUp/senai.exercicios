#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

/**
 * @class Sensor
 * @brief Componente especializado para telemetria de drones.
 */
class Sensor {
public:
    double obterTemperatura() {
        return 42.5; // Simulação de hardware
    }
    
    std::string lerCoordenadas() {
        return "40.7128 N, 74.0060 W";
    }
};

#endif
