import React, { useRef, useEffect, useState } from 'react';
import styles from './Atividade22.module.css';

/**
 * @page Atividade22
 * @brief Movimento de Precisão: Mastering RequestAnimationFrame.
 */
const Atividade22: React.FC = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [isActive, setIsActive] = useState(true);
  const [uptime, setUptime] = useState(0);
  const requestRef = useRef<number>();
  const angleRef = useRef(0);
  const startTimeRef = useRef(Date.now());

  const canvasSize = 400;
  const centerX = canvasSize / 2;
  const centerY = canvasSize / 2;
  const radius = canvasSize / 2 - 10;

  const drawBackground = (ctx: CanvasRenderingContext2D) => {
    ctx.strokeStyle = "rgba(0, 242, 255, 0.1)";
    ctx.lineWidth = 1;

    // Círculos de distância
    for (let i = 1; i <= 4; i++) {
      ctx.beginPath();
      ctx.arc(centerX, centerY, (radius / 4) * i, 0, Math.PI * 2);
      ctx.stroke();
    }

    // Eixos cardeais
    ctx.beginPath();
    ctx.moveTo(centerX, 10); ctx.lineTo(centerX, canvasSize - 10);
    ctx.moveTo(10, centerY); ctx.lineTo(canvasSize - 10, centerY);
    ctx.stroke();
  };

  const animate = () => {
    if (!isActive) return;

    const canvas = canvasRef.current;
    if (!canvas) return;

    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    // 1. Efeito de Rastro (Ghosting)
    ctx.fillStyle = "rgba(0, 0, 0, 0.05)";
    ctx.fillRect(0, 0, canvasSize, canvasSize);

    drawBackground(ctx);

    // 2. Cálculo da Agulha (Trigonometria)
    const x = centerX + Math.cos(angleRef.current) * radius;
    const y = centerY + Math.sin(angleRef.current) * radius;

    // 3. Desenho da Varredura (Sweep)
    ctx.strokeStyle = "#60a5fa";
    ctx.lineWidth = 3;
    ctx.shadowBlur = 15;
    ctx.shadowColor = "#00f2ff";
    
    ctx.beginPath();
    ctx.moveTo(centerX, centerY);
    ctx.lineTo(x, y);
    ctx.stroke();
    
    ctx.shadowBlur = 0;

    // 4. Evolução do Estado
    angleRef.current += 0.03;
    setUptime(Math.floor((Date.now() - startTimeRef.current) / 1000));

    // 5. Próximo Quadro
    requestRef.current = requestAnimationFrame(animate);
  };

  useEffect(() => {
    if (isActive) {
      requestRef.current = requestAnimationFrame(animate);
    } else {
      if (requestRef.current) cancelAnimationFrame(requestRef.current);
    }
    return () => {
      if (requestRef.current) cancelAnimationFrame(requestRef.current);
    };
  }, [isActive]);

  const toggleEngine = () => setIsActive(!isActive);

  const resetEngine = () => {
    angleRef.current = 0;
    startTimeRef.current = Date.now();
    setUptime(0);
    const canvas = canvasRef.current;
    if (canvas) {
      const ctx = canvas.getContext('2d');
      ctx?.clearRect(0, 0, canvasSize, canvasSize);
    }
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Movimento de Precisão</h1>
        <p>Loop de Renderização de Elite (RequestAnimationFrame & Ghosting).</p>
      </header>

      <main className={styles.radarContainer}>
        <div className={styles.statusPanel}>
          <div className={styles.statusItem}>
            <span>STATUS: </span>
            <span style={{ color: isActive ? '#10b981' : '#ef4444' }}>
              {isActive ? 'OPERACIONAL' : 'SUSPENSO'}
            </span>
          </div>
          <div className={styles.statusItem}>
            <span>UPTIME: </span>
            <span>{uptime}s</span>
          </div>
        </div>

        <div className={styles.canvasWrapper}>
          <canvas 
            ref={canvasRef} 
            width={canvasSize} 
            height={canvasSize} 
            className={styles.radarCanvas}
          />
        </div>

        <div className={styles.controls}>
          <button 
            className={`${styles.btnAction} ${isActive ? styles.btnToggleActive : styles.btnToggle}`} 
            onClick={toggleEngine}
          >
            {isActive ? 'PAUSAR VARREDURA' : 'REATIVAR MOTOR'}
          </button>
          <button className={`${styles.btnAction} ${styles.btnReset}`} onClick={resetEngine}>
            RESETAR COORDENADAS
          </button>
        </div>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: O Loop de Renderização</h4>
          <p>
            No React, animações contínuas exigem cuidado para não causar <i>re-renders</i> desnecessários. 
            Usamos <code>useRef</code> para manter o ângulo da animação e o ID do frame fora do fluxo de estado comum.
            <br /><br />
            O <strong>RequestAnimationFrame</strong> sincroniza o desenho com a taxa de atualização do monitor (V-Sync), 
            enquanto o efeito de rastro é obtido desenhando um retângulo semitransparente em cada frame, 
            fazendo com que os desenhos antigos desbotem progressivamente.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade22;
