/**
 * @author Cristiano
 * @date 2026
 */
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

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
