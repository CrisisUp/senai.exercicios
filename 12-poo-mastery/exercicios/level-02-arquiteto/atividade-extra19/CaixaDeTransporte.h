/**
 * @file CaixaDeTransporte.h
 * @brief Definição da classe template CaixaDeTransporte.
 * @author Gemini CLI
 * @date 2026-04-22
 */

#ifndef CAIXA_DE_TRANSPORTE_H
#define CAIXA_DE_TRANSPORTE_H

#include <iostream>
#include <string>

/**
 * @brief Classe genérica para transporte de itens.
 * @tparam T O tipo de item a ser transportado.
 */
template <typename T>
class CaixaDeTransporte {
private:
    T* item;
    std::string etiqueta;

public:
    CaixaDeTransporte(std::string etq) : item(nullptr), etiqueta(etq) {}

    void guardar(T* novoItem) {
        item = novoItem;
        std::cout << "[Caixa: " << etiqueta << "] Item guardado com sucesso." << std::endl;
    }

    T* retirar() {
        std::cout << "[Caixa: " << etiqueta << "] Item retirado." << std::endl;
        T* temp = item;
        item = nullptr;
        return temp;
    }

    bool estaVazia() const {
        return item == nullptr;
    }
    
    void mostrarConteudo() const {
        if (estaVazia()) {
            std::cout << "[Caixa: " << etiqueta << "] Está vazia." << std::endl;
        } else {
            std::cout << "[Caixa: " << etiqueta << "] Contém um item de tipo genérico." << std::endl;
        }
    }
};

#endif // CAIXA_DE_TRANSPORTE_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
