/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file worker.js
 * @brief Hypersonic Telemetry & Batching Engine (v4.0)
 */

self.onmessage = (event) => {
    const { sharedBuffer } = event.data;
    const sharedArray = new Int32Array(sharedBuffer);
    
    // Índices da Memória Compartilhada:
    // 0: Altitude, 1: Velocidade (Mach), 2: Bateria, 3: X, 4: Y, 5: Control, 6: Hz Counter
    
    let isRunning = false;
    let batchBuffer = [];

    function generateTelemetry() {
        if (Atomics.load(sharedArray, 5) === 0) return; // Parar se controle for 0

        // Simulação de Voo Hipersônico
        const alt = 15000 + Math.floor(Math.random() * 500);
        const vel = 5 + (Math.random() * 2); // Mach 5 a 7
        const bat = Math.max(0, Atomics.load(sharedArray, 2) - (Math.random() > 0.99 ? 1 : 0));
        
        // Movimento no Radar (0 a 100)
        let x = Atomics.load(sharedArray, 3) + (Math.random() * 2 - 1);
        let y = Atomics.load(sharedArray, 4) + (Math.random() * 2 - 1);
        
        // Clamp Radar
        if (x < 0 || x > 100) x = 50;
        if (y < 0 || y > 100) y = 50;

        // Escrita Atômica (Zero-Copy)
        Atomics.store(sharedArray, 0, alt);
        Atomics.store(sharedArray, 1, Math.floor(vel * 100)); // Mach * 100 para int
        Atomics.store(sharedArray, 2, bat);
        Atomics.store(sharedArray, 3, Math.floor(x));
        Atomics.store(sharedArray, 4, Math.floor(y));
        Atomics.add(sharedArray, 6, 1); // Incrementa Hz

        // Batching para o IndexedDB (Agrupamos 50 registros por mensagem)
        batchBuffer.push({ t: Date.now(), a: alt, v: vel.toFixed(2), b: bat });
        
        if (batchBuffer.length >= 50) {
            self.postMessage({ type: 'BATCH_LOG', data: batchBuffer });
            batchBuffer = [];
        }

        setTimeout(generateTelemetry, 1); // 1000Hz
    }

    // Monitor de Inicialização
    const checkControl = () => {
        if (Atomics.load(sharedArray, 5) === 1) {
            generateTelemetry();
        } else {
            setTimeout(checkControl, 100);
        }
    };
    
    checkControl();
};

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
