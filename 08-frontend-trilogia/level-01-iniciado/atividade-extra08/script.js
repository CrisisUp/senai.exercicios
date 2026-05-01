/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Automação e Monitoramento em Tempo Real (Atividade 08).
 */

// 1. Estado da Frota (Memória Reativa)
let frota = [
    { id: "ALPHA-707", bateria: 100 },
    { id: "BETA-404", bateria: 100 }
];

/**
 * @brief Atualiza a visualização dos drones no DOM.
 */
function atualizarDashboard() {
    frota.forEach(drone => {
        // Busca o card específico pelo ID
        const cardId = drone.id === "ALPHA-707" ? "drone-707" : "drone-404";
        const cardElement = document.getElementById(cardId);

        if (cardElement) {
            // Atualiza o texto da bateria
            const batSpan = cardElement.querySelector('.bat-val');
            batSpan.innerText = drone.bateria;

            // Atualiza a barra de progresso visualmente
            const fill = cardElement.querySelector('.progress-fill');
            fill.style.width = drone.bateria + "%";

            // Lógica de alerta visual (Fase anterior)
            if (drone.bateria < 20) {
                fill.style.backgroundColor = "#f85149";
                cardElement.style.borderColor = "#f85149";
            }
        }
    });
}

/**
 * @brief Simula o consumo de energia (Motor do Sistema).
 */
function processarConsumo() {
    frota = frota.map(drone => {
        // Reduz bateria em 1% (mínimo 0)
        let novaBateria = drone.bateria - 1;
        return { ...drone, bateria: novaBateria < 0 ? 0 : novaBateria };
    });

    atualizarDashboard();
}

// 2. INICIALIZAÇÃO DA AUTOMAÇÃO (O Pulso do Sistema)
// Executa a função 'processarConsumo' a cada 3000ms (3 segundos)
const monitorId = setInterval(processarConsumo, 3000);

console.log("[SYSTEM] Monitoramento de telemetria automática INICIADO.");
console.log("[DEBUG] Interval ID: " + monitorId);

// Mock de parada (para evitar loops infinitos em testes)
// setTimeout(() => clearInterval(monitorId), 60000); // Para após 1 minuto

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
