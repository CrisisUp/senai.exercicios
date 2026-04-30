/**
 * @file ui.js
 * @brief Módulo de Renderização de Interface.
 */

const dashboard = document.getElementById('dashboard-view');

/**
 * @brief Renderiza os cartões de drone na tela.
 * @param {Array} drones Lista de objetos drone.
 */
export function renderFleet(drones) {
    console.log("\x1b[1;32m[MODULE:UI]\x1b[0m Atualizando visor tático...");
    dashboard.innerHTML = ""; // Limpa atual

    drones.forEach(drone => {
        const card = document.createElement('div');
        card.className = "drone-card";
        card.innerHTML = `
            <h3>${drone.username}</h3>
            <p><strong>FREQ:</strong> ${drone.address.city}</p>
            <div class="status-indicator">ON</div>
        `;
        dashboard.appendChild(card);
    });
}

/**
 * @brief Exibe mensagem de erro na interface.
 */
export function showErrorMessage(msg) {
    dashboard.innerHTML = `<p class="error">${msg}</p>`;
}
