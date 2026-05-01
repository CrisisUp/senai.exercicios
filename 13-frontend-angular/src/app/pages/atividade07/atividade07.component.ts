/**
 * @date 2026
 */
import { Component, signal, computed } from '@angular/core';
import { Drone, DroneCardComponent } from './components/drone-card/drone-card.component';

/**
 * @file atividade07.component.ts
 * @brief Componente da Atividade 07: Visão Tática (Filtros e Signals).
 * @author Gemini CLI Elite
 */

@Component({
  selector: 'app-atividade07',
  standalone: true,
  imports: [DroneCardComponent],
  templateUrl: './atividade07.component.html',
  styleUrl: './atividade07.component.css'
})
export class Atividade07Component {
  /**
   * @description Signal para o filtro selecionado (JS Atitude).
   */
  protected readonly filter = signal<string>('ALL');

  /**
   * @description Dados brutos da frota.
   */
  private readonly fullFleet: Drone[] = [
    { id: 'DR-10', name: 'Eagle Eye', status: 'OPERATIONAL', load: 45 },
    { id: 'DR-22', name: 'Storm Breaker', status: 'WARNING', load: 88 },
    { id: 'DR-35', name: 'Night Hawk', status: 'IN_ROUTE', load: 12 },
    { id: 'DR-49', name: 'Cloud Racer', status: 'OPERATIONAL', load: 30 },
    { id: 'DR-51', name: 'Iron Wing', status: 'WARNING', load: 95 },
  ];

  /**
   * @description Signal computado para a frota filtrada (Requisito de Elite).
   * Substitui o useMemo do React com performance nativa superior.
   */
  protected readonly filteredFleet = computed(() => {
    const currentFilter = this.filter();
    if (currentFilter === 'ALL') return this.fullFleet;
    return this.fullFleet.filter(drone => drone.status === currentFilter);
  });

  /**
   * @brief Handler para mudança do filtro.
   */
  protected onFilterChange(event: Event): void {
    const select = event.target as HTMLSelectElement;
    this.filter.set(select.value);
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
