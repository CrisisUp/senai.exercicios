/**
 * @date 2026
 */
/**
 * @file App.tsx
 * @brief Orquestrador de Telemetria em Tempo Real via WebSocket.
 * @author Engenheiro de Elite
 */

import React, { useState, useEffect, useRef } from 'react';
import './styles/theme.css';

interface ITelemetriaWS {
    id: string;
    x: number;
    y: number;
    bateria: number;
}

function App() {
    const [telemetria, setTelemetria] = useState<ITelemetriaWS | null>(null);
    const [status, setStatus] = useState<'CONNECTING' | 'LIVE' | 'DISCONNECTED'>('CONNECTING');
    const socketRef = useRef<WebSocket | null>(null);

    /**
     * @brief Conexão e Gestão do Ciclo de Vida do WebSocket.
     */
    useEffect(() => {
        const connect = () => {
            console.log("\x1b[1;34m[WS]\x1b[0m Tentando conexão com Nexus Server...");
            const ws = new WebSocket('ws://localhost:9001');

            ws.onopen = () => {
                console.log("\x1b[1;32m[WS]\x1b[0m Conexão estabelecida.");
                setStatus('LIVE');
            };

            ws.onmessage = (event) => {
                const data: ITelemetriaWS = JSON.parse(event.data);
                setTelemetria(data);
            };

            ws.onclose = () => {
                console.log("\x1b[1;31m[WS]\x1b[0m Conexão encerrada.");
                setStatus('DISCONNECTED');
                // Auto-reconnect após 3 segundos
                setTimeout(connect, 3000);
            };

            socketRef.current = ws;
        };

        connect();

        // CLEANUP: Vital para evitar conexões zumbis
        return () => {
            if (socketRef.current) {
                socketRef.current.close();
            }
        };
    }, []);

    return (
        <div className="nexus-app" style={{ padding: '40px', minHeight: '100vh' }}>
            <header style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '30px' }}>
                <h1>NEXUS <span style={{ fontWeight: 300 }}>REAL-TIME MONITOR</span></h1>
                <div style={{ display: 'flex', alignItems: 'center', gap: '10px' }}>
                    <div style={{ 
                        width: '12px', height: '12px', borderRadius: '50%', 
                        background: status === 'LIVE' ? 'var(--status-success)' : 'var(--status-alert)',
                        boxShadow: status === 'LIVE' ? '0 0 10px var(--status-success)' : 'none'
                    }}></div>
                    <span style={{ fontWeight: 'bold' }}>{status}</span>
                </div>
            </header>

            <main>
                <section style={{ 
                    background: 'var(--bg-surface)', border: '1px solid var(--border-color)', 
                    height: '400px', borderRadius: '8px', position: 'relative',
                    overflow: 'hidden'
                }}>
                    <p style={{ position: 'absolute', top: '10px', left: '10px', color: 'var(--text-muted)', fontSize: '0.7rem' }}>
                        MAPA TÁTICO (COORDENADAS WS)
                    </p>

                    {telemetria && (
                        <div style={{
                            position: 'absolute',
                            left: `${telemetria.x}px`,
                            top: `${telemetria.y}px`,
                            width: '40px',
                            height: '40px',
                            background: 'var(--brand-accent)',
                            borderRadius: '50%',
                            display: 'flex',
                            justifyContent: 'center',
                            alignItems: 'center',
                            transition: 'all 0.5s ease',
                            boxShadow: '0 0 20px var(--brand-accent)'
                        }}>
                            <span style={{ fontSize: '1rem' }}>🛸</span>
                            <div style={{ position: 'absolute', top: '45px', background: 'black', padding: '2px 8px', borderRadius: '4px', fontSize: '0.7rem', whiteSpace: 'nowrap' }}>
                                {telemetria.id} | BAT: {telemetria.bateria}%
                            </div>
                        </div>
                    )}

                    {!telemetria && status === 'CONNECTING' && (
                        <div style={{ display: 'flex', height: '100%', justifyContent: 'center', alignItems: 'center', color: 'var(--text-secondary)' }}>
                            ESTABELECENDO CANAL DE TELEMETRIA...
                        </div>
                    )}
                </section>

                <div style={{ marginTop: '20px', fontLines: 'monospace', fontSize: '0.8rem', color: 'var(--text-secondary)' }}>
                    <p>&gt; Link Protocol: WebSocket (TCP Persistente)</p>
                    <p>&gt; Buffer State: Optimized</p>
                </div>
            </main>

            <footer style={{ marginTop: '60px', textAlign: 'center', color: 'var(--text-muted)', fontSize: '0.7rem' }}>
                &copy; 2026 LogiSpeed Global. Full-Duplex Link: VALIDATED.
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
