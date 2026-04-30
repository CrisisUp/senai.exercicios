/**
 * @file MissionContext.tsx
 * @brief Gerenciador de Estado Global da Missão SkyCargo.
 * @author Engenheiro de Elite
 */

import React, { createContext, useContext, useState, useEffect, useCallback } from 'react';
import type { ReactNode } from 'react';
import type { IDrone, IMissionState } from '../types';

interface MissionContextType extends IMissionState {
    sendCommand: (droneId: string, action: string) => void;
    toggleSystemIntegrity: () => void;
}

const MissionContext = createContext<MissionContextType | undefined>(undefined);

export const MissionProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    // 1. Estado Centralizado
    const [fleet, setFleet] = useState<IDrone[]>([
        { id: 'ALPHA-707', modelo: 'Interceptor', status: 'OPERACIONAL', altitude: 150, velocidade: 85 },
        { id: 'BETA-404', modelo: 'Cargo', status: 'ALERTA', altitude: 12, velocidade: 0 }
    ]);
    const [systemIntegrity, setSystemIntegrity] = useState<number>(100);
    const [lastSync, setLastSync] = useState<Date>(new Date());

    // 2. Operação de Comando (Memoizada para evitar re-renders de botões)
    const sendCommand = useCallback((droneId: string, action: string) => {
        console.log(`\x1b[1;33m[NEXUS-HQ]\x1b[0m Comando '${action}' para ${droneId}`);
        setFleet(prev => prev.map(d => 
            d.id === droneId ? { ...d, status: 'EM ROTA' } : d
        ));
    }, []);

    const toggleSystemIntegrity = () => setSystemIntegrity(prev => (prev === 100 ? 85 : 100));

    // 3. Efeito de Sincronia Automática (Polling Industrial)
    useEffect(() => {
        const timer = setInterval(() => {
            setLastSync(new Date());
            // Simulação de oscilação de altitude
            setFleet(prev => prev.map(d => ({
                ...d,
                altitude: d.altitude + (Math.random() > 0.5 ? 1 : -1)
            })));
        }, 5000);

        return () => clearInterval(timer);
    }, []);

    return (
        <MissionContext.Provider value={{ 
            fleet, 
            activeDrones: fleet.length, 
            systemIntegrity, 
            lastSync,
            sendCommand,
            toggleSystemIntegrity
        }}>
            {children}
        </MissionContext.Provider>
    );
};

export const useMission = () => {
    const context = useContext(MissionContext);
    if (!context) throw new Error("useMission deve ser usado dentro de MissionProvider");
    return context;
};
