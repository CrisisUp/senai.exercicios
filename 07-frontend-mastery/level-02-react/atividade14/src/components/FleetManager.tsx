/**
 * @file FleetManager.tsx
 * @brief Gerenciador de Frota Dinâmica com Reconciliação de Elite.
 * @author Engenheiro de Elite
 */

import React, { useState } from 'react';
import type { IDrone } from '../types/index';

const FleetManager: React.FC = () => {
    // 1. Estado da Frota (Lista Dinâmica)
    const [drones, setDrones] = useState<IDrone[]>([
        { id: 'ALPHA-01', modelo: 'Vulture v1', status: 'OPERACIONAL', carga_util: 85 },
        { id: 'BETA-02', modelo: 'Vulture v2', status: 'EM ROTA', carga_util: 92 }
    ]);

    // 2. Operação: Adicionar Drone (Decolagem)
    const decolarNovoDrone = () => {
        const novoId = `DRONE-${Math.floor(Math.random() * 1000)}`;
        const novoDrone: IDrone = {
            id: novoId,
            modelo: 'Phoenix Industrial',
            status: 'EM ROTA',
            carga_util: 100
        };
        
        // Padrão Imutável: Novo array com o item adicionado
        setDrones(prev => [...prev, novoDrone]);
        console.log(`\x1b[1;32m[LOG]\x1b[0m Drone ${novoId} entrou em operação.`);
    };

    // 3. Operação: Remover Drone (Pouso Forçado)
    const realizarPouso = (id: string) => {
        // Filtramos o array removendo o ID específico
        setDrones(prev => prev.filter(d => d.id !== id));
        console.log(`\x1b[1;31m[LOG]\x1b[0m Drone ${id} pousou e foi removido da frota ativa.`);
    };

    return (
        <section style={{ padding: '20px' }}>
            <header style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '30px' }}>
                <h2 style={{ color: 'var(--brand-accent)' }}>GERENCIAMENTO DE FROTA</h2>
                <button 
                    onClick={decolarNovoDrone}
                    style={{
                        padding: '10px 20px', background: 'var(--brand-primary)', 
                        color: 'white', border: 'none', borderRadius: '4px', cursor: 'pointer',
                        fontWeight: 'bold'
                    }}
                >
                    + DECOLAR NOVO DRONE
                </button>
            </header>

            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(250px, 1fr))', gap: '20px' }}>
                {/* 4. RENDERIZAÇÃO DE LISTA DE ELITE */}
                {drones.map((drone) => (
                    <article 
                        key={drone.id} // VITAL: Chave estável para reconciliação
                        style={{
                            background: 'var(--bg-surface)', border: '1px solid var(--border-color)',
                            padding: '15px', borderRadius: 'var(--border-radius)',
                            display: 'flex', flexDirection: 'column', gap: '10px'
                        }}
                    >
                        <div style={{ display: 'flex', justifyContent: 'space-between' }}>
                            <strong>{drone.id}</strong>
                            <span style={{ fontSize: '0.7rem', color: 'var(--text-muted)' }}>{drone.modelo}</span>
                        </div>
                        <p style={{ fontSize: '0.8rem' }}>Status: {drone.status}</p>
                        
                        <button 
                            onClick={() => realizarPouso(drone.id)}
                            style={{ 
                                marginTop: '10px', padding: '5px', background: 'transparent',
                                border: '1px solid var(--status-alert)', color: 'var(--status-alert)',
                                cursor: 'pointer', borderRadius: '4px'
                            }}
                        >
                            SOLICITAR POUSO
                        </button>
                    </article>
                ))}
            </div>

            {drones.length === 0 && (
                <p style={{ textAlign: 'center', marginTop: '50px', color: 'var(--text-muted)' }}>
                    Nenhum drone em operação no momento.
                </p>
            )}
        </section>
    );
};

export default FleetManager;
