/**
 * @file Atividade24.worker.ts
 * @brief O Cérebro do Processamento Paralelo.
 */

self.onmessage = (e: MessageEvent) => {
  if (e.data === 'START_CALCULATION') {
    const totalSteps = 10;
    const iterationsPerStep = 50000000; // 50 milhões de iterações

    for (let i = 1; i <= totalSteps; i++) {
      // eslint-disable-next-line @typescript-eslint/no-unused-vars
      let dummy = 0;
      for (let j = 0; j < iterationsPerStep; j++) {
        dummy += Math.sqrt(j);
      }

      const progress = (i / totalSteps) * 100;
      self.postMessage({ type: 'PROGRESS', value: progress });
    }

    self.postMessage({ 
      type: 'COMPLETE', 
      result: "500 MILHÕES DE PONTOS DE TELEMETRIA CALCULADOS." 
    });
  }
};

export {};
