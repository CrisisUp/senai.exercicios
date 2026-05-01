/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file DroneMonitor.tsx
 * @brief Componente de visualização de telemetria individual.
 */

import React from 'react';
import type { IDrone } from '../types';
import { useMission } from '../contexts/MissionContext';

const DroneMonitor: React.FC<{ drone: IDrone }> = React.memo(({ drone }) => {
    const { sendCommand } = useMission();

    return (
        <article style={{
            background: 'var(--bg-card)',
            border: `1px solid ${drone.status === 'ALERTA' ? 'var(--status-alert)' : 'var(--border-color)'}`,
            padding: '15px',
            borderRadius: 'var(--border-radius)',
            display: 'flex',
            flexDirection: 'column',
            gap: '10px'
        }}>
            <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
                <h4 style={{ color: 'var(--brand-accent)' }}>{drone.id}</h4>
                <span style={{ fontSize: '0.7rem', padding: '2px 8px', borderRadius: '10px', background: 'var(--bg-surface)' }}>
                    {drone.status}
                </span>
            </div>
            
            <div style={{ fontSize: '0.8rem', color: 'var(--text-secondary)' }}>
                <p>Altitude: <strong>{drone.altitude}m</strong></p>
                <p>Velocity: <strong>{drone.velocidade}km/h</strong></p>
            </div>

            <button 
                onClick={() => sendCommand(drone.id, 'ALIGN')}
                style={{ cursor: 'pointer', background: 'var(--brand-primary)', color: 'white', border: 'none', padding: '5px', borderRadius: '4px' }}
            >
                RE-ALIGN
            </button>
        </article>
    );
});

export default DroneMonitor;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
