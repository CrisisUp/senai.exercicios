/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file nexus_core.h
 * @brief Definição do Motor de Telemetria de Elite (C++ Core) - REVISADO.
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include <atomic>
#include "rust/cxx.h"

namespace logispeed {

// Removemos a definição manual de RawTelemetria aqui, 
// pois ela será gerada pelo cxxbridge a partir do Rust.
struct RawTelemetria; 

class TelemetriaPool {
public:
    TelemetriaPool(size_t tamanho);
    RawTelemetria* adquirir();
    void liberar(RawTelemetria* t);

private:
    std::vector<std::unique_ptr<RawTelemetria>> storage;
    std::vector<RawTelemetria*> livres;
};

class NexusCore {
public:
    NexusCore();
    void processar_pacote_assincrono(int id_satelite) const;
    long long obter_total_processado() const;
    
    // Este método usa a struct gerada pelo Rust
    RawTelemetria capturar_dados_hardware() const;

private:
    mutable std::atomic<long long> total_pacotes{0};
    std::unique_ptr<TelemetriaPool> pool;
};

std::unique_ptr<NexusCore> criar_nexus();

} // namespace logispeed

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
