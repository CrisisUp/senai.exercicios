/**
 * @date 2026
 */
/**
 * @file ThemeSwitcher.tsx
 * @brief Consumidor Distante do Estado Global.
 * @author Engenheiro de Elite
 */

import React from 'react';
import { useTheme } from '../contexts/ThemeContext';

const ThemeSwitcher: React.FC = () => {
    // Consumindo dados globais via Custom Hook
    const { isDarkMode, toggleTheme } = useTheme();

    return (
        <div style={{
            padding: '15px',
            background: 'var(--bg-surface)',
            border: '1px solid var(--border-color)',
            borderRadius: 'var(--border-radius)',
            display: 'flex',
            justifyContent: 'space-between',
            alignItems: 'center',
            marginBottom: '30px'
        }}>
            <span>AMBIENTE ATUAL: <strong>{isDarkMode ? 'OPERACIONAL (DARK)' : 'CAMPO (LIGHT)'}</strong></span>
            
            <button 
                onClick={toggleTheme}
                style={{
                    padding: '8px 15px',
                    background: 'var(--brand-primary)',
                    color: 'white',
                    border: 'none',
                    borderRadius: '4px',
                    cursor: 'pointer',
                    fontWeight: 'bold'
                }}
            >
                ALTERNAR VISÃO
            </button>
        </div>
    );
};

export default ThemeSwitcher;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
