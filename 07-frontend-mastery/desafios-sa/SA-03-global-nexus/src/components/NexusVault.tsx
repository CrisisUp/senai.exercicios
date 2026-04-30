/**
 * @file NexusVault.tsx
 * @brief Visualizador de Histórico com Cache Inteligente (TanStack Query).
 */

import React from 'react';
import { useQuery } from '@tanstack/react-query';
import type { INexusEvent } from '../types';

const fetchVaultLogs = async (): Promise<INexusEvent[]> => {
    // Simulação de chamada ao Backend Rust/SQL
    await new Promise(r => setTimeout(r, 1000));
    return [
        { id: '1', timestamp: '19:45:01', layer: 'HARDWARE', message: 'Sensor calibrado com sucesso.' },
        { id: '2', timestamp: '19:46:12', layer: 'SECURITY', message: 'Token de acesso rotacionado via KMS.' },
        { id: '3', timestamp: '19:48:30', layer: 'DATA', message: 'Checkpoint de integridade SQL validado.' }
    ];
};

const NexusVault: React.FC = () => {
    const { data, isLoading, isFetching } = useQuery({
        queryKey: ['vault-logs'],
        queryFn: fetchVaultLogs
    });

    if (isLoading) return <div style={{ color: 'var(--text-muted)' }}>ACESSANDO SQL VAULT...</div>;

    return (
        <div style={{ background: 'var(--bg-surface)', padding: '20px', borderRadius: '8px', border: '1px solid var(--border-color)' }}>
            <header style={{ display: 'flex', justifyContent: 'space-between', marginBottom: '15px' }}>
                <h3 style={{ fontSize: '0.9rem', color: 'var(--brand-accent)' }}>HISTÓRICO DE AUDITORIA</h3>
                {isFetching && <small style={{ color: 'var(--status-warning)' }}>REFRESHING...</small>}
            </header>
            
            <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
                {data?.map(log => (
                    <div key={log.id} style={{ fontSize: '0.8rem', fontLines: 'monospace', padding: '5px', borderLeft: '2px solid var(--brand-primary)' }}>
                        <span style={{ color: 'var(--text-muted)' }}>[{log.timestamp}]</span> 
                        <span style={{ fontWeight: 'bold', margin: '0 5px' }}>[{log.layer}]</span>
                        {log.message}
                    </div>
                ))}
            </div>
        </div>
    );
};

export default NexusVault;
