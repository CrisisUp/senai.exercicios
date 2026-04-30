/**
 * @file script.js
 * @brief Lógica Matemática de Missão (Atividade 03).
 */

// 1. Entrada de Dados
const bateriaPorcentagem = 80;
const FATOR_CONVERSAO = 1.5; // 1% de bateria = 1.5km de autonomia

// 2. Processamento (Matemática Industrial)
const autonomiaKm = bateriaPorcentagem * FATOR_CONVERSAO;

// 3. Saída de Dados (Interação com o DOM)
const displayBateria = document.getElementById('bat-level');
const displayAutonomia = document.getElementById('autonomia-res');

if (displayBateria) {
    displayBateria.innerText = bateriaPorcentagem;
}

if (displayAutonomia) {
    // Concatenando número com string para exibição profissional
    displayAutonomia.innerText = autonomiaKm + " km";
}

// Registro técnico no console
console.log(`[MATH] Bateria: ${bateriaPorcentagem}% | Fator: ${FATOR_CONVERSAO} | Resultado: ${autonomiaKm}km`);
