/**
 * @file script.js
 * @brief Gerenciamento de Variáveis e Manipulação (Atividade 02).
 */

// 1. Definição de Variáveis (A memória do sistema)
const SISTEMA_VERSAO = "2.1.0-ELITE"; // Não muda nunca
let operadorAtual = "Cristiano";     // Pode mudar se outro logar

// 2. Manipulação de DOM básica (Saída na página)
// Buscamos o elemento por ID e inserimos o valor da variável
const opSpan = document.getElementById('op-name');
if (opSpan) {
    opSpan.innerText = operadorAtual;
    opSpan.style.fontWeight = "bold";
}

// 3. Feedback Industrial
console.log(`[STATUS] Versão do Sistema: ${SISTEMA_VERSAO}`);
console.log(`[STATUS] Operador Ativo: ${operadorAtual}`);
