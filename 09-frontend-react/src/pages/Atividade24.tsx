import React, { useState, useEffect, useRef } from 'react';
import styles from './Atividade24.module.css';

/**
 * @page Atividade24
 * @brief Processamento Paralelo: Mastering Web Workers no React.
 */
const Atividade24: React.FC = () => {
  const [progress, setProgress] = useState(0);
  const [status, setStatus] = useState<'IDLE' | 'PROCESSING' | 'FINISHED'>('IDLE');
  const [logs, setLogs] = useState<string[]>([]);
  
  const radarRef = useRef<HTMLCanvasElement>(null);
  const workerRef = useRef<Worker | null>(null);
  const angleRef = useRef(0);

  // 1. MOTOR DE UI: Animação de Radar (Thread Principal)
  useEffect(() => {
    const canvas = radarRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    const animate = () => {
      ctx.fillStyle = "rgba(0, 0, 0, 0.05)";
      ctx.fillRect(0, 0, canvas.width, canvas.height);

      const x = 100 + Math.cos(angleRef.current) * 90;
      const y = 100 + Math.sin(angleRef.current) * 90;

      ctx.strokeStyle = "#00f2ff";
      ctx.lineWidth = 2;
      ctx.beginPath();
      ctx.moveTo(100, 100);
      ctx.lineTo(x, y);
      ctx.stroke();

      angleRef.current += 0.05;
      requestAnimationFrame(animate);
    };

    const animId = requestAnimationFrame(animate);
    return () => cancelAnimationFrame(animId);
  }, []);

  // 2. GESTÃO DO WORKER (Thread de Fundo)
  const iniciarSimulacao = () => {
    setLogs(["> [INFO] Operação em Background iniciada."]);
    setStatus('PROCESSING');
    setProgress(0);

    // Instancia o Worker usando a sintaxe compatível com Vite
    const worker = new Worker(new URL('./Atividade24.worker.ts', import.meta.url), { type: 'module' });
    workerRef.current = worker;

    worker.onmessage = (e) => {
      const { type, value, result } = e.data;
      if (type === 'PROGRESS') {
        setProgress(value);
      } else if (type === 'COMPLETE') {
        setStatus('FINISHED');
        setLogs(prev => [...prev, `> [SUCCESS] ${result}`]);
        worker.terminate();
      }
    };

    worker.postMessage('START_CALCULATION');
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Processamento Paralelo</h1>
        <p>Thread de Fundo (Web Workers) para cálculos massivos sem UI Freeze.</p>
      </header>

      <main className={styles.dashboard}>
        {/* Lado Esquerdo: UI Thread (Monitor) */}
        <section className={styles.card}>
          <h2>UI Thread: Radar Ativo</h2>
          <canvas ref={radarRef} width={200} height={200} className={styles.radarCanvas} />
          <div className={styles.statusInfo}>
            <span className={styles.statusLabel}>Monitor: </span>
            <span className={styles.statusValue}>60 FPS ESTÁVEL</span>
          </div>
        </section>

        {/* Lado Direito: Worker Thread (Cálculo) */}
        <section className={styles.card}>
          <h2>Worker Thread: Simulação</h2>
          <div className={styles.statusInfo}>
            <span className={styles.statusLabel}>Carga CPU: </span>
            <span className={styles.statusValue} style={{ color: status === 'PROCESSING' ? '#fbbf24' : '#10b981' }}>
              {status}
            </span>
          </div>

          <div className={styles.progressContainer}>
            <div className={styles.progressBar}>
              <div className={styles.progressFill} style={{ width: `${progress}%` }}></div>
            </div>
            <div style={{ marginTop: '0.5rem', fontSize: '0.8rem', color: '#9ca3af' }}>
              Progresso: {Math.round(progress)}%
            </div>
          </div>

          <div className={styles.logArea}>
            {logs.map((log, i) => <div key={i}>{log}</div>)}
          </div>

          <button 
            className={styles.btnAction} 
            onClick={iniciarSimulacao}
            disabled={status === 'PROCESSING'}
          >
            {status === 'PROCESSING' ? 'PROCESSANDO EM SEGUNDO PLANO...' : 'INICIAR CÁLCULO MASSIVO'}
          </button>
        </section>
      </main>

      <footer className={styles.theoryBox}>
        <h4>Nota do Engenheiro: O Poder das Threads</h4>
        <p>
          O JavaScript é <i>Single-Threaded</i> por padrão. Se executássemos o cálculo de 500 milhões de pontos na thread principal, 
          o radar à esquerda travaria completamente até o fim do processo.
          <br /><br />
          O <strong>Web Worker</strong> cria um universo paralelo. Ele realiza o trabalho pesado e nos envia apenas o 
          resultado via mensagens (<code>postMessage</code>), mantendo a interface 100% responsiva para o operador.
        </p>
      </footer>
    </div>
  );
};

export default Atividade24;
