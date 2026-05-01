/**
 * @file script.js
 * @brief Sistema de Telemetria Acústica via Web Audio API.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

document.addEventListener('DOMContentLoaded', () => {
    // UI Elements
    const btnMaster = document.getElementById('btn-master-audio');
    const btnAlarm = document.getElementById('btn-alarm');
    const altitudeSlider = document.getElementById('altitude-slider');
    const altitudeVal = document.getElementById('altitude-val');
    const audioStatusEl = document.getElementById('audio-status');
    const alarmIndicator = document.getElementById('alarm-indicator');
    const terminalLog = document.getElementById('terminal-log');
    const canvas = document.getElementById('oscillos-canvas');
    const ctxCanvas = canvas.getContext('2d');

    // Audio State
    let audioCtx = null;
    let mainGain = null;
    let telemetryOsc = null;
    let telemetryGain = null;
    let alarmOsc = null;
    let alarmGain = null;
    let analyzer = null;

    /**
     * @section Inicialização do Motor de Áudio
     * Requisito de Elite: Acordar o contexto após interação do usuário.
     */
    function initAudio() {
        if (audioCtx) return;

        audioCtx = new (window.AudioContext || window.webkitAudioContext)();
        
        // Nó Principal de Ganho (Master Volume)
        mainGain = audioCtx.createGain();
        mainGain.gain.value = 0.5;

        // Analisador para o Osciloscópio
        analyzer = audioCtx.createAnalyser();
        analyzer.fftSize = 2048;

        // Roteamento: Source -> Analyzer -> Master -> Destination
        mainGain.connect(analyzer);
        analyzer.connect(audioCtx.destination);

        setupTelemetry();
        startVisualizer();

        audioStatusEl.textContent = "AUDIO ENGINE: OPERATIONAL";
        audioStatusEl.className = "status-on";
        btnMaster.disabled = true;
        logToTerminal("Motor de Áudio inicializado com sucesso.");
    }

    /**
     * @section Telemetria Acústica (Bipe Dinâmico)
     */
    function setupTelemetry() {
        telemetryOsc = audioCtx.createOscillator();
        telemetryGain = audioCtx.createGain();

        telemetryOsc.type = 'sine';
        telemetryOsc.frequency.value = 440; // Base: Lá 4
        telemetryGain.gain.value = 0; // Inicia mudo

        telemetryOsc.connect(telemetryGain);
        telemetryGain.connect(mainGain);
        telemetryOsc.start();

        // Loop de Bipe
        setInterval(() => {
            if (!audioCtx || audioCtx.state === 'suspended') return;
            
            const now = audioCtx.currentTime;
            // Envelope Suave para evitar "Audio Popping" (Requisito 2)
            telemetryGain.gain.setTargetAtTime(0.1, now, 0.01);
            telemetryGain.gain.setTargetAtTime(0, now + 0.1, 0.01);
        }, 1000);
    }

    /**
     * @section Alarme Crítico (Onda Quadrada)
     */
    let alarmActive = false;
    function toggleAlarm() {
        if (!audioCtx) return;

        if (!alarmActive) {
            alarmOsc = audioCtx.createOscillator();
            alarmGain = audioCtx.createGain();
            
            alarmOsc.type = 'square';
            alarmOsc.frequency.value = 880;
            alarmGain.gain.value = 0;

            alarmOsc.connect(alarmGain);
            alarmGain.connect(mainGain);
            alarmOsc.start();

            // Sirene Pulsante via Automação (Requisito 4)
            const now = audioCtx.currentTime;
            alarmGain.gain.setValueAtTime(0, now);
            
            // Loop de automação manual para a sirene
            alarmInterval = setInterval(() => {
                const t = audioCtx.currentTime;
                alarmOsc.frequency.exponentialRampToValueAtTime(880, t + 0.2);
                alarmOsc.frequency.exponentialRampToValueAtTime(440, t + 0.5);
                alarmGain.gain.linearRampToValueAtTime(0.3, t + 0.1);
                alarmGain.gain.linearRampToValueAtTime(0, t + 0.5);
            }, 600);

            alarmIndicator.textContent = "CRITICAL ALARM ACTIVE";
            alarmIndicator.classList.add('alarm-active');
            logToTerminal("ALERTA CRÍTICO ATIVADO PELO OPERADOR.");
        } else {
            if (alarmOsc) {
                alarmOsc.stop();
                alarmOsc.disconnect();
                clearInterval(alarmInterval);
            }
            alarmIndicator.textContent = "ALARM IDLE";
            alarmIndicator.classList.remove('alarm-active');
            logToTerminal("Alerta crítico silenciado.");
        }
        alarmActive = !alarmActive;
    }

    /**
     * @section Visualização (Osciloscópio)
     */
    function startVisualizer() {
        const bufferLength = analyzer.frequencyBinCount;
        const dataArray = new Uint8Array(bufferLength);

        function draw() {
            requestAnimationFrame(draw);
            analyzer.getByteTimeDomainData(dataArray);

            ctxCanvas.fillStyle = '#000';
            ctxCanvas.fillRect(0, 0, canvas.width, canvas.height);

            ctxCanvas.lineWidth = 2;
            ctxCanvas.strokeStyle = '#00ffff';
            ctxCanvas.beginPath();

            const sliceWidth = canvas.width * 1.0 / bufferLength;
            let x = 0;

            for (let i = 0; i < bufferLength; i++) {
                const v = dataArray[i] / 128.0;
                const y = v * canvas.height / 2;

                if (i === 0) ctxCanvas.moveTo(x, y);
                else ctxCanvas.lineTo(x, y);
                x += sliceWidth;
            }

            ctxCanvas.lineTo(canvas.width, canvas.height / 2);
            ctxCanvas.stroke();
        }
        draw();
    }

    // Interações
    altitudeSlider.addEventListener('input', (e) => {
        const val = e.target.value;
        altitudeVal.textContent = val;
        
        if (telemetryOsc) {
            // Frequência base + (altitude / 5)
            const newFreq = 220 + (val / 5);
            telemetryOsc.frequency.setTargetAtTime(newFreq, audioCtx.currentTime, 0.1);
        }
    });

    btnMaster.addEventListener('click', initAudio);
    btnAlarm.addEventListener('click', toggleAlarm);

    function logToTerminal(msg) {
        terminalLog.textContent = msg;
    }
});

/*
===============================================================================
RESUMO TEÓRICO: WEB AUDIO API (NÍVEL 35 - ELITE)
===============================================================================

1. AUDIO CONTEXT:
   É o ecossistema principal. Tudo começa aqui. Ele gerencia o tempo (currentTime) 
   com precisão de nanossegundos, essencial para sincronia de áudio.

2. O MODELO DE GRAFO:
   Diferente de APIs imperativas simples, a Web Audio trabalha com um Grafo de 
   Roteamento. Você conecta saídas de um nó em entradas de outro 
   (Osc -> Filter -> Gain -> Out). Isso permite processamento complexo em tempo real.

3. OSCILLATORS (SYNTHESIS):
   Geradores de som puro. Podem ser Senoides (suaves), Quadradas (agressivas), 
   Dente de Serra (brilhantes) ou Triangulares. São recursos de baixo custo 
   comparados a carregar arquivos binários.

4. AUTOMATION PARAMETERS (AudioParam):
   O segredo do som profissional. Métodos como 'exponentialRampToValueAtTime' 
   garantem transições suaves que o hardware de áudio consegue processar sem 
   gerar artefatos digitais (estalos).
===============================================================================
*/

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */
