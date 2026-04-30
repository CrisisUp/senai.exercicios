import React, { useState, useEffect, useRef } from 'react';
import styles from './Atividade10.module.css';

interface LogEntry {
  timestamp: string;
  message: string;
}

const Atividade10: React.FC = () => {
  // Estados Persistentes (HD Virtual)
  const [operator, setOperator] = useState<string>(() => {
    return localStorage.getItem('nexus_operator') || '';
  });
  
  const [logs, setLogs] = useState<LogEntry[]>(() => {
    const savedLogs = localStorage.getItem('nexus_mission_logs');
    return savedLogs ? JSON.parse(savedLogs) : [];
  });

  const [inputLog, setInputLog] = useState<string>('');
  const logEndRef = useRef<HTMLDivElement>(null);

  /**
   * @section Persistência (Requisito de Elite)
   * Sincroniza estados com LocalStorage sempre que mudam.
   */
  useEffect(() => {
    localStorage.setItem('nexus_operator', operator);
  }, [operator]);

  useEffect(() => {
    localStorage.setItem('nexus_mission_logs', JSON.stringify(logs));
    // Auto-scroll para o fim dos logs
    logEndRef.current?.scrollIntoView({ behavior: 'smooth' });
  }, [logs]);

  const handleAddLog = (e: React.FormEvent) => {
    e.preventDefault();
    if (!inputLog.trim()) return;

    const newEntry: LogEntry = {
      timestamp: new Date().toLocaleTimeString(),
      message: inputLog
    };

    setLogs(prev => [...prev, newEntry]);
    setInputLog('');
  };

  const clearHistory = () => {
    if (confirm("Deseja apagar TODO o histórico de missão?")) {
      setLogs([]);
      localStorage.removeItem('nexus_mission_logs');
    }
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Terminal de Persistência - Nexus v10</h1>
        <p>Garantindo a integridade dos dados históricos de missão.</p>
      </header>

      <main className={styles.main}>
        <section className={styles.setupPanel}>
          <h2><span className={styles.icon}>🆔</span> Identificação do Operador</h2>
          <div className={styles.inputGroup}>
            <label>NOME DE GUERRA:</label>
            <input 
              type="text" 
              placeholder="Digite seu nome..." 
              value={operator}
              onChange={(e) => setOperator(e.target.value.toUpperCase())}
            />
          </div>
          <p className={styles.hint}>Este nome será preservado mesmo se você fechar o navegador.</p>
        </section>

        <section className={styles.logPanel}>
          <header className={styles.logHeader}>
            <h2><span className={styles.icon}>📜</span> Registro de Auditoria (JSON)</h2>
            <button onClick={clearHistory} className={styles.btnClear}>LIMPAR HD</button>
          </header>

          <div className={styles.logViewport}>
            {logs.length === 0 ? (
              <p className={styles.emptyMsg}>Aguardando primeiro registro de missão...</p>
            ) : (
              <ul className={styles.logList}>
                {logs.map((log, index) => (
                  <li key={index}>
                    <span className={styles.timestamp}>[{log.timestamp}]</span>
                    <span className={styles.operatorTag}>{operator || 'ANON'}:</span>
                    <span className={styles.msg}>{log.message}</span>
                  </li>
                ))}
                <div ref={logEndRef} />
              </ul>
            )}
          </div>

          <form onSubmit={handleAddLog} className={styles.logForm}>
            <input 
              type="text" 
              placeholder="Digite uma observação de campo..." 
              value={inputLog}
              onChange={(e) => setInputLog(e.target.value)}
            />
            <button type="submit">GRAVAR</button>
          </form>
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota Técnica: Persistência & JSON</h4>
          <p>
            O React gerencia a interface em memória RAM (volátil). Para sobreviver a reloads, utilizamos o 
            <code>localStorage</code>. Os dados complexos (arrays) são serializados com <code>JSON.stringify()</code> 
            antes do salvamento e restaurados com <code>JSON.parse()</code> na inicialização do componente.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade10;
