import React, { useState, useEffect } from 'react';
import styles from './Atividade29.module.css';

/**
 * @file Atividade29.tsx
 * @brief Sobrevivência Digital: Service Workers e Modo Offline no React.
 * @author Gemini CLI
 * @date 2026-04-29
 * 
 * @section MemoryMap
 * - Stack: Booleans (isOnline), strings de status, referências locais de handlers.
 * - Heap: Funções de efeito, listeners de evento, registro de Service Worker.
 */
const Atividade29: React.FC = () => {
  const [isOnline, setIsOnline] = useState(navigator.onLine);
  const [swStatus, setSwStatus] = useState('VERIFICANDO...');
  const [lastSync, setLastSync] = useState(new Date().toLocaleTimeString());

  useEffect(() => {
    // 1. Registro do Service Worker
    if ('serviceWorker' in navigator) {
      navigator.serviceWorker.register('/sw.js')
        .then((reg) => {
          setSwStatus('ATIVO (OFFLINE STORAGE: VALIDATED)');
          console.log('[SW] Registrado com sucesso:', reg.scope);
        })
        .catch((err) => {
          setSwStatus('FALHA NO REGISTRO');
          console.error('[SW] Erro no registro:', err);
        });
    } else {
      setSwStatus('NÃO SUPORTADO');
    }

    // 2. Monitoramento de Rede
    const handleOnline = () => {
      setIsOnline(true);
      setLastSync(new Date().toLocaleTimeString());
    };
    const handleOffline = () => setIsOnline(false);

    window.addEventListener('online', handleOnline);
    window.addEventListener('offline', handleOffline);

    return () => {
      window.removeEventListener('online', handleOnline);
      window.removeEventListener('offline', handleOffline);
    };
  }, []);

  return (
    <div className={`${styles.container} ${!isOnline ? styles.offlineMode : ''}`}>
      <header className={styles.header}>
        <h1>Sobrevivência Digital SkyCargo</h1>
        <p>Resiliência de Rede e Cache Local via Service Workers.</p>
      </header>

      <main>
        <div className={styles.statusPanel}>
          <div className={styles.statusItem}>
            <span>STATUS DE REDE:</span>
            <span className={isOnline ? styles.onlineText : styles.offlineText}>
              {isOnline ? '● ONLINE (SATÉLITE ATIVO)' : '○ OFFLINE (MODO SOBREVIVÊNCIA)'}
            </span>
          </div>
          <div className={styles.statusItem}>
            <span>SERVICE WORKER:</span>
            <span className={styles.swText}>{swStatus}</span>
          </div>
          <div className={styles.statusItem}>
            <span>ÚLTIMA SINCRONIA:</span>
            <span>{lastSync}</span>
          </div>
        </div>

        <section className={styles.dashboard}>
          <div className={styles.card}>
            <h3>DADOS CACHEADOS</h3>
            <p>Os dados abaixo estão disponíveis mesmo sem internet.</p>
            <div className={styles.mockData}>
              <div className={styles.dataRow}>
                <span>DRONE ALPHA-707:</span> <span>EM ROTA</span>
              </div>
              <div className={styles.dataRow}>
                <span>CARGA TÉRMICA:</span> <span>4.2°C (ESTÁVEL)</span>
              </div>
              <div className={styles.dataRow}>
                <span>COMBUSTÍVEL:</span> <span>88%</span>
              </div>
            </div>
          </div>

          <div className={styles.warningBox}>
            {!isOnline ? (
              <p className={styles.alertMsg}>
                ⚠️ AVISO: Conexão perdida. Interface desaturada para sinalizar operação via cache local.
              </p>
            ) : (
              <p className={styles.successMsg}>
                ✓ Conexão estável. Sincronizando dados com o Nexus Central em tempo real.
              </p>
            )}
          </div>
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: Arquitetura Offline-First</h4>
          <p>
            Em sistemas de missão crítica, a ausência de rede não deve significar a ausência de serviço.
            A <strong>Cache API</strong> em conjunto com <strong>Service Workers</strong> permite que o app seja 
            instalado no disco do usuário, servindo arquivos instantaneamente. 
            <br /><br />
            No React, usamos efeitos para detectar mudanças no <code>navigator.onLine</code>, 
            permitindo que a UI se adapte visualmente (como o filtro grayscale aplicado aqui) 
            para informar ao operador sobre o estado atual da conectividade.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade29;
