/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Main Thread Controller for Shared Memory & Atomics.
 */

document.addEventListener('DOMContentLoaded', () => {
    const btnStart = document.getElementById('btn-start');
    const btnStop = document.getElementById('btn-stop');
    const securityStatus = document.getElementById('security-status');
    const atomicLogs = document.getElementById('atomic-logs');
    
    // UI Value Elements
    const altEl = document.getElementById('val-altitude');
    const batEl = document.getElementById('val-battery');
    const sigEl = document.getElementById('val-signals');
    const latencyEl = document.getElementById('bus-latency');

    let worker = null;
    let updateLoop = null;

    // 1. Verificação de Segurança (Requisito SAB)
    if (self.crossOriginIsolated) {
        securityStatus.textContent = "COOP/COEP HEADERS: ACTIVE (SAFE)";
        securityStatus.className = "status-success";
    } else {
        securityStatus.textContent = "COOP/COEP HEADERS: MISSING (SAB DISABLED)";
        securityStatus.className = "status-error";
        log("AVISO: SharedArrayBuffer requer ambiente isolado para funcionar em produção.", "crit");
    }

    // 2. Alocação de Memória Compartilhada (SharedArrayBuffer)
    // Alocamos 4 inteiros de 32 bits (16 bytes)
    const sharedBuffer = new SharedArrayBuffer(16);
    const sharedArray = new Int32Array(sharedBuffer);

    function initWorker() {
        worker = new Worker('js/worker.js');
        worker.postMessage({ sharedBuffer });
        log("Worker inicializado e mapeado para memória compartilhada.");
    }

    btnStart.addEventListener('click', () => {
        if (!worker) initWorker();
        
        // SINAL DE CONTROLE: Muda o índice 2 para 1 (Run) e notifica o worker
        Atomics.store(sharedArray, 2, 1);
        Atomics.notify(sharedArray, 2);
        
        log("Comando ATOMICS.NOTIFY enviado: STREAM START.", "atomic");
        startUIUpdateLoop();
    });

    btnStop.addEventListener('click', () => {
        Atomics.store(sharedArray, 2, 0); // Stop
        cancelAnimationFrame(updateLoop);
        log("Comando ATOMICS.STORE enviado: STREAM STOP.", "atomic");
    });

    function startUIUpdateLoop() {
        const startTime = performance.now();
        
        function update() {
            // LEITURA ATÔMICA: Obtém os valores da RAM sem cópia
            const altitude = Atomics.load(sharedArray, 0);
            const battery = Atomics.load(sharedArray, 1);
            const signals = Atomics.load(sharedArray, 3);

            altEl.textContent = altitude;
            batEl.textContent = battery;
            sigEl.textContent = signals;

            // Medição de latência de barramento (simulada)
            const latency = (performance.now() - startTime) / signals;
            if (signals > 0) latencyEl.textContent = `${latency.toFixed(4)}ms`;

            updateLoop = requestAnimationFrame(update);
        }
        updateLoop = requestAnimationFrame(update);
    }

    function log(msg, type = 'info') {
        const div = document.createElement('div');
        div.className = `log-line ${type}`;
        div.textContent = `[${new Date().toLocaleTimeString()}] ${msg}`;
        atomicLogs.prepend(div);
    }

    /**
     * @section Resumo Teórico
     * SharedArrayBuffer permite que múltiplas threads (Main + Workers) acessem
     * a mesma região de memória física. Isso evita a serialização JSON e a 
     * cópia de dados do postMessage.
     * 
     * Atomics API é essencial porque o hardware e o compilador podem reordenar
     * operações de memória por performance. Atomics garante que a ordem de 
     * escrita e leitura seja respeitada entre as CPUs.
     */
});

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */
