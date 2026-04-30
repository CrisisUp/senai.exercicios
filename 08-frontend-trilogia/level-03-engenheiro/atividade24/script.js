/**
 * @file script.js
 * @brief Orquestrador da Thread Principal e Gestor do Worker (Atividade 24).
 */

// --- 1. MOTOR DE UI: RADAR (Thread Principal) ---
const canvas = document.getElementById('ui-radar');
const ctx = canvas.getContext('2d');
let angle = 0;

function animarRadar() {
    // Limpa com rastro (Atividade 22)
    ctx.fillStyle = "rgba(0, 0, 0, 0.05)";
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Linha de Varredura
    const x = 150 + Math.cos(angle) * 140;
    const y = 150 + Math.sin(angle) * 140;

    ctx.strokeStyle = "#00f2ff";
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(150, 150);
    ctx.lineTo(x, y);
    ctx.stroke();

    angle += 0.05;
    requestAnimationFrame(animarRadar);
}

// --- 2. MOTOR DE DADOS: WEB WORKER (Thread de Fundo) ---
let nexusWorker = null;

function iniciarCalculo() {
    const statusTxt = document.getElementById('worker-status');
    const progressBar = document.getElementById('worker-progress');
    const progVal = document.getElementById('progress-val');
    const logArea = document.getElementById('result-log');
    const btn = document.getElementById('btn-start');

    // Inicializa o Worker (Note o caminho a partir do index.html)
    if (!nexusWorker) {
        nexusWorker = new Worker('js/worker.js');
        
        // Escuta os resultados do Worker
        nexusWorker.onmessage = function(e) {
            const msg = e.data;

            if (msg.type === 'PROGRESS') {
                progressBar.value = msg.value;
                progVal.innerText = Math.round(msg.value);
            }

            if (msg.type === 'COMPLETE') {
                statusTxt.innerText = "FINISHED";
                statusTxt.style.color = "#2ea043";
                logArea.innerHTML += `<br>> [SUCCESS] ${msg.result}`;
                btn.disabled = false;
                console.log("%c[SYSTEM] Cálculo paralelo concluído.", "color: #2ea043; font-weight: bold;");
            }
        };
    }

    // Dispara a missão
    btn.disabled = true;
    statusTxt.innerText = "PROCESSING...";
    statusTxt.style.color = "#d29922";
    logArea.innerHTML = "> [INFO] Operação em Background iniciada.";
    
    nexusWorker.postMessage('START_CALCULATION');
}

// Boot da Interface
animarRadar();
console.log("[SYSTEM] UI Thread estável. Web Worker pronto.");
