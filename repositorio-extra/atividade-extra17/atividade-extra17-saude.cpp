/**
 * @file atividade-extra17-saude.cpp
 * @brief Monitoramento de UTI: Introdução a Classes e Encapsulamento.
 * 
 * Versão Refatorada: Arquitetura Modular (Nível 11+).
 * Demonstra a transição de 'struct' para 'class' de forma profissional.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "MonitorSaude.h"

using namespace std;

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "     SISTEMA DE MONITORAMENTO DE UTI v1.0      " << endl;
    cout << "      (Arquitetura Modular Refatorada)         " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando um objeto (instância) da classe modular
    PacienteMonitorado p1("João da Silva");

    int entradaBPM, entradaOxy;
    double entradaTemp;

    // Simulação de entrada de dados do monitor real
    cout << "Digite o BPM atual do paciente: ";
    cin >> entradaBPM;
    if (!p1.setBPM(entradaBPM)) {
        cout << UI::AMARELO << "AVISO: Valor de BPM inválido ignorado para segurança." << UI::RESET << endl;
    }

    cout << "Digite a Temperatura atual (°C): ";
    cin >> entradaTemp;
    if (!p1.setTemperatura(entradaTemp)) {
        cout << UI::AMARELO << "AVISO: Valor de Temperatura inválido ignorado." << UI::RESET << endl;
    }

    cout << "Digite a Oxigenação (%): ";
    cin >> entradaOxy;
    if (!p1.setOxigenacao(entradaOxy)) {
        cout << UI::AMARELO << "AVISO: Valor de Oxigenação inválido ignorado." << UI::RESET << endl;
    }

    // Análise segura dos dados encapsulados no módulo
    p1.analisarEstado();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ENCAPSULAMENTO E ARQUITETURA MODULAR
    ===============================================================

    1. O PODER DO ENCAPSULAMENTO (Private/Public):
       - Ao mover a classe para um módulo separado, reforçamos o 
         conceito de "Caixa Preta". O programador da main não precisa 
         saber como a validação é feita; ele apenas confia na interface 
         pública do MonitorSaude.h.

    2. PROTEÇÃO DE DADOS CRÍTICOS:
       - Em sistemas médicos ou financeiros, o encapsulamento é 
         vital. Impedir o acesso direto a variáveis como 'oxigenacao' 
         evita que valores fatais sejam inseridos acidentalmente.

    3. MANUTENABILIDADE:
       - Se a regra de febre mudar (ex: de 37.5 para 37.8), alteramos 
         apenas o MonitorSaude.cpp, e todas as partes do sistema que 
         usam o monitor serão atualizadas instantaneamente.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Information Hiding: A base da engenharia de software robusta.
    - Princípio da Abstração: Esconder detalhes complexos.
    - Getters/Setters: Por que não usar apenas variáveis públicas?
    ===============================================================
*/
