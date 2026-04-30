/**
 * @file worker.js
 * @brief O Cérebro do Processamento (Background Thread).
 */

// Escuta mensagens da thread principal
self.onmessage = function(e) {
    if (e.data === 'START_CALCULATION') {
        console.log("[WORKER] Recebido sinal de início. Iniciando loop massivo...");
        
        // Simulação de cálculo pesado (Ex: processamento de telemetria)
        const totalPassos = 10;
        const iteraçõesPorPasso = 50000000; // 50 milhões

        for (let i = 1; i <= totalPassos; i++) {
            // Cálculo 'inútil' apenas para gastar CPU
            let dummy = 0;
            for (let j = 0; j < iteraçõesPorPasso; j++) {
                dummy += Math.sqrt(j);
            }

            // Envia o progresso de volta para a Thread Principal
            const progresso = (i / totalPassos) * 100;
            self.postMessage({ type: 'PROGRESS', value: progresso });
        }

        // Envia o resultado final
        self.postMessage({ type: 'COMPLETE', result: "500 MILHÕES DE PONTOS CALCULADOS." });
    }
};
