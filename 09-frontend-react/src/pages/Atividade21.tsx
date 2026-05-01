/**
 * @file Atividade21.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useRef, useEffect, useState } from 'react';
import styles from './Atividade21.module.css';

interface DronePoint {
  x: number;
  y: number;
  id: number;
}

/**
 * @page Atividade21
 * @brief Monitor de Radar Tático (HTML5 Canvas no React).
 */
const Atividade21: React.FC = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [drones, setDrones] = useState<DronePoint[]>([]);
  const [scanCount, setScanCount] = useState(0);

  const canvasSize = 400;
  const centerX = canvasSize / 2;
  const centerY = canvasSize / 2;

  // Efeito principal de renderização
  useEffect(() => {
    // Função para desenhar a grade do radar
    const drawGrid = (ctx: CanvasRenderingContext2D) => {
      ctx.strokeStyle = "rgba(46, 160, 67, 0.4)";
      ctx.lineWidth = 1;

      // Círculos concêntricos
      for (let r = 50; r <= 200; r += 50) {
        ctx.beginPath();
        ctx.arc(centerX, centerY, r, 0, Math.PI * 2);
        ctx.stroke();
      }

      // Eixos táticos
      ctx.beginPath();
      ctx.moveTo(centerX, 0); ctx.lineTo(centerX, canvasSize);
      ctx.moveTo(0, centerY); ctx.lineTo(canvasSize, centerY);
      ctx.stroke();
    };

    // Função para desenhar os drones
    const drawDrones = (ctx: CanvasRenderingContext2D) => {
      drones.forEach(drone => {
        ctx.fillStyle = "#ffffff";
        ctx.shadowBlur = 15;
        ctx.shadowColor = "#00f2ff";
        
        ctx.beginPath();
        ctx.arc(drone.x, drone.y, 5, 0, Math.PI * 2);
        ctx.fill();
        
        // Reset shadow para não afetar outros desenhos
        ctx.shadowBlur = 0;
      });
    };

    const canvas = canvasRef.current;
    if (!canvas) return;

    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    // Limpeza e Redesenho (Ciclo de Vida do Canvas)
    ctx.clearRect(0, 0, canvasSize, canvasSize);
    drawGrid(ctx);
    drawDrones(ctx);
  }, [drones, centerX, centerY, canvasSize]);

  const scanArea = () => {
    const angle = Math.random() * Math.PI * 2;
    const dist = Math.random() * 180;
    
    const newDrone: DronePoint = {
      x: centerX + Math.cos(angle) * dist,
      y: centerY + Math.sin(angle) * dist,
      id: Date.now()
    };

    setDrones(prev => [...prev, newDrone]);
    setScanCount(prev => prev + 1);
  };

  const resetRadar = () => {
    setDrones([]);
    setScanCount(0);
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Monitor de Radar Tático</h1>
        <p>Visualização de Unidades em Tempo Real via GPU (HTML5 Canvas).</p>
      </header>

      <main>
        <div className={styles.radarWrapper}>
          <canvas 
            ref={canvasRef} 
            width={canvasSize} 
            height={canvasSize} 
            className={styles.radarCanvas}
          />
        </div>

        <div className={styles.controls}>
          <button className={styles.btnAction} onClick={scanArea}>
            VARREDURA DE ÁREA ({scanCount})
          </button>
          <button className={styles.btnReset} onClick={resetRadar}>
            REINICIALIZAR MONITOR
          </button>
        </div>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: Canvas vs DOM</h4>
          <p>
            No React, o <strong>Canvas</strong> é tratado como um elemento "caixa preta". 
            Usamos o <code>useRef</code> para obter o contexto de desenho e o <code>useEffect</code> para 
            sincronizar o estado do React (nossa lista de drones) com os pixels na tela.
            <br /><br />
            Diferente de criar centenas de <code>&lt;div&gt;</code>, o Canvas mantém a performance constante 
            mesmo com milhares de objetos, sendo ideal para painéis de telemetria e jogos industriais.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade21;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
