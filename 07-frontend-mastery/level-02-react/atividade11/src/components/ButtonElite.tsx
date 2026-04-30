/**
 * @file ButtonElite.tsx
 * @brief Botão Reutilizável com Tipagem de Callbacks.
 */

import React from 'react';

interface ButtonEliteProps {
    label: string;
    onClick: () => void; // Callback tipado
    variant?: 'primary' | 'danger'; // Propriedade opcional
    disabled?: boolean;
}

const ButtonElite: React.FC<ButtonEliteProps> = ({ label, onClick, variant = 'primary', disabled = false }) => {
    const style: React.CSSProperties = {
        padding: '10px 20px',
        borderRadius: 'var(--border-radius)',
        border: 'none',
        cursor: disabled ? 'not-allowed' : 'pointer',
        backgroundColor: variant === 'danger' ? 'var(--status-alert)' : 'var(--brand-primary)',
        color: 'white',
        fontWeight: 'bold',
        opacity: disabled ? 0.5 : 1,
        transition: 'all 0.2s ease'
    };

    return (
        <button 
            style={style} 
            onClick={onClick} 
            disabled={disabled}
            onMouseEnter={(e) => !disabled && (e.currentTarget.style.filter = 'brightness(1.2)')}
            onMouseLeave={(e) => !disabled && (e.currentTarget.style.filter = 'brightness(1)')}
        >
            {label.toUpperCase()}
        </button>
    );
};

export default ButtonElite;
