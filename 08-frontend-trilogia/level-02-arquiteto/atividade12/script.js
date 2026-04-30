/**
 * @file script.js
 * @brief Manipulação de Objetos Complexos e Template Literals (Atividade 12).
 */

// 1. DADOS MULTIDIMENSIONAIS (Objetos de Elite)
const frotaNexus = [
    {
        id: "ALPHA-707",
        modelo: "Vulture v1",
        carga: 1500,
        autonomia: 25,
        ano: 2024
    },
    {
        id: "BETA-404",
        modelo: "Cargo Lifter",
        carga: 5000,
        autonomia: 12,
        ano: 2025
    },
    {
        id: "GAMMA-909",
        modelo: "Stealth Scout",
        carga: 200,
        autonomia: 45,
        ano: 2026
    }
];

/**
 * @brief Renderiza a frota detalhada no dashboard.
 */
function renderizarFrota() {
    const container = document.getElementById('fleet-container');
    
    // TEMPLATE LITERALS: Permite criar strings de múltiplas linhas e injetar variáveis via ${}
    let htmlFinal = "";

    frotaNexus.forEach(drone => {
        htmlFinal += `
            <article class="drone-card">
                <h2>${drone.id}</h2>
                <div class="data-row">
                    <span class="label">MODELO:</span>
                    <span class="value">${drone.modelo}</span>
                </div>
                <div class="data-row">
                    <span class="label">CARGA:</span>
                    <span class="value">${drone.carga}<span class="unit">kg</span></span>
                </div>
                <div class="data-row">
                    <span class="label">AUTONOMIA:</span>
                    <span class="value">${drone.autonomia}<span class="unit">km</span></span>
                </div>
                <div class="data-row">
                    <span class="label">FABRICAÇÃO:</span>
                    <span class="value">${drone.ano}</span>
                </div>
            </article>
        `;
    });

    container.innerHTML = htmlFinal;
    console.log(`[SYSTEM] Arquiteto: ${frotaNexus.length} unidades detalhadas renderizadas.`);
}

// Inicializa o sistema
renderizarFrota();
