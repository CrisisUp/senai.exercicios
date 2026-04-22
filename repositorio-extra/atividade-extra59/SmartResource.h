/**
 * @file SmartResource.h
 * @brief Definição modular de Recursos Críticos usando Ponteiros Inteligentes.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef SMART_RESOURCE_H
#define SMART_RESOURCE_H

#include <string>
#include <iostream>

namespace Logistica {

    /**
     * @brief Classe que simula um recurso de hardware crítico.
     */
    class ModuloGPS {
    private:
        std::string id;
        double latitude;
        double longitude;

    public:
        ModuloGPS(std::string _id);
        ~ModuloGPS(); // Logs no destrutor para ver o Smart Pointer em ação.

        void atualizarCoordenadas(double lat, double lon);
        void mostrarStatus() const;
        
        std::string getId() const { return id; }
    };
}

#endif // SMART_RESOURCE_H
