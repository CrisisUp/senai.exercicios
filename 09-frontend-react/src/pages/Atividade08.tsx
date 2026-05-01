/**
 * @file Atividade08.tsx
 * @brief Implementação/Componente Atividade08.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState, useEffect } from 'react';
import styles from './Atividade08.module.css';

interface DroneState {
  id: string;
  name: string;
  battery: number;
}

const Atividade08: React.FC = () => {
  // Estado para dois drones em missão
  const [drones, setDrones] = useState<DroneState[]>([
    { id: 'DX-01', name: 'Desert Storm', battery: 100 },
    { id: 'DX-02', name: 'Ocean Pearl', battery: 100 },
  ]);

  /**
   * @section Automação de Telemetria (Requisito de Elite)
   * Uso de useEffect com cleanup para gerenciar o setInterval.
   */
  useEffect(() => {
    const interval = setInterval(() => {
      setDrones(prevDrones => 
        prevDrones.map(drone => ({
          ...drone,
          battery: Math.max(0, drone.battery - 1) // Consumo de 1%
        }))
      );
      console.log("[TELEMETRY] Bateria atualizada via Intervalo.");
    }, 3000); // 3 Segundos

    // CLEANUP: Vital para evitar Processos Zumbis
    return () => clearInterval(interval);
  }, []);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Nexus Dashboard - Live Feed</h1>
        <div className={styles.heartbeatArea}>
          <div className={styles.led}></div>
          <span>SISTEMA ATIVO - MONITORANDO...</span>
        </div>
      </header>

      <main className={styles.dashboard}>
        {drones.map(drone => (
          <section key={drone.id} className={styles.droneCard}>
            <div className={styles.radarContainer}>
              <div className={styles.radarCircle}>
                <div className={styles.radarScan}></div>
                <div className={styles.dronePoint}></div>
              </div>
            </div>

            <div className={styles.info}>
              <h3>{drone.name} <small>[{drone.id}]</small></h3>
              <div className={styles.batteryArea}>
                <div className={styles.batteryLabel}>NÍVEL DE ENERGIA:</div>
                <div className={styles.batteryBar}>
                  <div 
                    className={styles.batteryFill} 
                    style={{ 
                      width: `${drone.battery}%`,
                      backgroundColor: drone.battery > 20 ? '#39ff14' : '#ff3131'
                    }}
                  ></div>
                </div>
                <span className={styles.percentText}>{drone.battery}%</span>
              </div>
              <div className={styles.statusMsg}>
                {drone.battery > 0 ? 'EM OPERAÇÃO' : 'UNIDADE DESLIGADA'}
              </div>
            </div>
          </section>
        ))}
      </main>

      <footer className={styles.theoryBox}>
        <h4>Nota Técnica: Ciclo de Vida e Efeitos</h4>
        <p>
          No React, o <code>setInterval</code> deve ser encapsulado no hook <code>useEffect</code>. 
          A função de retorno (cleanup) é a nossa blindagem contra <strong>vazamentos de memória</strong>: 
          ao sair desta página, o intervalo é destruído, impedindo que o navegador continue processando dados 
          de uma tela que não está mais visível.
        </p>
      </footer>
    </div>
  );
};

export default Atividade08;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
