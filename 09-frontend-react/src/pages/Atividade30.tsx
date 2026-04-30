import React, { useState, useEffect, useRef, useCallback } from 'react';
import styles from './Atividade30.module.css';

/**
 * @file Atividade30.tsx
 * @brief O Link Bi-direcional: Mastering WebSockets API no React.
 * @author Gemini CLI
 * @date 2026-04-29
 * 
 * @section MemoryMap
 * - Stack: Strings de status e input, timestamps primitivos (Date.now).
 * - Heap: Instância WebSocket (socketRef), array de mensagens (state), callbacks memoizados (useCallback).
 */
const Atividade30: React.FC = () => {
  const [status, setStatus] = useState<'CONNECTING' | 'OPEN' | 'CLOSED'>('CLOSED');
  const [messages, setMessages] = useState<{ id: number; text: string; type: 'IN' | 'OUT'; time: string }[]>([]);
  const [inputMessage, setInputMessage] = useState('');
  const [latency, setLatency] = useState<number | null>(null);
  const socketRef = useRef<WebSocket | null>(null);
  const lastPingTime = useRef<number>(0);

  const addLog = (text: string, type: 'IN' | 'OUT') => {
    setMessages(prev => [
      ...prev.slice(-15), // Mantém apenas as últimas 15 mensagens para performance
      { id: Date.now(), text, type, time: new Date().toLocaleTimeString() }
    ]);
  };

  const connect = useCallback(() => {
    if (socketRef.current) socketRef.current.close();

    setStatus('CONNECTING');
    const ws = new WebSocket('wss://ws.postman-echo.com/raw');

    ws.onopen = () => {
      setStatus('OPEN');
      addLog('LINK ESTABELECIDO COM NEXUS SERVER', 'IN');
    };

    ws.onmessage = (event) => {
      const timeRecv = Date.now();
      if (lastPingTime.current > 0) {
        setLatency(timeRecv - lastPingTime.current);
        lastPingTime.current = 0;
      }
      addLog(event.data, 'IN');
    };

    ws.onclose = () => {
      setStatus('CLOSED');
      addLog('CONEXÃO ENCERRADA PELO HOST', 'IN');
    };

    ws.onerror = () => {
      addLog('ERRO CRÍTICO NA TRANSMISSÃO DE DADOS', 'IN');
    };

    socketRef.current = ws;
  }, []);

  const sendMessage = (e?: React.FormEvent) => {
    e?.preventDefault();
    if (socketRef.current?.readyState === WebSocket.OPEN && inputMessage.trim()) {
      lastPingTime.current = Date.now();
      socketRef.current.send(inputMessage);
      addLog(inputMessage, 'OUT');
      setInputMessage('');
    }
  };

  useEffect(() => {
    connect();
    return () => socketRef.current?.close();
  }, [connect]);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Link Bi-direcional SkyCargo</h1>
        <p>Comunicação de Baixa Latência via WebSockets (Full-Duplex).</p>
      </header>

      <main>
        <section className={styles.dashboard}>
          <div className={styles.connectionInfo}>
            <div className={styles.statusChip}>
              STATUS: 
              <span className={styles[status.toLowerCase()]}>
                {status} {status === 'OPEN' && <span className={styles.pulse}></span>}
              </span>
            </div>
            <div className={styles.latencyChip}>
              LATÊNCIA: <span>{latency !== null ? `${latency}ms` : '--'}</span>
            </div>
          </div>

          <div className={styles.streamConsole}>
            <div className={styles.consoleHeader}>NEXUS STREAM CONSOLE</div>
            <div className={styles.messageList}>
              {messages.length === 0 && <div className={styles.emptyMsg}>Aguardando fluxo de dados...</div>}
              {messages.map((msg) => (
                <div key={msg.id} className={`${styles.messageRow} ${msg.type === 'OUT' ? styles.msgOut : styles.msgIn}`}>
                  <span className={styles.msgTime}>[{msg.time}]</span>
                  <span className={styles.msgType}>{msg.type === 'OUT' ? '>>>' : '<<<'}</span>
                  <span className={styles.msgText}>{msg.text}</span>
                </div>
              ))}
            </div>
          </div>

          <form className={styles.commandLine} onSubmit={sendMessage}>
            <input 
              type="text" 
              placeholder="Digite comando tático..." 
              value={inputMessage}
              onChange={(e) => setInputMessage(e.target.value)}
              disabled={status !== 'OPEN'}
            />
            <button type="submit" disabled={status !== 'OPEN' || !inputMessage.trim()}>
              ENVIAR
            </button>
            <button type="button" onClick={connect} className={styles.btnReconnect}>
              RESET LINK
            </button>
          </form>
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: O Poder do TCP Persistente</h4>
          <p>
            Diferente do HTTP, onde cada requisição abre e fecha uma conexão (overhead), 
            o <strong>WebSocket</strong> mantém um canal aberto e bi-direcional. 
            Isso é vital para telemetria de drones em tempo real, onde milissegundos importam.
            <br /><br />
            No React, usamos <code>useRef</code> para persistir a instância do socket entre renderizações 
            sem disparar re-renderizações desnecessárias, e <code>useEffect</code> para gerenciar 
            o ciclo de vida da conexão (abrir no mount, fechar no unmount).
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade30;
