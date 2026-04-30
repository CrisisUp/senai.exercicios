/**
 * @file DroneCommander.tsx
 * @brief Painel de Controle de Telemetria Reativo com useState.
 * @author Engenheiro de Elite
 */

import React, { useState } from 'react';

const DroneCommander: React.FC = () => {
    // 1. Definição de Estados (Memória do Componente)
    const [altitude, setAltitude] = useState<number>(100);
    const [velocidade, setVelocidade] = useState<number>(50);
    const [isEmergencia, setIsEmergencia] = useState<boolean>(false);

    // 2. Handlers de Lógica (Mudança de Estado)
    const aumentarAltitude = () => {
        // Padrão de Elite: Sempre usar o valor anterior para cálculos
        setAltitude(prev => Math.min(prev + 10, 500)); 
    };

    const diminuirAltitude = () => {
        setAltitude(prev => Math.max(prev - 10, 0));
    };

    const toggleEmergencia = () => {
        setIsEmergencia(!isEmergencia);
        if (!isEmergencia) {
            setVelocidade(0); // Força parada imediata
        }
    };

    return (
        <section style={{
            background: isEmergencia ? '#400' : 'var(--bg-surface)',
            border: `2px solid ${isEmergencia ? 'var(--status-alert)' : 'var(--border-color)'}`,
            padding: '30px',
            borderRadius: 'var(--border-radius)',
            transition: 'all 0.4s ease'
        }}>
            <h2 style={{ color: 'var(--brand-accent)', marginBottom: '20px' }}>
                COMANDO TÁTICO: <span style={{ color: 'white' }}>NEXUS-01</span>
            </h2>

            <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '30px' }}>
                
                {/* Visualização de Estado */}
                <div style={{ fontLines: 'monospace' }}>
                    <p style={{ fontSize: '1.2rem' }}>📐 ALTITUDE: <strong style={{ color: 'var(--brand-accent)' }}>{altitude}m</strong></p>
                    <p style={{ fontSize: '1.2rem' }}>⚡ VELOCIDADE: <strong>{velocidade} km/h</strong></p>
                    <p style={{ marginTop: '10px' }}>SISTEMA: {isEmergencia ? '⚠️ MODO EMERGÊNCIA' : '✅ NORMAL'}</p>
                </div>

                {/* Controles Reativos */}
                <div style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
                    <button 
                        onClick={aumentarAltitude}
                        style={{ padding: '10px', cursor: 'pointer', background: 'var(--bg-card)', color: 'white', border: '1px solid var(--border-color)' }}
                    >
                        SUBIR +10m
                    </button>
                    <button 
                        onClick={diminuirAltitude}
                        style={{ padding: '10px', cursor: 'pointer', background: 'var(--bg-card)', color: 'white', border: '1px solid var(--border-color)' }}
                    >
                        DESCER -10m
                    </button>
                    <button 
                        onClick={toggleEmergencia}
                        style={{ 
                            padding: '12px', 
                            cursor: 'pointer', 
                            background: isEmergencia ? 'var(--status-success)' : 'var(--status-alert)', 
                            color: 'white', 
                            border: 'none',
                            fontWeight: 'bold',
                            marginTop: '10px'
                        }}
                    >
                        {isEmergencia ? 'REATIVAR SISTEMAS' : 'BOTÃO DE EMERGÊNCIA'}
                    </button>
                </div>

            </div>
        </section>
    );
};

export default DroneCommander;
