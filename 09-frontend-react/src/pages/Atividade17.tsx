import React, { useState, useEffect, useRef } from 'react';
import styles from './Atividade17.module.css';

/**
 * @page Atividade17
 * @brief Processamento de Dados: Regex, Date e Strings.
 */
const Atividade17: React.FC = () => {
  const [droneId, setDroneId] = useState('');
  const [logInput, setLogInput] = useState('');
  const [auditLogs, setAuditLogs] = useState<string[]>([]);
  const [currentTime, setCurrentTime] = useState('');
  const logViewRef = useRef<HTMLPreElement>(null);

  // Regex Padrão Industrial: 5 Letras, Traço, 3 Números
  const regexPadrao = /^[A-Z]{5}-\d{3}$/;

  /**
   * @brief Formata a data atual no padrão brasileiro industrial.
   */
  const obterDataFormatada = () => {
    const agora = new Date();
    const dia = String(agora.getDate()).padStart(2, '0');
    const mes = String(agora.getMonth() + 1).padStart(2, '0');
    const ano = agora.getFullYear();
    const hora = String(agora.getHours()).padStart(2, '0');
    const min = String(agora.getMinutes()).padStart(2, '0');
    const seg = String(agora.getSeconds()).padStart(2, '0');
    return `${dia}/${mes}/${ano} - ${hora}:${min}:${seg}`;
  };

  // Efeito para o Relógio em Tempo Real
  useEffect(() => {
    setCurrentTime(obterDataFormatada());
    const interval = setInterval(() => {
      setCurrentTime(obterDataFormatada());
    }, 1000);

    // Log Inicial
    setAuditLogs([`> SISTEMA INICIALIZADO ÀS ${obterDataFormatada()}`]);

    return () => clearInterval(interval);
  }, []);

  // Efeito para Scroll Automático do Log
  useEffect(() => {
    if (logViewRef.current) {
      logViewRef.current.scrollTop = logViewRef.current.scrollHeight;
    }
  }, [auditLogs]);

  const handleLogSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    const textoSaneado = logInput.trim().toUpperCase();

    if (textoSaneado !== "") {
      const timestamp = obterDataFormatada();
      setAuditLogs(prev => [...prev, `> [${timestamp}] ${textoSaneado}`]);
      setLogInput('');
    }
  };

  const getValidationFeedback = () => {
    if (droneId.trim() === "") return { text: "Aguardando entrada...", class: "" };
    if (regexPadrao.test(droneId.trim())) {
      return { text: "ID VALIDADO: PADRÃO INDUSTRIAL CORRETO.", class: styles.valid };
    }
    return { text: "ERRO: O PADRÃO DEVE SER 'ABCDE-123'.", class: styles.invalid };
  };

  const feedback = getValidationFeedback();

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Nexus Data Validation</h1>
        <p>Terminal de Integridade de Missão (Regex & Dates)</p>
      </header>

      <main className={styles.main}>
        {/* 1. Validador de Identidade (Regex) */}
        <section className={styles.card}>
          <h2>Registro de Unidade</h2>
          <div className={styles.inputGroup}>
            <label htmlFor="drone-id">ID DO DRONE (PADRÃO: AAAAA-000):</label>
            <input 
              type="text" 
              id="drone-id" 
              placeholder="Ex: ALPHA-707" 
              value={droneId}
              onChange={(e) => setDroneId(e.target.value)}
            />
            <div className={`${styles.feedback} ${feedback.class}`}>
              {feedback.text}
            </div>
          </div>
        </section>

        {/* 2. Console de Auditoria (Dates & Strings) */}
        <section className={styles.card}>
          <h2>Logs de Auditoria Forense</h2>
          <pre ref={logViewRef} className={styles.logView}>
            {auditLogs.join('\n')}
          </pre>
          <form onSubmit={handleLogSubmit} className={styles.form}>
            <input 
              type="text" 
              placeholder="Mensagem do log..." 
              value={logInput}
              onChange={(e) => setLogInput(e.target.value)}
            />
            <button type="submit" className={styles.btnAction}>AUDITAR</button>
          </form>
          <p style={{ marginTop: '1rem', fontSize: '0.8rem' }}>
            Hora Local do Sistema: <span className={styles.currentTime}>{currentTime}</span>
          </p>
        </section>

        <footer className={styles.theoryBox}>
          <h4>Resumo Teórico: O Triângulo da Integridade</h4>
          <p>
            1. <strong>RegExp (Regex)</strong>: Atua como o porteiro de dados. O padrão <code>/^[A-Z]{'{5}'}-\d{'{3}'}$/</code> garante que nenhum dado "sujo" entre no sistema.
            <br />
            2. <strong>Date Object</strong>: Fundamental para auditoria. Sem timestamps precisos, é impossível reconstruir falhas ou rotas.
            <br />
            3. <strong>String Methods</strong>: O uso de <code>.trim()</code> e <code>.toUpperCase()</code> garante a normalização, evitando que " drone" e "DRONE" sejam tratados como entidades diferentes.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade17;
