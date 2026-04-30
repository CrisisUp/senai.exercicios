/**
 * @file DroneCard.tsx
 * @brief Componente Molecular para representação de telemetria de drone.
 * @author Engenheiro de Elite
 */

import React from 'react';
import StatusBadge from './StatusBadge';

interface DroneCardProps {
    id: string;
    altitude: number;
    velocidade: number;
    status: 'OPERACIONAL' | 'EM ROTA' | 'ALERTA' | 'OFFLINE';
}

const DroneCard: React.FC<DroneCardProps> = ({ id, altitude, velocidade, status }) => {
    return (
        <article className="drone-card" style={{
            backgroundColor: 'var(--bg-surface)',
            border: '1px solid var(--border-color)',
            borderRadius: 'var(--border-radius)',
            padding: '20px',
            minWidth: '300px',
            display: 'flex',
            flexDirection: 'column',
            gap: '15px'
        }}>
            <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
                <h3 style={{ margin: 0, color: 'var(--brand-accent)' }}>{id}</h3>
                <StatusBadge status={status} />
            </div>

            <div style={{ fontSize: '0.9rem', color: 'var(--text-secondary)' }}>
                <p>Altitude: <strong style={{ color: 'var(--text-primary)' }}>{altitude}m</strong></p>
                <p>Velocidade: <strong style={{ color: 'var(--text-primary)' }}>{velocidade} km/h</strong></p>
            </div>

            <button style={{
                background: 'transparent',
                border: '1px solid var(--brand-primary)',
                color: 'var(--brand-primary)',
                padding: '8px',
                borderRadius: '4px',
                cursor: 'pointer',
                fontWeight: 'bold'
            }}>
                VER DETALHES
            </button>
        </article>
    );
};

export default DroneCard;
