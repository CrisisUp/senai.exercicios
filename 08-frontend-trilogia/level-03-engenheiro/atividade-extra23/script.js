/**
 * @date 2026
 */
/**
 * @file script.js
 * @brief Motor de Síntese de Áudio Digital (Web Audio API).
 * @author Engenheiro de Elite
 */

let audioCtx = null;
let masterGain = null;

/**
 * @brief Inicializa o contexto de áudio (Exige ação do usuário).
 */
function inicializarAudio() {
    if (audioCtx) return;

    // 1. Criação do Contexto Mestre
    audioCtx = new (window.AudioContext || window.webkitAudioContext)();
    
    // 2. Criação do GainNode (Controle de Volume Master)
    masterGain = audioCtx.createGain();
    masterGain.gain.value = 0.5; // 50% inicial
    masterGain.connect(audioCtx.destination);

    // Atualização da UI
    document.getElementById('audio-status-led').className = "led active";
    document.getElementById('engine-text').innerText = "ENGINE: ACTIVE";
    document.getElementById('btn-start').style.display = "none";
    
    console.log("%c[AUDIO] Motor de síntese ativado com sucesso.", "color: #2ea043; font-weight: bold;");
}

/**
 * @brief Gera um sinal sonoro puro (Bipe).
 */
function tocarBipe(freq, tipo = 'sine', duracao = 0.2) {
    if (!audioCtx) return;

    // 1. Criar o Oscilador (Gerador de Onda)
    const osc = audioCtx.createOscillator();
    const nodeGain = audioCtx.createGain();

    osc.type = tipo;
    osc.frequency.setValueAtTime(freq, audioCtx.currentTime);

    // 2. Envelope de Amplitude (Evita 'clicks' secos)
    nodeGain.gain.setValueAtTime(0, audioCtx.currentTime);
    nodeGain.gain.linearRampToValueAtTime(masterGain.gain.value, audioCtx.currentTime + 0.01);
    nodeGain.gain.exponentialRampToValueAtTime(0.001, audioCtx.currentTime + duracao);

    // 3. Roteamento: Osc -> Gain Local -> Master Gain -> Out
    osc.connect(nodeGain);
    nodeGain.connect(masterGain);

    // 4. Disparo
    osc.start();
    osc.stop(audioCtx.currentTime + duracao);
}

/**
 * @brief Orquestrador de Sinais Táticos.
 */
function tocarSinal(tipo) {
    if (!audioCtx) {
        alert("Erro: Inicialize o motor de áudio primeiro.");
        return;
    }

    switch (tipo) {
        case 'NORMAL':
            tocarBipe(880, 'sine', 0.1); // Bipe agudo curto
            break;
        case 'WARNING':
            tocarBipe(440, 'triangle', 0.5); // Aviso médio
            break;
        case 'CRITICAL':
            // Sirene: Variação de frequência
            const tempo = audioCtx.currentTime;
            for(let i = 0; i < 3; i++) {
                const start = tempo + (i * 0.6);
                tocarBipe(440, 'sawtooth', 0.3);
                setTimeout(() => tocarBipe(880, 'sawtooth', 0.3), (i * 600) + 300);
            }
            break;
    }
}

function ajustarVolume() {
    const vol = document.getElementById('volume-master').value;
    document.getElementById('volume-val').innerText = Math.round(vol * 100) + "%";
    
    if (masterGain) {
        masterGain.gain.setTargetAtTime(vol, audioCtx.currentTime, 0.05);
    }
}

console.log("[SYSTEM] Audio Subsystem Ready. Waiting for operator initialization.");

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
