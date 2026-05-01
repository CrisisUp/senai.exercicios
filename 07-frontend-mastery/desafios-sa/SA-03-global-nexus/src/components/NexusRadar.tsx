/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file NexusRadar.tsx
 * @brief Radar Tático de Tempo Real (Simulação C++ Signals).
 */

import React from 'react';
import { useNexus } from '../contexts/NexusContext';

const NexusRadar: React.FC = () => {
    const { fleet } = useNexus();

    return (
        <section style={{ 
            background: 'var(--bg-page)', 
            border: '2px solid var(--brand-primary)', 
            borderRadius: '12px',
            height: '400px',
            position: 'relative',
            overflow: 'hidden',
            display: 'flex',
            justifyContent: 'center',
            alignItems: 'center'
        }}>
            {/* Linhas de Grade de Radar */}
            <div style={{ position: 'absolute', width: '100%', height: '1px', background: 'rgba(0,122,255,0.1)' }}></div>
            <div style={{ position: 'absolute', height: '100%', width: '1px', background: 'rgba(0,122,255,0.1)' }}></div>
            
            {/* Renderização da Frota Viva */}
            {fleet.map(drone => (
                <div 
                    key={drone.id}
                    style={{
                        position: 'absolute',
                        left: `${(drone.longitude + 46.7) * 1000}px`,
                        top: `${(drone.latitude + 23.6) * 1000}px`,
                        transition: 'all 2s linear',
                        display: 'flex',
                        flexDirection: 'column',
                        alignItems: 'center'
                    }}
                >
                    <div style={{ 
                        width: '12px', height: '12px', background: 'var(--brand-accent)', 
                        borderRadius: '50%', boxShadow: '0 0 10px var(--brand-accent)' 
                    }}></div>
                    <span style={{ fontSize: '0.6rem', marginTop: '5px', whiteSpace: 'nowrap', color: 'white' }}>
                        {drone.id} ({drone.altitude.toFixed(0)}m)
                    </span>
                </div>
            ))}

            <p style={{ position: 'absolute', bottom: '10px', right: '10px', fontSize: '0.7rem', color: 'var(--text-muted)' }}>
                SINAL DE ALTA FREQUÊNCIA (C++ CORE)
            </p>
        </section>
    );
};

export default NexusRadar;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
