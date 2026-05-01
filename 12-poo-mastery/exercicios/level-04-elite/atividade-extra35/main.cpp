#include <iostream>
#include <string>
#include <vector>
#include <utility> // Para std::move

/**
 * @file main.cpp
 * @brief Implementação da Regra dos Cinco e Semântica de Movimento.
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Buffer Original (Heap): Memória alocada dinamicamente.
 * - Move (Pointers): Apenas o endereço do ponteiro é copiado da Stack de origem para a Stack de destino.
 * - Objeto Origem: É deixado em estado 'nullptr' para evitar double-free no destrutor.
 */

class BufferTelemetria {
private:
    std::string id;
    size_t tamanho;
    int* dados;

public:
    // 1. Construtor Padrão
    BufferTelemetria(std::string name, size_t size) : id(name), tamanho(size) {
        dados = new int[tamanho];
        std::cout << "[CONSTRUTOR] " << id << ": Alocados " << tamanho * sizeof(int) << " bytes." << std::endl;
    }

    // 2. Destrutor (Essencial para limpar a Heap)
    ~BufferTelemetria() {
        if (dados != nullptr) {
            std::cout << "\033[31m[DESTRUTOR] " << id << ": Liberando memória da Heap.\033[0m" << std::endl;
            delete[] dados;
        } else {
            std::cout << "[DESTRUTOR] " << id << ": Objeto vazio (memória já movida). Nada a liberar." << std::endl;
        }
    }

    // 3. Construtor de Cópia (Deep Copy - O que queremos evitar para objetos grandes)
    BufferTelemetria(const BufferTelemetria& outro) : id(outro.id + "_copia"), tamanho(outro.tamanho) {
        dados = new int[tamanho];
        for (size_t i = 0; i < tamanho; ++i) dados[i] = outro.dados[i];
        std::cout << "\033[33m[CÓPIA] Realizada cópia pesada de " << id << ".\033[0m" << std::endl;
    }

    // 4. Operador de Atribuição por Cópia
    BufferTelemetria& operator=(const BufferTelemetria& outro) {
        if (this == &outro) return *this;
        delete[] dados; // Limpa o antigo
        tamanho = outro.tamanho;
        id = outro.id + "_atribuicao";
        dados = new int[tamanho];
        for (size_t i = 0; i < tamanho; ++i) dados[i] = outro.dados[i];
        return *this;
    }

    // --- ELITE: SEMÂNTICA DE MOVIMENTO ---

    // 5. Construtor de Movimento (Move Constructor)
    // Recebe uma R-value reference (&&)
    BufferTelemetria(BufferTelemetria&& outro) noexcept 
        : id(std::move(outro.id)), tamanho(outro.tamanho), dados(outro.dados) {
        
        // O PULO DO GATO: "Anulamos" o objeto original para que o destrutor dele não apague os dados que "roubamos"
        outro.dados = nullptr;
        outro.tamanho = 0;
        
        std::cout << "\033[32m[MOVE] Sucesso! Dados de '" << id << "' transferidos via ponteiro.\033[0m" << std::endl;
    }

    // 6. Operador de Atribuição por Movimento (Move Assignment)
    BufferTelemetria& operator=(BufferTelemetria&& outro) noexcept {
        if (this == &outro) return *this;

        delete[] dados; // Limpa o recurso que tínhamos

        // Rouba os recursos do outro
        dados = outro.dados;
        tamanho = outro.tamanho;
        id = std::move(outro.id);

        // Deixa o outro em estado seguro
        outro.dados = nullptr;
        outro.tamanho = 0;

        std::cout << "\033[32m[MOVE ASSIGN] Dados transferidos e recurso antigo liberado.\033[0m" << std::endl;
        return *this;
    }

    void status() const {
        std::cout << " > Status [" << id << "]: " << (dados ? "Ativo" : "Vazio/Movido") << std::endl;
    }
};

// Função que gera um objeto pesado
BufferTelemetria criarPacoteDados() {
    BufferTelemetria temp("Pacote-RAW-4K", 1000);
    return temp; // O C++ Moderno usará Move aqui automaticamente (RVO)
}

int main() {
    std::cout << "--- SkyCargo Nexus: Otimização de Performance (Move Semantics) ---" << std::endl;

    // 1. Cenário de Cópia (Lento)
    std::cout << "\n[Cenário 1] Cópia Tradicional:" << std::endl;
    BufferTelemetria b1("Buffer-Alpha", 500);
    BufferTelemetria b2 = b1; // Chama Construtor de Cópia

    // 2. Cenário de Movimento (Rápido)
    std::cout << "\n[Cenário 2] Movimento Explícito (std::move):" << std::endl;
    BufferTelemetria b3("Buffer-Beta", 500);
    b3.status();
    
    BufferTelemetria b4 = std::move(b3); // "Beta" é movido para b4. b3 fica vazio.
    
    std::cout << "Após o movimento:" << std::endl;
    b3.status();
    b4.status();

    // 3. Retorno de Funções (Eficiência Máxima)
    std::cout << "\n[Cenário 3] Retorno de Função (Transferência Automática):" << std::endl;
    BufferTelemetria b5 = criarPacoteDados();
    b5.status();

    std::cout << "\n--- Finalizando Execução e Limpando Recursos ---" << std::endl;

    /*
     * RESUMO TEÓRICO:
     * A Semântica de Movimento permite que recursos (memória, file handles, etc) 
     * sejam transferidos entre objetos em vez de duplicados.
     * 
     * Diferença Técnica:
     * - Cópia: New Buffer -> Copy Data -> 2 Buffers idênticos.
     * - Movimento: Copy Pointer -> Null Original Pointer -> 1 Buffer transferido.
     * 
     * Regra dos Cinco: Se você precisa de um Destrutor, provavelmente precisa de 
     * Cópia (Constructor/Assignment) e Movimento (Constructor/Assignment).
     */

    return 0;
}
