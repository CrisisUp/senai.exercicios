#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file SmartResource.h
 * @brief Interface para Módulos de Hardware geridos por Smart Pointers.
 * 
 * Atividade Extra 59 - Ponteiros Inteligentes (Nível 31+).
 * Demonstra a automação de RAII e posse compartilhada.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Smart Pointer Layout)
 * - unique_ptr: Ponteiro simples de 8 bytes na STACK. Objeto na HEAP.
 * - shared_ptr: Dois ponteiros na STACK (um para o objeto e outro para o 
 *   CONTROL BLOCK na HEAP).
 * - Control Block: Bloco extra na HEAP contendo o contador de referências.
 */

#ifndef SMARTRESOURCE_H
#define SMARTRESOURCE_H

#include <string>

namespace Logistica {

    /**
     * @class ModuloGPS
     * @brief Recurso de hardware simulado com logs de ciclo de vida.
     */
    class ModuloGPS {
    private:
        std::string idCaminhao;
        double latitude;
        double longitude;

    public:
        /** @brief Construtor com Log de Alocação. */
        ModuloGPS(const std::string& _id);

        /** @brief DESTRUTOR: Prova visual de que a memória foi limpa automaticamente. */
        ~ModuloGPS();

        void atualizarCoordenadas(double lat, double lon);
        void mostrarStatus() const;

        const std::string& getId() const { return idCaminhao; }
    };

} // namespace Logistica

#endif // SMARTRESOURCE_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */
