/**
 * @date 2026
 */
/**
 * @file script.js
 * @brief Motor de Renderização de Radar (HTML5 Canvas 2D).
 * @author Engenheiro de Elite
 */

const canvas = document.getElementById('radar-canvas');
const ctx = canvas.getContext('2d'); // A mira do desenhista

const centerX = canvas.width / 2;
const centerY = canvas.height / 2;

/**
 * @brief Desenha a grade tática do radar.
 */
function desenharGrade() {
    console.log("[RADAR] Gerando grade de varredura...");
    
    ctx.strokeStyle = "rgba(46, 160, 67, 0.4)";
    ctx.lineWidth = 1;

    // 1. Desenha círculos concêntricos
    for (let r = 50; r <= 200; r += 50) {
        ctx.beginPath();
        ctx.arc(centerX, centerY, r, 0, Math.PI * 2);
        ctx.stroke();
    }

    // 2. Desenha eixos táticos
    ctx.beginPath();
    ctx.moveTo(centerX, 0); ctx.lineTo(centerX, canvas.height); // Eixo Y
    ctx.moveTo(0, centerY); ctx.lineTo(canvas.width, centerY);   // Eixo X
    ctx.stroke();
}

/**
 * @brief Adiciona uma unidade de drone detectada no mapa.
 */
function adicionarDrone() {
    // Coordenadas aleatórias dentro do radar
    const angle = Math.random() * Math.PI * 2;
    const dist = Math.random() * 180;
    
    const x = centerX + Math.cos(angle) * dist;
    const y = centerY + Math.sin(angle) * dist;

    // Desenha o Ponto (Blip) do Drone
    ctx.fillStyle = "#ffffff";
    ctx.shadowBlur = 10;
    ctx.shadowColor = "#00f2ff";
    
    ctx.beginPath();
    ctx.arc(x, y, 4, 0, Math.PI * 2);
    ctx.fill();

    console.log(`[RADAR] Unidade detectada em: X=${x.toFixed(0)}, Y=${y.toFixed(0)}`);
}

/**
 * @brief Limpa toda a tela do canvas.
 */
function limparRadar() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    console.log("[SYSTEM] Monitor reinicializado.");
}

// Inicializa a grade ao carregar
desenharGrade();

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
