/**
 * @date 2026
 */
/**
 * @file StatusBadge.tsx
 * @brief Componente Atômico para exibição de status industrial.
 * @author Engenheiro de Elite
 */

import React from 'react';

// Tipagem das propriedades do componente (Rigor TypeScript)
interface StatusBadgeProps {
    status: 'OPERACIONAL' | 'EM ROTA' | 'ALERTA' | 'OFFLINE';
}

const StatusBadge: React.FC<StatusBadgeProps> = ({ status }) => {
    // Lógica de mapeamento de cores via Design System Tokens
    const getStatusColor = () => {
        switch (status) {
            case 'OPERACIONAL': return 'var(--status-success)';
            case 'ALERTA': return 'var(--status-alert)';
            case 'EM ROTA': return 'var(--brand-primary)';
            default: return 'var(--text-muted)';
        }
    };

    const style: React.CSSProperties = {
        backgroundColor: getStatusColor(),
        color: 'white',
        padding: '4px 12px',
        borderRadius: '20px',
        fontSize: '0.75rem',
        fontWeight: 'bold',
        display: 'inline-block'
    };

    return (
        <span style={style} className="status-badge">
            {status}
        </span>
    );
};

export default StatusBadge;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
