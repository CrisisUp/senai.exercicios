/**
 * @file script.js
 * @brief Orquestração de Fluxos de Vídeo e Filtros (Media API).
 * @author Engenheiro de Elite
 */

const video = document.getElementById('fpv-stream');
const statusLabel = document.getElementById('stream-status');

/**
 * @brief Inicializa o link de vídeo com o hardware.
 */
async function inicializarStream() {
    console.log("[MEDIA] Solicitando acesso aos sensores ópticos...");
    
    try {
        // 1. SOLICITAÇÃO DE HARDWARE (Somente vídeo para esta missão)
        const stream = await navigator.mediaDevices.getUserMedia({ 
            video: { width: 1280, height: 720 },
            audio: false 
        });

        // 2. ASSOCIAÇÃO AO VISOR
        video.srcObject = stream;
        
        statusLabel.innerText = "ONLINE";
        statusLabel.style.color = "#2ea043";
        console.log("%c[SUCCESS] Link Óptico Estabelecido.", "color: #2ea043; font-weight: bold;");

    } catch (err) {
        console.error("[CRITICAL] Falha no link de vídeo: " + err.name);
        statusLabel.innerText = "ACCESS DENIED";
        statusLabel.style.color = "#f85149";
        alert("ERRO DE HARDWARE: Verifique as permissões da câmera.");
    }
}

/**
 * @brief Altera dinamicamente o modo de visão via filtros CSS.
 */
function mudarVisao(modo) {
    // Remove classes anteriores
    video.className = "";

    if (modo !== 'normal') {
        video.classList.add(`vision-${modo}`);
    }

    console.log(`[OPTICS] Alterado para: ${modo.toUpperCase()}`);
}

/**
 * @brief Captura um frame fixo do vídeo (Evidência).
 */
function capturarFrame() {
    const canvas = document.getElementById('snapshot-canvas');
    const ctx = canvas.getContext('2d');
    const container = document.getElementById('snaps-container');

    // 1. DESENHA O VÍDEO NO CANVAS (Oculto)
    ctx.drawImage(video, 0, 0, canvas.width, canvas.height);

    // 2. CONVERTE PARA IMAGEM E INJETA NA GALERIA
    const imgData = canvas.toDataURL('image/png');
    const newImg = document.createElement('img');
    newImg.src = imgData;
    newImg.alt = "Captura de Evidência";

    // Adiciona ao início da galeria
    container.prepend(newImg);
    console.log("[SNAPSHOT] Evidência registrada no cofre.");
}

// Inicia o boot do sistema de visão
inicializarStream();
