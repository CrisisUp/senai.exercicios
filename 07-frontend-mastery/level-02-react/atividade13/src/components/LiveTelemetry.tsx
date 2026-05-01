/**
 * @date 2026
 */
/**
 * @file LiveTelemetry.tsx
 * @brief Monitor de Sincronização Automática com useEffect.
 * @author Engenheiro de Elite
 */

import React, { useState, useEffect } from 'react';

const LiveTelemetry: React.FC = () => {
    // 1. Estados Locais
    const [segundosMissao, setSegundosMissao] = useState<number>(0);
    const [lastSync, setLastSync] = useState<string>('NENHUMA');
    const [radioActive, setRadioActive] = useState<boolean>(true);

    // 2. Efeito de Sincronização (O Maestro)
    useEffect(() => {
        if (!radioActive) return;

        console.log("\x1b[1;32m[RADIO]\x1b[0m Estabelecendo conexão com satélite...");

        // A. Timer de Missão (Atualiza a cada 1s)
        const missionTimer = setInterval(() => {
            setSegundosMissao(prev => prev + 1);
        }, 1000);

        // B. Polling de Dados (Simula busca no Vault a cada 3s)
        const vaultSync = setInterval(() => {
            const now = new Date().toLocaleTimeString();
            setLastSync(now);
            console.log(`\x1b[1;34m[SQL]\x1b[0m Dados do Vault sincronizados às ${now}`);
        }, 3000);

        /**
         * @section CleanupFunction
         * Vital para a engenharia de elite: este código roda quando o componente 'morre'.
         * Se não fizermos o clearInterval, os timers continuariam rodando para sempre!
         */
        return () => {
            console.log("\x1b[1;31m[RADIO]\x1b[0m Desligando rádio e liberando recursos.");
            clearInterval(missionTimer);
            clearInterval(vaultSync);
        };

    }, [radioActive]); // O efeito reinicia apenas se o botão de rádio mudar

    return (
        <section style={{
            background: 'var(--bg-surface)',
            border: '1px solid var(--border-color)',
            padding: '30px',
            borderRadius: 'var(--border-radius)',
            boxShadow: 'var(--shadow-elite)'
        }}>
            <header style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '20px' }}>
                <h2 style={{ color: 'var(--brand-accent)' }}>TELEMETRIA AO VIVO</h2>
                <div style={{ display: 'flex', alignItems: 'center', gap: '10px' }}>
                    <div style={{ 
                        width: '12px', height: '12px', borderRadius: '50%', 
                        background: radioActive ? 'var(--status-success)' : 'var(--text-muted)',
                        boxShadow: radioActive ? '0 0 10px var(--status-success)' : 'none'
                    }}></div>
                    <span style={{ fontSize: '0.8rem' }}>{radioActive ? 'RADIO ACTIVE' : 'RADIO SILENCE'}</span>
                </div>
            </header>

            <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '20px', textAlign: 'center' }}>
                <div style={{ background: 'var(--bg-card)', padding: '20px', borderRadius: 'var(--border-radius)' }}>
                    <p style={{ color: 'var(--text-secondary)', fontSize: '0.8rem' }}>DURAÇÃO DA MISSÃO</p>
                    <p style={{ fontSize: '2rem', fontWeight: 'bold' }}>{segundosMissao}s</p>
                </div>
                <div style={{ background: 'var(--bg-card)', padding: '20px', borderRadius: 'var(--border-radius)' }}>
                    <p style={{ color: 'var(--text-secondary)', fontSize: '0.8rem' }}>ÚLTIMO SYNC VAULT</p>
                    <p style={{ fontSize: '1.5rem', fontWeight: 'bold' }}>{lastSync}</p>
                </div>
            </div>

            <button 
                onClick={() => setRadioActive(!radioActive)}
                style={{
                    width: '100%', marginTop: '20px', padding: '12px',
                    background: radioActive ? 'var(--status-alert)' : 'var(--brand-primary)',
                    color: 'white', border: 'none', borderRadius: 'var(--border-radius)',
                    cursor: 'pointer', fontWeight: 'bold'
                }}
            >
                {radioActive ? 'SUSPENDER TRANSMISSÃO' : 'REATIVAR RÁDIO'}
            </button>
        </section>
    );
};

export default LiveTelemetry;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
