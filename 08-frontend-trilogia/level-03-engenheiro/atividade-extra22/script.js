/**
 * @date 2026
 */
/**
 * @file script.js
 * @brief Motor de Animação de Alta Performance (requestAnimationFrame).
 * @author Engenheiro de Elite
 */

const canvas = document.getElementById('kinetic-canvas');
const ctx = canvas.getContext('2d');

const centerX = canvas.width / 2;
const centerY = canvas.height / 2;
const radius = canvas.width / 2 - 10;

let angle = 0;
let isActive = true;
let startTime = Date.now();

/**
 * @brief Desenha a estrutura fixa do radar (Fundo).
 */
function drawBackground() {
    ctx.strokeStyle = "rgba(0, 242, 255, 0.1)";
    ctx.lineWidth = 1;

    // Círculos de distância
    for (let i = 1; i <= 4; i++) {
        ctx.beginPath();
        ctx.arc(centerX, centerY, (radius / 4) * i, 0, Math.PI * 2);
        ctx.stroke();
    }

    // Eixos cardeais
    ctx.beginPath();
    ctx.moveTo(centerX, 10); ctx.lineTo(centerX, canvas.height - 10);
    ctx.moveTo(10, centerY); ctx.lineTo(canvas.width - 10, centerY);
    ctx.stroke();
}

/**
 * @brief Loop de Renderização de Elite (60 FPS).
 */
function loop() {
    if (!isActive) return;

    // 1. EFEITO DE RASTRO (GHOSTING): Limpa com transparência
    // Em vez de clearRect, desenhamos um retângulo preto quase transparente.
    // Isso faz com que os desenhos anteriores 'desbotem' devagar.
    ctx.fillStyle = "rgba(0, 0, 0, 0.05)";
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    drawBackground();

    // 2. CÁLCULO DA AGULHA (Trigonometria)
    const lineX = centerX + Math.cos(angle) * radius;
    const lineY = centerY + Math.sin(angle) * radius;

    // 3. DESENHO DA VARREDURA (Sweep)
    ctx.strokeStyle = "var(--color-accent)";
    ctx.lineWidth = 3;
    ctx.shadowBlur = 15;
    ctx.shadowColor = "#00f2ff";
    
    ctx.beginPath();
    ctx.moveTo(centerX, centerY);
    ctx.lineTo(lineX, lineY);
    ctx.stroke();
    
    ctx.shadowBlur = 0; // Limpa glow para não pesar no próximo frame

    // 4. EVOLUÇÃO DO ESTADO
    angle += 0.03; // Velocidade de rotação
    
    // Atualização de Uptime
    const uptime = Math.floor((Date.now() - startTime) / 1000);
    document.getElementById('uptime-val').innerText = uptime;

    // 5. SOLICITAÇÃO DO PRÓXIMO QUADRO (Sincronizado com o Monitor)
    requestAnimationFrame(loop);
}

/**
 * @brief Liga/Desliga o motor de renderização.
 */
function toggleEngine() {
    isActive = !isActive;
    const btn = document.getElementById('btn-toggle');
    const status = document.getElementById('engine-status');

    if (isActive) {
        btn.innerText = "SUSPENDER VARREDURA";
        status.innerText = "ONLINE";
        status.style.color = "#2ea043";
        loop(); // Reinicia o loop
    } else {
        btn.innerText = "REATIVAR VARREDURA";
        status.innerText = "PAUSED";
        status.style.color = "#f85149";
    }
}

function resetEngine() {
    angle = 0;
    startTime = Date.now();
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    console.log("[SYSTEM] Coordenadas de varredura resetadas.");
}

// Início do Boot Industrial
console.log("%c[ENGINE] Motor Cinético Iniciado.", "color: #00f2ff; font-weight: bold;");
loop();

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
