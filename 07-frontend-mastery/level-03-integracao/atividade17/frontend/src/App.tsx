/**
 * @date 2026
 */
/**
 * @file App.tsx
 * @brief Orquestrador Full-Stack: Consumo de API Rust com CORS.
 * @author Engenheiro de Elite
 */

import React, { useState, useEffect } from 'react';
import './styles/theme.css';

// 1. Contrato de Dados (Deve espelhar o Backend Rust)
interface ITelemetria {
  id: string;
  modelo: string;
  status: string;
  altitude: number;
  timestamp: string;
}

function App() {
  const [dados, setDados] = useState<ITelemetria[]>([]);
  const [carregando, setCarregando] = useState<boolean>(false);
  const [erro, setErro] = useState<string | null>(null);

  /**
   * @brief Função de Fetch de Elite.
   * Conecta o React (5173) ao Rust (8080).
   */
  const buscarTelemetria = async () => {
    setCarregando(true);
    setErro(null);
    const start = performance.now();

    try {
      // Chamada para o endpoint real do servidor Axum
      const response = await fetch('http://localhost:8080/api/telemetria');
      
      if (!response.ok) {
        throw new Error(`HTTP Error: ${response.status}`);
      }

      const json = await response.json();
      setDados(json);

      const rtt = (performance.now() - start).toFixed(2);
      console.log(`\x1b[1;32m[NETWORK]\x1b[0m RTT: ${rtt}ms`);
      
    } catch (e) {
      const msg = e instanceof Error ? e.message : 'Falha na conexão com Nexus API';
      setErro(msg);
      console.error(`\x1b[1;31m[ERROR]\x1b[0m ${msg}`);
    } finally {
      setCarregando(false);
    }
  };

  // Busca inicial ao montar o componente
  useEffect(() => {
    buscarTelemetria();
  }, []);

  return (
    <div className="nexus-app" style={{ padding: '40px', minHeight: '100vh' }}>
      <header style={{ marginBottom: '30px', borderBottom: '1px solid var(--border-color)', paddingBottom: '20px' }}>
        <h1>SKYCARGO <span style={{ fontWeight: 300 }}>FULL-STACK LINK</span></h1>
        <p style={{ color: 'var(--text-secondary)' }}>Status: <span style={{ color: erro ? 'var(--status-alert)' : 'var(--status-success)' }}>
          {erro ? 'API OFFLINE' : 'CONNECTED TO RUST'}
        </span></p>
      </header>

      <main>
        <button 
          onClick={buscarTelemetria}
          disabled={carregando}
          style={{ 
            padding: '10px 20px', background: 'var(--brand-primary)', color: 'white', 
            border: 'none', borderRadius: '4px', cursor: 'pointer', marginBottom: '30px'
          }}
        >
          {carregando ? 'SINCRONIZANDO...' : 'RECARREGAR DADOS REAIS'}
        </button>

        {erro && (
          <div style={{ color: 'var(--status-alert)', background: 'rgba(248, 81, 73, 0.1)', padding: '20px', borderRadius: '8px' }}>
            <strong>ERRO DE REDE:</strong> {erro}
            <p style={{ fontSize: '0.8rem', marginTop: '10px' }}>Verifique se o servidor Rust está rodando em localhost:8080 e se o CORS está configurado.</p>
          </div>
        )}

        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(300px, 1fr))', gap: '20px' }}>
          {dados.map(drone => (
            <article key={drone.id} style={{ background: 'var(--bg-surface)', padding: '20px', borderRadius: '8px', border: '1px solid var(--border-color)' }}>
              <h3 style={{ color: 'var(--brand-accent)' }}>{drone.id}</h3>
              <p style={{ fontSize: '0.8rem', color: 'var(--text-muted)' }}>Modelo: {drone.modelo}</p>
              <hr style={{ margin: '15px 0', borderColor: 'var(--border-color)' }} />
              <p>Altitude: <strong>{drone.altitude}m</strong></p>
              <p>Status: <span style={{ color: drone.status === 'ALERTA' ? 'var(--status-alert)' : 'var(--status-success)' }}>{drone.status}</span></p>
            </article>
          ))}
        </div>
      </main>

      <footer style={{ marginTop: '80px', textAlign: 'center', color: 'var(--text-muted)', fontSize: '0.7rem' }}>
        &copy; 2026 LogiSpeed Global. REST/CORS Protocol: VALIDATED.
      </footer>
    </div>
  );
}

export default App;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
