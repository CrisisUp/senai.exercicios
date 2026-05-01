/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file DroneMonitor.tsx
 * @brief Monitor de Telemetria com Injeção de Objetos e Callbacks.
 */

import React from 'react';
import type { IDrone } from '../types/index';
import ButtonElite from './ButtonElite';

interface DroneMonitorProps {
    drone: IDrone; // Objeto de domínio injetado
    onCommand: (droneId: string, action: string) => void; // Callback tipado
}

const DroneMonitor: React.FC<DroneMonitorProps> = ({ drone, onCommand }) => {
    return (
        <article className="module-card" style={{
            background: 'var(--bg-surface)',
            border: '1px solid var(--border-color)',
            padding: '25px',
            borderRadius: 'var(--border-radius)',
            display: 'flex',
            flexDirection: 'column',
            gap: '10px'
        }}>
            <header style={{ display: 'flex', justifyContent: 'space-between', borderBottom: '1px solid var(--border-color)', paddingBottom: '10px' }}>
                <h3 style={{ color: 'var(--brand-accent)' }}>{drone.id}</h3>
                <small style={{ color: 'var(--text-muted)' }}>{drone.modelo}</small>
            </header>

            <div style={{ padding: '10px 0' }}>
                <p>🛰️ STATUS: <strong>{drone.status}</strong></p>
                <p>📏 ALTITUDE: {drone.altitude}m</p>
                <p>⚡ VELOCIDADE: {drone.velocidade} km/h</p>
            </div>

            <footer style={{ display: 'flex', gap: '10px', marginTop: '10px' }}>
                <ButtonElite 
                    label="Alinhar" 
                    onClick={() => onCommand(drone.id, "ALINHAMENTO")} 
                />
                <ButtonElite 
                    label="Abortar" 
                    variant="danger" 
                    onClick={() => onCommand(drone.id, "ABORTAR_MISSAO")} 
                />
            </footer>
        </article>
    );
};

export default DroneMonitor;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
