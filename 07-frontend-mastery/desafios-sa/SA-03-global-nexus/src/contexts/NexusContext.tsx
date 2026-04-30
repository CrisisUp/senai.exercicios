/**
 * @file NexusContext.tsx
 * @brief Orquestrador de Estado Global Full-Stack.
 * @author Engenheiro de Elite
 */

import React, { createContext, useContext, useState, useEffect, useCallback, ReactNode } from 'react';
import type { IGlobalState, MissionStatus, IDroneTelemetria } from '../types';

interface NexusContextType extends IGlobalState {
    fleet: IDroneTelemetria[];
    updateMissionStatus: (status: MissionStatus) => void;
    pushCommand: (droneId: string, command: string) => void;
}

const NexusContext = createContext<NexusContextType | undefined>(undefined);

export const NexusProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    // 1. Estado Global Reativo
    const [fleet, setFleet] = useState<IDroneTelemetria[]>([]);
    const [missionStatus, setMissionStatus] = useState<MissionStatus>('ACTIVE');
    const [networkIntegrity, setNetworkIntegrity] = useState<number>(100);
    const [lastNexusSync, setLastNexusSync] = useState<Date>(new Date());

    // 2. Handlers de Comando (Elite)
    const updateMissionStatus = (status: MissionStatus) => setMissionStatus(status);
    
    const pushCommand = useCallback((droneId: string, command: string) => {
        console.log(`\x1b[1;33m[NEXUS-HQ]\x1b[0m Comando '${command}' enviado para ${droneId}`);
        // Aqui o comando seria enviado via WebSocket para o servidor Rust
    }, []);

    // 3. Simulação de Integração WebSockets (Tempo Real)
    useEffect(() => {
        // Inicialização da frota (Simulando REST inicial)
        setFleet([
            { id: 'ALPHA-707', modelo: 'Interceptor', altitude: 150, velocidade: 85, bateria: 92, latitude: -23.55, longitude: -46.63, status: 'OPERACIONAL' },
            { id: 'BETA-404', modelo: 'Cargo', altitude: 12, velocidade: 0, bateria: 5, latitude: -23.56, longitude: -46.64, status: 'CRITICO' }
        ]);

        // Simulação de fluxo contínuo (Sinal do Hardware C++)
        const telemetryStream = setInterval(() => {
            setFleet(prev => prev.map(drone => ({
                ...drone,
                altitude: drone.altitude + (Math.random() > 0.5 ? 2 : -2),
                lastNexusSync: new Date()
            })));
            setLastNexusSync(new Date());
        }, 2000);

        return () => clearInterval(telemetryStream);
    }, []);

    return (
        <NexusContext.Provider value={{ 
            fleet, 
            missionStatus, 
            activeDrones: fleet.length, 
            networkIntegrity, 
            lastNexusSync,
            updateMissionStatus,
            pushCommand
        }}>
            {children}
        </NexusContext.Provider>
    );
};

export const useNexus = () => {
    const context = useContext(NexusContext);
    if (!context) throw new Error("useNexus deve ser usado dentro de NexusProvider");
    return context;
};
