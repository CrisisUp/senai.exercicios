/**
 * @file types/index.ts
 * @brief Contratos de Dados para Gerenciamento de Frota.
 */

export type DroneStatus = 'OPERACIONAL' | 'EM ROTA' | 'ALERTA' | 'POUSADO';

export interface IDrone {
    id: string; // O ID Único servirá como nossa KEY de reconciliação
    modelo: string;
    status: DroneStatus;
    carga_util: number;
}
