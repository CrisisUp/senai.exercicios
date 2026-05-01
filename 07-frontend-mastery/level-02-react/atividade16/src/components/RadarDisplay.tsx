/**
 * @date 2026
 */
/**
 * @file RadarDisplay.tsx
 * @brief Componente Otimizado via React.memo.
 * @author Engenheiro de Elite
 */

import React from 'react';

interface RadarProps {
    droneId: string;
    onReset: () => void;
}

// React.memo impede que o Radar seja redesenhado se as props forem idênticas
const RadarDisplay: React.FC<RadarProps> = React.memo(({ droneId, onReset }) => {
    console.log(`\x1b[1;32m[RENDER]\x1b[0m RadarDisplay redesenhado para: ${droneId}`);

    return (
        <div style={{
            padding: '20px',
            background: 'var(--bg-card)',
            border: '2px solid var(--brand-accent)',
            borderRadius: '50%',
            width: '200px',
            height: '200px',
            display: 'flex',
            flexDirection: 'column',
            justifyContent: 'center',
            alignItems: 'center',
            textAlign: 'center',
            margin: '20px auto'
        }}>
            <small style={{ color: 'var(--text-muted)' }}>LOCKED ON</small>
            <h3 style={{ margin: '10px 0' }}>{droneId}</h3>
            <button 
                onClick={onReset}
                style={{ fontSize: '0.6rem', cursor: 'pointer', background: 'transparent', color: 'var(--brand-accent)', border: '1px solid var(--brand-accent)', padding: '4px' }}
            >
                RESET SCAN
            </button>
        </div>
    );
});

export default RadarDisplay;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
