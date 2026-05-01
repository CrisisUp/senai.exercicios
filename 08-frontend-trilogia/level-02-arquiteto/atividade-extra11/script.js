/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Manipulação de Seletores de Grupo e Arrow Functions (Atividade 11).
 */

// 1. CAPTURA DE GRUPO (querySelectorAll retorna uma lista de todos os .module)
const modulos = document.querySelectorAll('.module');

/**
 * @brief Gerencia a seleção visual de um módulo.
 * @param event O objeto de evento do clique.
 */
const selecionarModulo = (event) => {
    // 'currentTarget' garante que pegamos o elemento .module, mesmo clicando no H3 ou Span interno
    const alvo = event.currentTarget;

    // Remove a seleção de todos os outros (limpeza industrial)
    modulos.forEach(m => m.classList.remove('module-selected'));

    // Adiciona a seleção ao atual
    alvo.classList.add('module-selected');

    const titulo = alvo.querySelector('h3').innerText;
    console.log(`[UI] Módulo Selecionado: ${titulo}`);
};

// 2. BINDING DE EVENTOS EM MASSA
// Usamos .forEach para aplicar o ouvinte em cada peça do dashboard
modulos.forEach(modulo => {
    modulo.addEventListener('click', selecionarModulo);
});

console.log(`[SYSTEM] Arquiteto de UI: ${modulos.length} módulos detectados e vinculados.`);

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
