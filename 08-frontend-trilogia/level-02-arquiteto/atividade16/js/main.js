/**
 * @file main.js
 * @brief Orquestrador Master da Arquitetura Modular.
 */

// 1. IMPORTAÇÃO DE MÓDULOS DE ELITE
import { fetchDroneFleet } from './modules/api.js';
import { renderFleet, showErrorMessage } from './modules/ui.js';

console.log("\x1b[1;36m[SYSTEM]\x1b[0m Nexus Orchestrator Inicializado.");

/**
 * @brief Sequência de Boot do Sistema.
 */
async function boot() {
    try {
        const data = await fetchDroneFleet();
        renderFleet(data);
    } catch (err) {
        showErrorMessage("FALHA CRÍTICA NO LINK DE SATÉLITE.");
        console.error("[BOOT ERROR] " + err.message);
    }
}

// Inicia o processo
boot();
