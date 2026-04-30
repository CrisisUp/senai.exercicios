/**
 * @file types/index.ts
 * @brief Contratos de Dados Globais - SkyCargo Global Nexus.
 */

export type MissionStatus = 'PRE-FLIGHT' | 'ACTIVE' | 'EMERGENCY' | 'COMPLETED';

export interface IDroneTelemetria {
    id: string;
    modelo: string;
    altitude: number;
    velocidade: number;
    bateria: number;
    latitude: number;
    longitude: number;
    status: 'OPERACIONAL' | 'ALERTA' | 'CRITICO';
}

export interface INexusEvent {
    id: string;
    timestamp: string;
    layer: 'HARDWARE' | 'SECURITY' | 'DATA' | 'CLOUD';
    message: string;
}

export interface IGlobalState {
    missionStatus: MissionStatus;
    activeDrones: number;
    networkIntegrity: number;
    lastNexusSync: Date;
}
