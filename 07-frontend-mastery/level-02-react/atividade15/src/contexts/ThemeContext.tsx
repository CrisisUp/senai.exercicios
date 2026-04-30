/**
 * @file ThemeContext.tsx
 * @brief Cérebro Global de Estilização do SkyCargo OS.
 * @author Engenheiro de Elite
 */

import React, { createContext, useContext, useState, ReactNode } from 'react';

// 1. Definição do Tipo do Contexto
interface ThemeContextType {
    isDarkMode: boolean;
    toggleTheme: () => void;
}

// 2. Criação do Contexto (Inicialmente indefinido)
const ThemeContext = createContext<ThemeContextType | undefined>(undefined);

/**
 * @brief Componente Provedor (O Campo de Força).
 * Envolve a aplicação e gerencia o estado global de tema.
 */
export const ThemeProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    const [isDarkMode, setIsDarkMode] = useState<boolean>(true);

    const toggleTheme = () => {
        setIsDarkMode(prev => !prev);
        console.log(`\x1b[1;36m[CONTEXT]\x1b[0m Tema global alterado para: ${!isDarkMode ? 'DARK' : 'LIGHT'}`);
    };

    return (
        <ThemeContext.Provider value={{ isDarkMode, toggleTheme }}>
            <div className={isDarkMode ? '' : 'light-mode'} style={{ minHeight: '100vh' }}>
                {children}
            </div>
        </ThemeContext.Provider>
    );
};

/**
 * @brief Custom Hook de Elite.
 * Facilita o acesso ao contexto e valida se o componente consumidor está dentro do provedor.
 */
export const useTheme = () => {
    const context = useContext(ThemeContext);
    if (!context) {
        throw new Error("useTheme deve ser usado dentro de um ThemeProvider");
    }
    return context;
};
