/**
 * @file HistoricalVault.tsx
 * @brief Monitor de Logs Históricos usando useQuery (TanStack).
 * @author Engenheiro de Elite
 */

import React from 'react';
import { useQuery } from '@tanstack/react-query';

interface ILog {
    id: number;
    evento: string;
    unidade: string;
}

/**
 * @brief Função de Busca (Fetcher).
 * Em um cenário real, chamaria o backend Rust.
 */
const fetchLogs = async (): Promise<ILog[]> => {
    console.log("\x1b[1;34m[NETWORK]\x1b[0m Buscando dados do Nexus Vault...");
    
    // Simulação de latência de 1.5s
    await new Promise(r => setTimeout(r, 1500));

    return [
        { id: 101, evento: "Decolagem ALPHA-707", unidade: "BR-SP" },
        { id: 102, evento: "Carga Processada", unidade: "US-CA" },
        { id: 103, evento: "Checkpoint Integridade", unidade: "EU-DE" }
    ];
};

const HistoricalVault: React.FC = () => {
    // O useQuery gerencia TUDO: cache, estado de loading e erros.
    const { data, isLoading, error, isFetching } = useQuery({
        queryKey: ['nexus-logs'], // Chave única para o cache
        queryFn: fetchLogs,
    });

    if (isLoading) return <div style={{ color: 'var(--brand-accent)' }}>ESTABELECENDO TÚNEL COM VAULT...</div>;
    
    if (error) return <div style={{ color: 'var(--status-alert)' }}>FALHA CRÍTICA NA RECUPERAÇÃO DE DADOS.</div>;

    return (
        <section style={{ 
            background: 'var(--bg-surface)', padding: '25px', 
            borderRadius: '8px', border: '1px solid var(--border-color)' 
        }}>
            <header style={{ display: 'flex', justifyContent: 'space-between', marginBottom: '20px' }}>
                <h3 style={{ color: 'var(--brand-accent)' }}>HISTÓRICO DO NEXUS VAULT</h3>
                {isFetching && <small style={{ color: 'var(--status-warning)' }}>RE-SINCRONIZANDO...</small>}
            </header>

            <div style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
                {data?.map(log => (
                    <div key={log.id} style={{ 
                        background: 'var(--bg-card)', padding: '10px', 
                        borderRadius: '4px', borderLeft: '3px solid var(--brand-primary)' 
                    }}>
                        <p style={{ fontSize: '0.9rem' }}>{log.evento}</p>
                        <small style={{ color: 'var(--text-muted)' }}>Unidade: {log.unidade}</small>
                    </div>
                ))}
            </div>
            
            <p style={{ marginTop: '20px', fontSize: '0.7rem', color: 'var(--text-secondary)' }}>
                * Os dados acima estão cacheados. Se você fechar e abrir este componente, 
                eles aparecerão instantaneamente enquanto a atualização ocorre em background.
            </p>
        </section>
    );
};

export default HistoricalVault;
