/**
 * @file worker.js
 * @brief Telemetry Engine using SharedArrayBuffer & Atomics.
 */

self.onmessage = (event) => {
    const { sharedBuffer, config } = event.data;
    
    // Criando a visão de dados sobre a memória compartilhada
    // Índice 0: Altitude
    // Índice 1: Bateria
    // Índice 2: Sinal de Controle (0=Stop, 1=Run)
    // Índice 3: Contador de Sinais
    const sharedArray = new Int32Array(sharedBuffer);

    function startStreaming() {
        if (Atomics.load(sharedArray, 2) === 0) return;

        // Simulação de telemetria hipersônica (alta frequência)
        const altitude = Math.floor(Math.random() * 100) + 10000;
        const battery = Math.floor(Math.random() * 100);

        // ESCRITA ATÔMICA: Garante que a Main Thread não leia um valor parcial
        Atomics.store(sharedArray, 0, altitude);
        Atomics.store(sharedArray, 1, battery);
        
        // Incrementa contador de sinais processados
        Atomics.add(sharedArray, 3, 1);

        // Notifica a Main Thread que os dados mudaram (opcional para polling de alta freq)
        // Atomics.notify(sharedArray, 0); 

        setTimeout(startStreaming, 1); // 1ms = 1000Hz
    }

    // Monitora o sinal de controle via Atomics.wait (Bloqueia a thread do worker eficientemente)
    while (true) {
        const controlState = Atomics.load(sharedArray, 2);
        
        if (controlState === 1) {
            startStreaming();
            break; // Sai do loop de espera e entra no stream
        }
        
        // Espera no índice 2 até que o valor mude de 0
        Atomics.wait(sharedArray, 2, 0);
    }
};
