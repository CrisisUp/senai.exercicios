/**
 * @date 2026
 */
import { Injectable, signal, OnDestroy } from '@angular/core';

/**
 * @file fleet.service.ts
 * @brief Serviço de Gestão de Frota (Patterns: Service, Singleton).
 * @author Gemini CLI Elite
 * 
 * @description Centraliza a lógica de telemetria e automação de consumo
 * de energia dos drones, provendo dados reativos para múltiplos componentes.
 */

export interface DroneState {
  id: string;
  name: string;
  battery: number;
}

@Injectable({
  providedIn: 'root'
})
export class FleetService implements OnDestroy {
  /**
   * @description Signal privado para controle interno da frota.
   * Expondo apenas a leitura para os componentes.
   */
  private readonly _drones = signal<DroneState[]>([
    { id: 'DX-01', name: 'Desert Storm', battery: 100 },
    { id: 'DX-02', name: 'Ocean Pearl', battery: 100 },
  ]);

  /**
   * @description Read-only signal para os consumidores.
   */
  public readonly drones = this._drones.asReadonly();

  private intervalId: any;

  constructor() {
    this.startSimulation();
  }

  /**
   * @brief Inicia a automação de telemetria (Consumo de Bateria).
   */
  private startSimulation(): void {
    this.intervalId = setInterval(() => {
      this._drones.update(currentDrones => 
        currentDrones.map(drone => ({
          ...drone,
          battery: Math.max(0, drone.battery - 1)
        }))
      );
      console.log("[NEXUS SERVICE] Telemetria atualizada automaticamente.");
    }, 3000);
  }

  /**
   * @brief Adiciona uma nova unidade à frota (Requisito de Expansão).
   */
  public addDrone(name: string): void {
    const newId = `DX-${(this._drones().length + 1).toString().padStart(2, '0')}`;
    this._drones.update(current => [
      ...current,
      { id: newId, name, battery: 100 }
    ]);
    console.log(`[NEXUS SERVICE] Nova unidade registrada: ${newId} (${name})`);
  }

  ngOnDestroy(): void {
    /**
     * @description Proteção contra ZOMBIE PROCESS (Requisito de Elite).
     */
    if (this.intervalId) {
      clearInterval(this.intervalId);
      console.log("[NEXUS SERVICE] Simulação encerrada com segurança.");
    }
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
