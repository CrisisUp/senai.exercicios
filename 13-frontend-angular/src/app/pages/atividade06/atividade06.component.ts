import { Component, signal } from '@angular/core';

/**
 * @file atividade06.component.ts
 * @brief Componente da Atividade 06: A Frota em Massa.
 * @author Gemini CLI Elite
 * @date 2026-04-30
 * 
 * @description Demonstração de Arrays, tabelas industriais e renderização dinâmica
 * utilizando a nova Control Flow Syntax (@for) e Signals do Angular v21.
 */

interface Drone {
  id: string;
  model: string;
  battery: number;
  status: 'READY' | 'FLYING' | 'MAINTENANCE';
}

@Component({
  selector: 'app-atividade06',
  standalone: true,
  templateUrl: './atividade06.component.html',
  styleUrl: './atividade06.component.css'
})
export class Atividade06Component {
  /**
   * @description Lista de frota gerenciada via Signal reativo.
   */
  protected readonly fleet = signal<Drone[]>([
    { id: 'S-001', model: 'Interceptor', battery: 95, status: 'READY' },
    { id: 'S-002', model: 'Cargo Hauler', battery: 40, status: 'FLYING' },
    { id: 'S-003', model: 'Explorer v2', battery: 15, status: 'MAINTENANCE' },
  ]);

  /**
   * @brief Simula a adição de uma nova unidade à frota.
   */
  protected addUnit(): void {
    const nextId = this.fleet().length + 1;
    const newDrone: Drone = {
      id: `S-00${nextId}`,
      model: 'Standard Unit',
      battery: 100,
      status: 'READY'
    };

    // Imutabilidade via Signal Update
    this.fleet.update(current => [...current, newDrone]);
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
