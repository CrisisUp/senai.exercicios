/**
 * @file script.js
 * @brief Nexus Terminal v3.0 - Orchestration of Integrated APIs.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

document.addEventListener('DOMContentLoaded', () => {
    // UI Elements
    const radarCanvas = document.getElementById('radar-canvas');
    const terminalOutput = document.getElementById('terminal-output');
    const netStatusEl = document.getElementById('net-status');
    const batteryEl = document.getElementById('drone-battery');
    const weightEl = document.getElementById('current-weight');
    const weightProgress = document.getElementById('weight-progress');
    const tickerMsg = document.getElementById('ticker-msg');
    const btnNotify = document.getElementById('btn-notify');

    // State
    let currentWeight = 0;
    const MAX_WEIGHT = 300;
    let isSocketOpen = false;

    /**
     * @section Módulo 1: Conectividade (WebSocket Simulation)
     */
    function initWebSocket() {
        log("CONECTANDO AO NEXUS SAT-LINK...", "warn");
        
        // Simulação de WebSocket (usando o servidor de eco para fins didáticos)
        const socket = new WebSocket('wss://echo.websocket.org');

        socket.onopen = () => {
            isSocketOpen = true;
            netStatusEl.textContent = "ONLINE";
            netStatusEl.className = "value status-online";
            log("LINK SATELITAL ESTABELECIDO.");
            tickerMsg.textContent = "REAL-TIME TELEMETRY ACTIVE | ALL SYSTEMS NOMINAL";
        };

        socket.onmessage = (event) => {
            try {
                const data = JSON.parse(event.data);
                updateTelemetry(data);
            } catch (e) {
                // Se não for JSON, é apenas o eco de texto
            }
        };

        socket.onclose = () => {
            isSocketOpen = false;
            netStatusEl.textContent = "OFFLINE";
            netStatusEl.className = "value status-offline";
            log("LINK SATELITAL PERDIDO! ACIONANDO CACHE LOCAL.", "crit");
            tickerMsg.textContent = "OFFLINE MODE | USING LOCAL MISSION DATA";
            document.body.classList.add('is-offline');
        };

        // Telemetria Simulada enviando pro Socket
        setInterval(() => {
            if (isSocketOpen) {
                const telemetry = {
                    battery: Math.floor(Math.random() * 20) + 80,
                    coords: { x: Math.random() * 100, y: Math.random() * 100 }
                };
                socket.send(JSON.stringify(telemetry));
            }
        }, 3000);
    }

    function updateTelemetry(data) {
        batteryEl.textContent = `${data.battery}%`;
        document.getElementById('radar-coords').textContent = `POS: ${data.coords.x.toFixed(2)}, ${data.coords.y.toFixed(2)}`;
        
        if (data.battery < 20) {
            log(`ALERTA: Bateria crítica no Drone (${data.battery}%)`, "crit");
            notify("LOW BATTERY", `Drone telemetry indicates ${data.battery}% remaining.`);
        }
    }

    /**
     * @section Módulo 2: Logística (Drag & Drop)
     */
    function initLogistics() {
        const cargoItems = document.querySelectorAll('.cargo-item');
        const droneBay = document.getElementById('drone-bay');

        cargoItems.forEach(item => {
            item.addEventListener('dragstart', (e) => {
                e.dataTransfer.setData('application/json', JSON.stringify({
                    id: item.dataset.id,
                    weight: parseInt(item.dataset.weight)
                }));
                item.classList.add('dragging');
            });

            item.addEventListener('dragend', () => item.classList.remove('dragging'));
        });

        droneBay.addEventListener('dragover', (e) => e.preventDefault());
        droneBay.addEventListener('dragenter', () => droneBay.classList.add('drag-over'));
        droneBay.addEventListener('dragleave', () => droneBay.classList.remove('drag-over'));

        droneBay.addEventListener('drop', (e) => {
            e.preventDefault();
            droneBay.classList.remove('drag-over');
            
            const data = JSON.parse(e.dataTransfer.getData('application/json'));
            
            if (currentWeight + data.weight > MAX_WEIGHT) {
                log(`FALHA: Sobrecarga detectada para item ${data.id}`, "crit");
                notify("OVERLOAD ALERT", `Cargo ${data.id} exceeds safety limits.`);
                return;
            }

            currentWeight += data.weight;
            updateWeightUI();
            log(`CARGA ${data.id} (${data.weight}kg) ACOPLADA AO DECK.`);
            
            // Persistência local (Offline Ready)
            saveMissionState();
        });
    }

    function updateWeightUI() {
        weightEl.textContent = currentWeight;
        const perc = (currentWeight / MAX_WEIGHT) * 100;
        weightProgress.style.width = `${perc}%`;
        
        if (perc > 90) weightProgress.style.background = "var(--accent-red)";
        else if (perc > 70) weightProgress.style.background = "var(--accent-yellow)";
    }

    /**
     * @section Módulo 3: Sobrevivência (Service Workers & Cache)
     */
    function initServiceWorker() {
        if ('serviceWorker' in navigator) {
            navigator.serviceWorker.register('sw.js')
                .then(() => log("SERVICE WORKER: ATIVO (OFFLINE SYNC ENABLED)"))
                .catch(() => log("SERVICE WORKER: FALHA NO REGISTRO", "crit"));
        }
    }

    function saveMissionState() {
        localStorage.setItem('nexus_mission_weight', currentWeight);
    }

    function loadMissionState() {
        const savedWeight = localStorage.getItem('nexus_mission_weight');
        if (savedWeight) {
            currentWeight = parseInt(savedWeight);
            updateWeightUI();
            log("ESTADO DE MISSÃO RESTAURADO DO STORAGE LOCAL.");
        }
    }

    /**
     * @section Módulo 4: Notificações
     */
    btnNotify.addEventListener('click', () => {
        Notification.requestPermission().then(permission => {
            if (permission === 'granted') {
                log("NOTIFICAÇÕES HABILITADAS.");
                btnNotify.style.display = 'none';
            }
        });
    });

    function notify(title, body) {
        if (Notification.permission === 'granted') {
            new Notification(`NEXUS ALERT: ${title}`, {
                body: body,
                icon: 'https://cdn-icons-png.flaticon.com/512/579/579268.png'
            });
        }
    }

    // Utilitários
    function log(msg, type = 'info') {
        const entry = document.createElement('div');
        entry.className = `log-entry ${type}`;
        entry.textContent = `[${new Date().toLocaleTimeString()}] ${msg}`;
        terminalOutput.prepend(entry);
    }

    // Inicialização Total
    initServiceWorker();
    initWebSocket();
    initLogistics();
    loadMissionState();
});

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
