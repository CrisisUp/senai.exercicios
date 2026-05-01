/**
 * @file Atividade03.tsx
 * @brief Implementação/Componente Atividade03.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState, useMemo } from 'react';
import styles from './Atividade03.module.css';

const Atividade03: React.FC = () => {
  // Estado para simular a bateria do drone
  const [battery, setBattery] = useState<number>(85);
  
  // Constante de autonomia (Requisito: Bateria * 1.5 km)
  const rangeMultiplier = 1.5;
  
  // Cálculo de Autonomia (Memoizado para performance, embora simples aqui)
  const range = useMemo(() => (battery * rangeMultiplier).toFixed(2), [battery]);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Monitor de Autonomia - Nexus v4.0</h1>
        <p>Análise de Performance Geométrica e Energética</p>
      </header>

      <main className={styles.mainContent}>
        <section className={styles.droneCard}>
          <div className={styles.imageContainer}>
            <img 
              src="https://images.unsplash.com/photo-1508614589041-895b88991e3e?auto=format&fit=crop&w=600&q=80" 
              alt="Drone de Carga Industrial" 
              className={styles.droneImage}
            />
          </div>
          
          <div className={styles.infoArea}>
            <h3>Drone SkyCargo Stealth</h3>
            <div className={styles.statRow}>
              <label>Bateria Atual:</label>
              <input 
                type="range" 
                min="0" 
                max="100" 
                value={battery} 
                onChange={(e) => setBattery(Number(e.target.value))}
                className={styles.slider}
              />
              <span className={styles.statValue}>{battery}%</span>
            </div>
            
            <div className={styles.resultBox}>
              <p>Autonomia Estimada:</p>
              <span className={styles.rangeValue}>{range} km</span>
            </div>
          </div>
        </section>

        <section className={styles.theoryNote}>
          <h4>Nota Técnica: Box Model & Matemática</h4>
          <p>O card acima utiliza o <strong>CSS Box Model</strong> para garantir que a imagem e os dados não colapsem. O cálculo de autonomia é reativo: qualquer mudança no estado da bateria atualiza instantaneamente a distância operacional.</p>
        </section>
      </main>
    </div>
  );
};

export default Atividade03;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
