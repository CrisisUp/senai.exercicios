/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Delegação de Eventos e Data Attributes (Atividade 13).
 */

const baseDrones = [
    { id: "ALPHA-707", status: "OPERACIONAL" },
    { id: "BETA-404", status: "ALERTA" },
    { id: "GAMMA-909", status: "OPERACIONAL" },
    { id: "SIGMA-001", status: "ALERTA" },
    { id: "ZETA-888", status: "OPERACIONAL" }
];

const container = document.getElementById('fleet-delegate');

/**
 * @brief Renderiza a frota com Data Attributes.
 */
function renderizar(lista) {
    container.innerHTML = "";
    lista.forEach(drone => {
        const div = document.createElement('div');
        div.className = "drone-unit";
        
        // 1. DATA ATTRIBUTES: Guardando o dado no HTML
        div.setAttribute('data-id', drone.id);
        div.setAttribute('data-status', drone.status);
        
        div.innerHTML = `<strong>${drone.id}</strong><br><small>${drone.status}</small>`;
        container.appendChild(div);
    });
}

// 2. DELEGAÇÃO DE EVENTOS: Um único listener no PAI
container.addEventListener('click', (event) => {
    // Buscamos o ancestral mais próximo que seja um .drone-unit
    const card = event.target.closest('.drone-unit');
    
    if (card) {
        // 3. DATASET: Lendo o dado do HTML via JS
        const id = card.dataset.id;
        const status = card.dataset.status;

        const display = document.getElementById('status-display');
        display.innerText = `CONEXÃO ESTABELECIDA COM: ${id} [${status}]`;
        console.log(`[DELEGATION] Clique detectado no drone: ${id}`);
    }
});

/**
 * @brief Filtra a frota conforme o input.
 */
function executarBusca() {
    const termo = document.getElementById('input-busca').value.toUpperCase();
    const filtrados = baseDrones.filter(d => d.id.includes(termo));
    renderizar(filtrados);
}

// Boot
renderizar(baseDrones);

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
