/**
 * @file Frota.cpp
 * @brief Implementação modular da Herança para Veículos e Caminhões.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Frota.h"
#include <iostream>

namespace Logistica {

    // IMPLEMENTAÇÃO DA CLASSE BASE (VEICULO)
    Veiculo::Veiculo(std::string p, std::string m) : placa(p), marca(m), odometro(0.0) {}

    void Veiculo::viajar(double km) {
        if (km > 0) odometro += km;
    }

    std::string Veiculo::getInfo() const {
        return "PLACA: " + placa + " | MARCA: " + marca + " | ODO: " + std::to_string(odometro);
    }

    // IMPLEMENTAÇÃO DA CLASSE DERIVADA (CAMINHAO)
    /**
     * @brief O construtor do Filho DEVE chamar o construtor do Pai
     * usando a Lista de Inicialização.
     */
    Caminhao::Caminhao(std::string p, std::string m, double cap) 
        : Veiculo(p, m), capacidadeCarga(cap), cargaAtual(0.0) {}

    bool Caminhao::carregar(double toneladas) {
        if (cargaAtual + toneladas > capacidadeCarga) {
            return false; // Excesso de peso
        }
        cargaAtual += toneladas;
        return true;
    }

    std::string Caminhao::getRelatorioCaminhao() const {
        // Note como acessamos 'placa' e 'marca' diretamente porque são PROTECTED na base.
        std::string rel = ">>> RELATÓRIO DO CAMINHÃO <<<\n";
        rel += "IDENTIFICAÇÃO: " + placa + " (" + marca + ")\n";
        rel += "ODO: " + std::to_string(odometro) + " km\n";
        rel += "CARGA: " + std::to_string(cargaAtual) + " t / " + std::to_string(capacidadeCarga) + " t";
        return rel;
    }
}
