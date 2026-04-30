import React, { useState } from 'react';
import styles from './Atividade05.module.css';

const Atividade05: React.FC = () => {
  // Estados para gerenciar o formulário e telemetria
  const [callsign, setCallsign] = useState<string>("SKY-RAPTOR");
  const [tempCallsign, setTempCallsign] = useState<string>("");
  const [battery, setBattery] = useState<number>(100);

  // Lógica Condicional (Requisito de Elite)
  const isCritical = battery < 20;
  
  const handleUpdateCallsign = (e: React.FormEvent) => {
    e.preventDefault();
    if (tempCallsign.trim()) {
      setCallsign(tempCallsign.toUpperCase());
      setTempCallsign("");
    }
  };

  return (
    <div className={`${styles.container} ${isCritical ? styles.perigo : styles.normal}`}>
      <header className={styles.header}>
        <h1>Nexus Control v5.0 - {callsign}</h1>
        <div className={styles.statusBadge}>
          {isCritical ? "⚠️ STATUS: ALERTA CRÍTICO" : "✅ STATUS: OPERAÇÃO NORMAL"}
        </div>
      </header>

      <main className={styles.dashboard}>
        {/* Seção de Configuração (Formulários) */}
        <section className={styles.configPanel}>
          <h2><span className={styles.icon}>⚙️</span> Configuração de Unidade</h2>
          <form onSubmit={handleUpdateCallsign} className={styles.form}>
            <div className={styles.inputGroup}>
              <label htmlFor="callsign-input">Novo Callsign:</label>
              <input 
                id="callsign-input"
                type="text" 
                placeholder="Ex: ALPHA-01"
                value={tempCallsign}
                onChange={(e) => setTempCallsign(e.target.value)}
              />
            </div>
            <button type="submit" className={styles.btnAction}>ATUALIZAR REGISTRO</button>
          </form>
        </section>

        {/* Seção de Telemetria (Flexbox) */}
        <section className={styles.telemetryPanel}>
          <h2><span className={styles.icon}>🔋</span> Gestão de Energia</h2>
          <div className={styles.energyControl}>
            <button onClick={() => setBattery(prev => Math.max(0, prev - 10))}>REDUZIR CARGA</button>
            <div className={styles.batteryValue}>{battery}%</div>
            <button onClick={() => setBattery(prev => Math.min(100, prev + 10))}>REABASTECER</button>
          </div>
          <div className={styles.progressBar}>
            <div className={styles.progressFill} style={{ width: `${battery}%` }}></div>
          </div>
        </section>
      </main>

      <footer className={styles.theoryBox}>
        <h3>Resumo Técnico: Inteligência & Layout</h3>
        <p>
          Este componente demonstra a fusão de <strong>Flexbox</strong> para alinhamento dinâmico e 
          <strong>Lógica Condicional JS</strong> integrada ao JSX. A interface "reage" ao estado <code>battery</code>: 
          ao atingir o limiar crítico, o React injeta dinamicamente classes de perigo, alterando a percepção visual do operador.
        </p>
      </footer>
    </div>
  );
};

export default Atividade05;
