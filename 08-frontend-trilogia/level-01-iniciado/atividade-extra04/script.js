/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Lógica Reativa e Funções (Atividade 04).
 */

// 1. Estado Global do Componente
let bateria = 50;
const FATOR_AUTONOMIA = 1.5;

/**
 * @brief Atualiza os elementos visuais na tela.
 * Centraliza a manipulação do DOM em um único local.
 */
function atualizarInterface() {
    const spanBat = document.getElementById('bat-display');
    const spanAut = document.getElementById('autonomia-display');

    if (spanBat) spanBat.innerText = bateria;
    if (spanAut) spanAut.innerText = (bateria * FATOR_AUTONOMIA).toFixed(1) + " km";

    console.log(`[UI] Interface atualizada. Bateria: ${bateria}%`);
}

/**
 * @brief Handler de comando para alterar a energia.
 * @param valor Quantidade a ser somada ou subtraída.
 */
function alterarEnergia(valor) {
    // Lógica de Limites (Clamping)
    bateria = bateria + valor;

    if (bateria > 100) bateria = 100;
    if (bateria < 0) bateria = 0;

    atualizarInterface();
}

// Inicializa a tela no boot
console.log("[SYSTEM] Painel interativo inicializado.");
atualizarInterface();

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
