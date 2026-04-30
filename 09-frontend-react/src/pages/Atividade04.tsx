import React, { useState } from 'react';
import styles from './Atividade04.module.css';

const Atividade04: React.FC = () => {
  // Estado inicial da bateria
  const [battery, setBattery] = useState<number>(50);
  
  // Constante de autonomia (km por 1% de bateria)
  const KM_PER_BATTERY = 1.2;

  /**
   * @brief Centraliza a lógica de alteração de bateria com limites de segurança.
   * Em React, a atualização do estado dispara automaticamente a re-renderização.
   */
  const handleBatteryChange = (amount: number) => {
    setBattery(prev => {
      const nextValue = prev + amount;
      // Limites de 0 a 100%
      return Math.min(Math.max(nextValue, 0), 100);
    });
  };

  // Cálculo derivado do estado
  const autonomy = (battery * KM_PER_BATTERY).toFixed(1);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Console de Operações - SkyCargo</h1>
        <p>Sistema de Gestão de Energia e Comandos Táticos</p>
      </header>

      <main className={styles.controlCenter}>
        <div className={styles.statusPanel}>
          <div className={styles.gaugeContainer}>
            <div 
              className={styles.gaugeFill} 
              style={{ 
                width: `${battery}%`,
                backgroundColor: battery > 20 ? '#39ff14' : '#ff0055' 
              }}
            ></div>
          </div>
          <div className={styles.metrics}>
            <span className={styles.batteryText}>{battery}% Bateria</span>
            <span className={styles.rangeText}>{autonomy} km disponíveis</span>
          </div>
        </div>

        <section className={styles.actionButtons}>
          <button 
            className={styles.btnCharge} 
            onClick={() => handleBatteryChange(10)}
            title="Recarregar 10% de energia"
          >
            RECARREGAR (+)
          </button>
          
          <button 
            className={styles.btnDrain} 
            onClick={() => handleBatteryChange(-15)}
            title="Gastar 15% de energia em voo"
          >
            INICIAR VOO (-)
          </button>
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota Técnica: Eventos e Funções</h4>
          <p>
            Diferente do Vanilla JS, no React não precisamos de uma função <code>atualizarInterface()</code> que manipule o DOM manualmente. 
            Ao disparar o evento <code>onClick</code>, alteramos o <strong>Estado (State)</strong>, e o React "reage" redesenhando apenas o que mudou com máxima eficiência.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade04;
