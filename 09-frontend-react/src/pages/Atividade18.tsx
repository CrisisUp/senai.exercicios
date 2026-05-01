/**
 * @file Atividade18.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState } from 'react';
import styles from './Atividade18.module.css';

type Status = 'IDLE' | 'CONNECTING' | 'SUCCESS' | 'ERROR';

/**
 * @page Atividade18
 * @brief Simulação de Assincronia e Promises com Skeleton Loading.
 */
const Atividade18: React.FC = () => {
  const [status, setStatus] = useState<Status>('IDLE');
  const [data, setData] = useState<string | null>(null);

  const simularHandshake = () => {
    setStatus('CONNECTING');
    setData(null);

    // Promise de Elite: Simula latência de rede
    const handshakePromise = new Promise<string>((resolve, reject) => {
      setTimeout(() => {
        const sucesso = Math.random() > 0.3; // 70% de chance de sucesso
        if (sucesso) {
          resolve("LINK SATELITAL ESTABELECIDO: NEYXUS-ALPHA-7");
        } else {
          reject("FALHA NA SINCRONIA: TIMEOUT DE RESPOSTA");
        }
      }, 3000); // 3 segundos de espera (Event Loop em ação)
    });

    handshakePromise
      .then((resultado) => {
        setData(resultado);
        setStatus('SUCCESS');
      })
      .catch((erro) => {
        setData(erro);
        setStatus('ERROR');
      });
  };

  const getStatusClass = () => {
    switch (status) {
      case 'CONNECTING': return styles.loading;
      case 'SUCCESS': return styles.success;
      case 'ERROR': return styles.error;
      default: return styles.idle;
    }
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Sincronia de Dubai</h1>
        <p>Dominando o Event Loop e Promises (Nível Arquiteto).</p>
      </header>

      <main>
        <div className={styles.card}>
          <div className={`${styles.statusBox} ${getStatusClass()}`}>
            Status do Satélite: {status}
          </div>

          <div className={styles.contentArea}>
            {status === 'CONNECTING' ? (
              <div className={styles.skeletonWrapper}>
                <div className={styles.skeletonLine}></div>
                <div className={styles.skeletonLine}></div>
                <div className={`${styles.skeletonLine} ${styles.skeletonLineShort}`}></div>
              </div>
            ) : (
              <div className={styles.dataDisplay}>
                {data || "Aguardando comando de inicialização..."}
              </div>
            )}
          </div>

          <button 
            className={styles.btnAction} 
            onClick={simularHandshake}
            disabled={status === 'CONNECTING'}
          >
            {status === 'CONNECTING' ? 'SINCRONIZANDO...' : 'INICIAR HANDSHAKE'}
          </button>
        </div>

        <footer className={styles.theoryBox}>
          <h4>Nota do Arquiteto: O Event Loop</h4>
          <p>
            No JavaScript, operações pesadas ou esperas (como rede) não travam a tela. 
            A Promise permite que o navegador continue rodando enquanto o satélite não responde.
            O <strong>Skeleton Loading</strong> é a técnica visual para avisar o operador que o sistema está trabalhando.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade18;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
