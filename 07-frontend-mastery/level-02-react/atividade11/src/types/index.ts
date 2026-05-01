/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file types/index.ts
 * @brief Contratos de Dados de Elite para o ecossistema Nexus.
 */

export type DroneStatus = 'OPERACIONAL' | 'EM ROTA' | 'ALERTA' | 'OFFLINE';

export interface IDrone {
    readonly id: string;
    modelo: string;
    status: DroneStatus;
    altitude: number;
    velocidade: number;
}

export interface ILogEvent {
    id: string;
    timestamp: Date;
    message: string;
    severity: 'INFO' | 'WARN' | 'CRITICAL';
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
