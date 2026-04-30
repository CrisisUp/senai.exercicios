import React, { useState, useEffect } from 'react';
import styles from './Atividade28.module.css';

type AlertLevel = 'INFO' | 'WARNING' | 'CRITICAL';

/**
 * @page Atividade28
 * @brief Alertas Externos: Mastering Notification & Vibration API no React.
 */
const Atividade28: React.FC = () => {
  const [permission, setPermission] = useState<NotificationPermission>(Notification.permission);
  const [lastLog, setLastLog] = useState('SISTEMA DE MONITORAMENTO DE ALERTAS PRONTO.');
  const [isShaking, setIsShaking] = useState(false);

  const solicitarPermissao = async () => {
    if (!("Notification" in window)) {
      alert("ERRO: Este navegador não suporta notificações de desktop.");
      return;
    }

    const result = await Notification.requestPermission();
    setPermission(result);
  };

  const dispararAlerta = (nivel: AlertLevel) => {
    switch (nivel) {
      case 'INFO':
        setLastLog("EVENTO DE ROTINA: Checkout realizado com sucesso.");
        break;

      case 'WARNING':
        setLastLog("AVISO: Turbulência detectada no Setor de Carga 4.");
        // VIBRAÇÃO API (200ms)
        if (navigator.vibrate) navigator.vibrate(200);
        break;

      case 'CRITICAL':
        setLastLog("🚨 EMERGÊNCIA: ROTA DE COLISÃO IMINENTE!");
        
        // 1. Feedback Visual (Shake)
        setIsShaking(true);
        setTimeout(() => setIsShaking(false), 1000);

        // 2. Feedback Tátil (Padrão SOS: 100ms vibra, 100ms pausa, 100ms vibra, 100ms pausa, 300ms vibra)
        if (navigator.vibrate) navigator.vibrate([100, 100, 100, 100, 300]);

        // 3. Notificação OS
        if (permission === 'granted') {
          new Notification("🚨 NEXUS CRITICAL ALERT", {
            body: "Drone ALPHA-707 em rota de colisão. Ação imediata exigida!",
            icon: "https://placehold.co/100x100/ef4444/ffffff?text=X",
            tag: "collision-alert"
          });
        } else {
          alert("🚨 ALERTA CRÍTICO: ROTA DE COLISÃO!");
        }
        break;
    }
  };

  useEffect(() => {
    // Atualiza o estado da permissão caso mude externamente (improvável mas boa prática)
    setPermission(Notification.permission);
  }, []);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Alertas Externos SkyCargo</h1>
        <p>Notificações Nativas e Feedback Háptico (Notification & Vibration API).</p>
      </header>

      <main>
        <section className={`${styles.card} ${isShaking ? styles.shake : ''}`}>
          <div className={styles.statusInfo}>
            PERMISSÃO DE NOTIFICAÇÃO: 
            <span style={{ 
              color: permission === 'granted' ? '#10b981' : (permission === 'denied' ? '#ef4444' : '#fbbf24'),
              marginLeft: '0.5rem',
              fontWeight: 'bold'
            }}>
              {permission.toUpperCase()}
            </span>
          </div>

          {permission !== 'granted' && (
            <button className={styles.btnRequest} onClick={solicitarPermissao}>
              SOLICITAR AUTORIZAÇÃO DE SEGURANÇA
            </button>
          )}

          <div className={styles.alertsGrid}>
            <div className={styles.alertTrigger} onClick={() => dispararAlerta('INFO')}>
              <h3>ROUTINE</h3>
              <p>Check-out industrial padrão.</p>
            </div>
            
            <div className={`${styles.alertTrigger} ${styles.warning}`} onClick={() => dispararAlerta('WARNING')}>
              <h3>WARNING</h3>
              <p>Feedback tátil via Vibração.</p>
            </div>

            <div className={`${styles.alertTrigger} ${styles.critical}`} onClick={() => dispararAlerta('CRITICAL')}>
              <h3>CRITICAL</h3>
              <p>Alerta OS + Shake + SOS Vibrate.</p>
            </div>
          </div>
        </section>

        <div className={styles.logArea}>
          {lastLog}
        </div>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: Canais de Atenção</h4>
          <p>
            Em sistemas de missão crítica, a interface deve transcender a aba do navegador. 
            A <strong>Notification API</strong> garante que o operador seja alertado mesmo se estiver em outra tarefa no Desktop.
            <br /><br />
            Para dispositivos móveis, a <strong>Vibration API</strong> fornece o canal háptico, permitindo que o alerta seja "sentido" fisicamente. 
            No React, gerenciamos esses disparos através de eventos, garantindo que o feedback visual (Shake) esteja em sincronia com o feedback de hardware.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade28;
