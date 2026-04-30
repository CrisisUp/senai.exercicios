/**
 * @file types/index.ts
 * @brief Contratos de Dados para o SkyCargo React Engine.
 */

export type DroneStatus = 'OPERACIONAL' | 'EM ROTA' | 'ALERTA' | 'OFFLINE';

export interface IDrone {
    id: string;
    modelo: string;
    status: DroneStatus;
    altitude: number;
    velocidade: number;
}

export interface IMissionState {
    fleet: IDrone[];
    activeDrones: number;
    systemIntegrity: number;
    lastSync: Date;
}
