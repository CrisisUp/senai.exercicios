/**
 * @file Atividade14.tsx
 * @brief Implementação/Componente Atividade14.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState } from 'react';
import styles from './Atividade14.module.css';

interface SensorData {
  id: number;
  value: number;
  status: 'OPTIMAL' | 'WARNING' | 'CRITICAL';
}

const Atividade14: React.FC = () => {
  const [sensors, setSensors] = useState<SensorData[]>([]);
  const [renderTime, setRenderTime] = useState<number>(0);
  const [isGenerating, setIsRunning] = useState(false);

  /**
   * @section Batch Processing (O Segredo da Performance)
   * Em Vanilla, usaríamos DocumentFragment. No React, geramos o array 
   * completo e o injetamos no estado em um ÚNICO "tiro" (setSensors).
   */
  const generateSensorsBatch = () => {
    const start = performance.now();
    
    const newSensors: SensorData[] = Array.from({ length: 100 }, (_, i) => {
      const val = Math.floor(Math.random() * 100);
      return {
        id: i + 1,
        value: val,
        status: val > 80 ? 'CRITICAL' : val > 50 ? 'WARNING' : 'OPTIMAL'
      };
    });

    setSensors(newSensors);
    
    const end = performance.now();
    setRenderTime(end - start);
    setIsRunning(true);
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Grade de Comando Tática - Dubai Node</h1>
        <div className={styles.performanceMonitor}>
          <span className={styles.label}>BATCH LATENCY:</span>
          <span className={styles.value}>{renderTime.toFixed(4)} ms</span>
        </div>
      </header>

      <main className={styles.main}>
        <div className={styles.controlBar}>
          <button onClick={generateSensorsBatch} className={styles.btnInit}>
            {isGenerating ? 'RE-SCAN SENSOR GRID' : 'INITIALIZE SENSOR GRID'}
          </button>
          <span className={styles.count}>Nodes Ativos: {sensors.length}</span>
        </div>

        {/* CSS GRID em Ação (Requisito de Elite) */}
        <section className={styles.sensorGrid}>
          {sensors.map(sensor => (
            <div 
              key={sensor.id} 
              className={`${styles.sensorNode} ${styles[sensor.status]}`}
            >
              <div className={styles.nodeId}>#{sensor.id.toString().padStart(3, '0')}</div>
              <div className={styles.nodeValue}>{sensor.value}<small>%</small></div>
              <div className={styles.statusLabel}>{sensor.status}</div>
            </div>
          ))}
          {!isGenerating && (
            <div className={styles.placeholder}>SISTEMA EM STANDBY. AGUARDANDO COMANDO INICIAL...</div>
          )}
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Arquiteto: CSS Grid & Batching</h4>
          <p>
            O <strong>CSS Grid</strong> permite criar esta grade 2D complexa com poucas linhas de código, 
            evitando aninhamento excessivo de containers. Diferente da manipulação manual do DOM 
            (que exigiria DocumentFragment), o <strong>React Batching</strong> garante que a atualização 
            dos 100 sensores ocorra em um único ciclo de renderização do Virtual DOM, minimizando 
            o custo de CPU para o navegador.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade14;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
