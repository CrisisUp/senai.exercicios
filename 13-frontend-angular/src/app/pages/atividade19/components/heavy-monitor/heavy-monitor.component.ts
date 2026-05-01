/**
 * @file heavy-monitor.component.ts
 * @brief Componente de Alta Carga (Simulação de Processamento).
 * @author Cristiano
 * @date 2026
 */

import { Component, ChangeDetectionStrategy, signal, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-heavy-monitor',
  standalone: true,
  imports: [CommonModule],
  changeDetection: ChangeDetectionStrategy.OnPush,
  template: `
    <div class="heavy-card">
      <header>
        <h4>NÚCLEO DE PROCESSAMENTO</h4>
        <span class="load-badge">LOAD: {{ cpuLoad() }}%</span>
      </header>
      <div class="visualizer">
        @for (bar of bars(); track $index) {
          <div class="bar" [style.height.%]="bar"></div>
        }
      </div>
      <p class="optimization-note">
        <b>OnPush Active:</b> Este componente só renderiza quando seus Signals ou Inputs mudam.
      </p>
    </div>
  `,
  styles: [`
    .heavy-card {
      background: #000;
      border: 1px solid #30363d;
      padding: 1.5rem;
      border-radius: 8px;
    }
    header {
      display: flex;
      justify-content: space-between;
      margin-bottom: 1rem;
    }
    .load-badge {
      color: #3fb950;
      font-family: monospace;
    }
    .visualizer {
      display: flex;
      gap: 2px;
      height: 60px;
      align-items: flex-end;
      margin-bottom: 1rem;
    }
    .bar {
      flex: 1;
      background: #58a6ff;
      transition: height 0.3s ease;
    }
    .optimization-note {
      font-size: 0.7rem;
      color: #8b949e;
    }
  `]
})
export class HeavyMonitorComponent implements OnInit {
  protected readonly cpuLoad = signal<number>(0);
  protected readonly bars = signal<number[]>([]);

  ngOnInit(): void {
    // Inicializa barras aleatórias
    this.bars.set(Array.from({ length: 40 }, () => Math.random() * 100));
    
    // Simula atualização de carga
    setInterval(() => {
      this.cpuLoad.set(Math.floor(Math.random() * 100));
      this.bars.set(Array.from({ length: 40 }, () => Math.random() * 100));
    }, 2000);
  }
}
