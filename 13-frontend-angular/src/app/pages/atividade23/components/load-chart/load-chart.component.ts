/**
 * @file load-chart.component.ts
 * @brief Componente de Gráfico SVG Reativo (Engenharia de Dados).
 * @author Cristiano
 * @date 2026
 */

import { Component, input, computed } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-load-chart',
  standalone: true,
  imports: [CommonModule],
  template: `
    <svg [attr.viewBox]="viewBox()" class="nexus-chart">
      <!-- Grid de Fundo -->
      @for (line of gridLines(); track $index) {
        <line [attr.x1]="0" [attr.y1]="line" [attr.x2]="width()" [attr.y2]="line" class="grid-line" />
      }

      <!-- Linha de Dados -->
      <polyline
        fill="none"
        stroke="#00ff9d"
        stroke-width="2"
        [attr.points]="pointsPath()"
        class="data-line"
      />

      <!-- Área Preenchida (Gradiente Simulado) -->
      <polygon
        [attr.points]="areaPath()"
        fill="url(#chartGradient)"
        class="data-area"
      />

      <!-- Definições de Gradiente -->
      <defs>
        <linearGradient id="chartGradient" x1="0%" y1="0%" x2="0%" y2="100%">
          <stop offset="0%" style="stop-color:#00ff9d; stop-opacity:0.3" />
          <stop offset="100%" style="stop-color:#00ff9d; stop-opacity:0" />
        </linearGradient>
      </defs>

      <!-- Pontos de Amostragem -->
      @for (p of scaledData(); track $index) {
        <circle [attr.cx]="p.x" [attr.cy]="p.y" r="3" class="data-point" />
      }
    </svg>
  `,
  styles: [`
    .nexus-chart {
      width: 100%;
      height: 200px;
      background: #0a0a0a;
      border: 1px solid #1a1a1a;
      border-radius: 4px;
    }
    .grid-line {
      stroke: #1a1a1a;
      stroke-width: 1;
    }
    .data-line {
      stroke-dasharray: 1000;
      stroke-dashoffset: 0;
      /* transition: stroke-dashoffset 2s ease-in-out; */
    }
    .data-point {
      fill: #00ff9d;
      filter: drop-shadow(0 0 5px #00ff9d);
    }
  `]
})
export class LoadChartComponent {
  /**
   * @brief Dados brutos de entrada (Signal Input).
   */
  data = input.required<number[]>();
  width = input<number>(600);
  height = input<number>(200);

  protected viewBox = computed(() => `0 0 ${this.width()} ${this.height()}`);

  /**
   * @brief Escala os dados para as dimensões do SVG.
   */
  protected scaledData = computed(() => {
    const raw = this.data();
    if (raw.length === 0) return [];
    
    const max = Math.max(...raw, 100);
    const step = this.width() / (raw.length - 1);
    
    return raw.map((val, i) => ({
      x: i * step,
      y: this.height() - (val / max) * this.height()
    }));
  });

  protected pointsPath = computed(() => 
    this.scaledData().map(p => `${p.x},${p.y}`).join(' ')
  );

  protected areaPath = computed(() => {
    const points = this.scaledData();
    if (points.length === 0) return '';
    const first = points[0];
    const last = points[points.length - 1];
    return `${first.x},${this.height()} ${this.pointsPath()} ${last.x},${this.height()}`;
  });

  protected gridLines = computed(() => {
    const lines = [];
    for (let i = 0; i <= this.height(); i += this.height() / 4) {
      lines.push(i);
    }
    return lines;
  });
}

/* @section ArchitectureMap
 * Gráfico desenvolvido puramente com SVG + Angular Signals.
 * Vantagens:
 * 1. Zero Dependências Externas (Engenharia de Elite).
 * 2. Alta Performance (Reatividade Granular).
 * 3. Acessibilidade e Escalabilidade infinita.
 */
