/**
 * @file atividade10.component.ts
 * @brief Atividade 10: Terminal de Controle Global (Desafio Integrador).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, signal, computed } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { FleetService } from '../atividade08/services/fleet.service';

/**
 * @description O Desafio Integrador consolida Signals, Services, Forms e Control Flow.
 * Implementa um dashboard tático para monitoramento e expansão da frota Nexus.
 */

@Component({
  selector: 'app-atividade10',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './atividade10.component.html',
  styleUrl: './atividade10.component.css'
})
export class Atividade10Component {
  private readonly fleetService = inject(FleetService);

  // Estados Locais (Formulário)
  protected newDroneName = signal<string>('');
  protected filterText = signal<string>('');

  // Reatividade Composta
  protected readonly drones = this.fleetService.drones;
  
  protected readonly filteredDrones = computed(() => {
    const filter = this.filterText().toLowerCase();
    return this.drones().filter(d => 
      d.name.toLowerCase().includes(filter) || 
      d.id.toLowerCase().includes(filter)
    );
  });

  protected readonly totalBatteryAverage = computed(() => {
    const list = this.drones();
    if (list.length === 0) return 0;
    return list.reduce((acc, d) => acc + d.battery, 0) / list.length;
  });

  /**
   * @brief Adiciona uma nova unidade à frota centralizada.
   * Demonstra o uso de serviços para persistência de estado entre componentes.
   */
  protected registerUnit(): void {
    if (this.newDroneName().trim().length < 3) return;

    this.fleetService.addDrone(this.newDroneName());
    this.newDroneName.set('');
  }
}

/* @section ArchitectureMap
 * Fluxo: Componente -> FleetService (Data Store) -> UI (Reactive Signals).
 * O uso de computed() garante que a filtragem e médias sejam recalculadas apenas quando necessário.
 */

/*
 * RESUMO TEÓRICO
 * O Desafio Integrador do Nível 01 valida a transição da manipulação de DOM para a 
 * arquitetura orientada a estados (Signals). O Angular moderno foca em componentes
 * leves e serviços potentes.
 */
