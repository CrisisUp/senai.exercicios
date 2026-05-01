/**
 * @file script.js
 * @brief SkyCargo Hypersonic Command v4.0 - Integrated Controller
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

document.addEventListener('DOMContentLoaded', () => {
    // UI Selectors
    const btnInit = document.getElementById('btn-init-system');
    const btnStop = document.getElementById('btn-emergency');
    const btnWipe = document.getElementById('btn-export');
    const altEl = document.getElementById('alt-val');
    const velEl = document.getElementById('vel-val');
    const batEl = document.getElementById('bat-val');
    const batBar = document.getElementById('bat-progress');
    const latEl = document.getElementById('lat-val');
    const lngEl = document.getElementById('lng-val');
    const hzEl = document.getElementById('atomic-hz');
    const totalLogsEl = document.getElementById('total-logs');
    const logsBody = document.getElementById('logs-body');
    const droneTarget = document.getElementById('drone-target');
    const audioCanvas = document.getElementById('audio-canvas');
    const ticker = document.getElementById('ticker-msg');

    // Global State
    let db = null;
    let worker = null;
    let audioCtx = null;
    let mainOsc = null;
    let analyzer = null;
    let sharedArray = null;
    let totalLogs = 0;

    // 1. IndexedDB Module (Persistence)
    function initDB() {
        return new Promise((resolve) => {
            const req = indexedDB.open('SkyCargo_V4_BlackBox', 1);
            req.onupgradeneeded = (e) => {
                const db = e.target.result;
                db.createObjectStore('telemetry_batch', { keyPath: 'id', autoIncrement: true });
            };
            req.onsuccess = (e) => {
                db = e.target.result;
                resolve();
            };
        });
    }

    function saveBatch(batch) {
        if (!db) return;
        const tx = db.transaction(['telemetry_batch'], 'readwrite');
        const store = tx.objectStore('telemetry_batch');
        store.add({ timestamp: Date.now(), data: batch });
        
        tx.oncomplete = () => {
            totalLogs += batch.length;
            totalLogsEl.textContent = totalLogs;
            updateLogTable(batch[0]); // Show one sample from batch
        };
    }

    // 2. Audio Module (Sonic Feedback)
    function initAudio() {
        audioCtx = new (window.AudioContext || window.webkitAudioContext)();
        analyzer = audioCtx.createAnalyser();
        const gain = audioCtx.createGain();
        
        mainOsc = audioCtx.createOscillator();
        mainOsc.type = 'sine';
        mainOsc.frequency.value = 440;
        
        mainOsc.connect(gain);
        gain.connect(analyzer);
        analyzer.connect(audioCtx.destination);
        
        gain.gain.value = 0.1;
        mainOsc.start();
        
        startOscilloscope();
    }

    function updateAudio(altitude) {
        if (!mainOsc) return;
        const freq = 200 + (altitude / 50);
        mainOsc.frequency.setTargetAtTime(freq, audioCtx.currentTime, 0.1);
    }

    // 3. Shared Memory Module (Performance)
    function initSystem() {
        if (worker) return;

        // SharedArrayBuffer (7 indices * 4 bytes = 28 bytes)
        const sab = new SharedArrayBuffer(32);
        sharedArray = new Int32Array(sab);
        
        // Initial Values
        Atomics.store(sharedArray, 2, 100); // Bateria
        Atomics.store(sharedArray, 3, 50);  // X
        Atomics.store(sharedArray, 4, 50);  // Y
        Atomics.store(sharedArray, 5, 1);   // Control (RUN)

        worker = new Worker('js/worker.js');
        worker.postMessage({ sharedBuffer: sab });
        
        worker.onmessage = (e) => {
            if (e.data.type === 'BATCH_LOG') {
                saveBatch(e.data.data);
            }
        };

        initAudio();
        startUpdateLoop();
        ticker.textContent = "SYSTEM ONLINE | HYPERSONIC LINK SECURED | RECORDING...";
    }

    // 4. UI Loop (Atomic Read)
    function startUpdateLoop() {
        function update() {
            const alt = Atomics.load(sharedArray, 0);
            const vel = Atomics.load(sharedArray, 1) / 100;
            const bat = Atomics.load(sharedArray, 2);
            const x = Atomics.load(sharedArray, 3);
            const y = Atomics.load(sharedArray, 4);
            const hz = Atomics.exchange(sharedArray, 6, 0); // Read and Reset Hz Counter

            // DOM Updates
            altEl.textContent = alt;
            velEl.textContent = vel.toFixed(2);
            batEl.textContent = bat;
            batBar.style.width = `${bat}%`;
            latEl.textContent = (45 + (y/100)).toFixed(4);
            lngEl.textContent = (-122 + (x/100)).toFixed(4);
            hzEl.textContent = `PROCESS RATE: ${hz} Hz`;
            
            // Radar Update
            droneTarget.style.left = `${x}%`;
            droneTarget.style.top = `${y}%`;

            updateAudio(alt);

            requestAnimationFrame(update);
        }
        requestAnimationFrame(update);
    }

    // 5. Visualizer
    function startOscilloscope() {
        const ctx = audioCanvas.getContext('2d');
        const buffer = analyzer.frequencyBinCount;
        const data = new Uint8Array(buffer);

        function draw() {
            requestAnimationFrame(draw);
            analyzer.getByteTimeDomainData(data);
            ctx.fillStyle = '#000';
            ctx.fillRect(0, 0, audioCanvas.width, audioCanvas.height);
            ctx.lineWidth = 2;
            ctx.strokeStyle = '#00d4ff';
            ctx.beginPath();
            const sliceWidth = audioCanvas.width / buffer;
            let x = 0;
            for (let i = 0; i < buffer; i++) {
                const v = data[i] / 128.0;
                const y = v * audioCanvas.height / 2;
                if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
                x += sliceWidth;
            }
            ctx.stroke();
        }
        draw();
    }

    function updateLogTable(sample) {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${new Date(sample.t).toLocaleTimeString()}</td>
            <td>TELEMETRY_BATCH</td>
            <td>${sample.a}m</td>
        `;
        logsBody.prepend(row);
        if (logsBody.children.length > 10) logsBody.lastElementChild.remove();
    }

    // Buttons
    btnInit.addEventListener('click', () => {
        initDB().then(initSystem);
        btnInit.disabled = true;
    });

    btnStop.addEventListener('click', () => {
        if (sharedArray) Atomics.store(sharedArray, 5, 0);
        ticker.textContent = "EMERGENCY SHUTDOWN TRIGGERED. ALL MODULES HALTED.";
        ticker.style.color = "var(--accent-red)";
    });

    btnWipe.addEventListener('click', () => {
        if (!db) return;
        const tx = db.transaction(['telemetry_batch'], 'readwrite');
        tx.objectStore('telemetry_batch').clear();
        tx.oncomplete = () => {
            totalLogs = 0;
            totalLogsEl.textContent = '0';
            logsBody.innerHTML = '';
            ticker.textContent = "BLACK BOX WIPED. CLEAN SLATE FOR NEXT MISSION.";
        };
    });
});

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
