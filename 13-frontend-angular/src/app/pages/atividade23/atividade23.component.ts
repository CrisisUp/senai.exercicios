/**
 * @file atividade23.component.ts
 * @brief Atividade 23: O Analisador de Carga (Reactive SVG Data Viz).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal, OnInit, OnDestroy } from '@angular/core';
import { CommonModule } from '@angular/common';
import { LoadChartComponent } from './components/load-chart/load-chart.component';

@Component({
  selector: 'app-atividade23',
  standalone: true,
  imports: [CommonModule, LoadChartComponent],
  templateUrl: './atividade23.component.html',
  styleUrl: './atividade23.component.css'
})
export class Atividade23Component implements OnInit, OnDestroy {
  /**
   * @description Stream de dados de telemetria simulados.
   */
  protected readonly telemetryData = signal<number[]>([]);
  private intervalId: any;

  ngOnInit(): void {
    // Inicializa com alguns dados
    this.telemetryData.set([30, 45, 60, 20, 85, 40, 55, 90, 70, 35]);

    // Simula telemetria contínua
    this.intervalId = setInterval(() => {
      this.telemetryData.update(current => {
        const next = [...current.slice(1), Math.floor(Math.random() * 100)];
        return next;
      });
    }, 2000);
  }

  ngOnDestroy(): void {
    if (this.intervalId) {
      clearInterval(this.intervalId);
    }
  }

  /* @section ArchitectureMap
   * O componente Atividade23 gerencia o ciclo de vida dos dados (Ingestion).
   * Ele utiliza um Signal imutável para notificar o LoadChartComponent.
   * O LoadChart, por sua vez, reage apenas às mudanças de referência do array.
   */
}

/*
 * RESUMO TEÓRICO
 * Gráficos SVG representam o estado da arte na visualização de dados web.
 * Ao contrário do Canvas (bitmap), o SVG é baseado em vetores (XML),
 * o que permite ao Angular gerenciar cada elemento gráfico (linha, círculo) 
 * como parte integrante do seu grafo de dependências, permitindo animações CSS 
 * e interatividade direta via templates.
 */
