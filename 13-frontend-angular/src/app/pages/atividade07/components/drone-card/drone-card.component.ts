/**
 * @date 2026
 */
import { Component, input } from '@angular/core';

/**
 * @file drone-card.component.ts
 * @brief Subcomponente para exibição de unidade individual (Component Composition).
 * @author Gemini CLI Elite
 */

export interface Drone {
  id: string;
  name: string;
  status: 'OPERATIONAL' | 'WARNING' | 'IN_ROUTE';
  load: number;
}

@Component({
  selector: 'app-drone-card',
  standalone: true,
  template: `
    <div class="card" [class]="status()">
      <div class="card-glass">
        <span class="drone-id">{{ id() }}</span>
        <h3>{{ name() }}</h3>
        <div class="status-info">
          <span class="indicator"></span>
          {{ status().replace('_', ' ') }}
        </div>
        <div class="load-area">
          <label>Carga:</label>
          <span>{{ load() }}%</span>
          <div class="load-bar">
            <div class="load-fill" [style.width.%]="load()"></div>
          </div>
        </div>
      </div>
    </div>
  `,
  styles: [`
    .card {
      border-radius: 12px;
      padding: 2px;
      background: linear-gradient(135deg, rgba(255,255,255,0.1), rgba(255,255,255,0.05));
      position: relative;
      overflow: hidden;
    }

    .card-glass {
      background: rgba(22, 27, 34, 0.8); /* CSS (Estética): RGBA Glassmorphism */
      backdrop-filter: blur(10px);
      border-radius: 10px;
      padding: 1.5rem;
      height: 100%;
      border: 1px solid rgba(255, 255, 255, 0.1);
    }

    /* CSS (Estética): Cores HSL para Status */
    .OPERATIONAL { --status-color: hsl(140, 50%, 50%); }
    .WARNING { --status-color: hsl(0, 70%, 50%); }
    .IN_ROUTE { --status-color: hsl(210, 70%, 50%); }

    h3 {
      margin: 0.5rem 0;
      color: #fff;
    }

    .drone-id {
      font-size: 0.7rem;
      font-family: monospace;
      color: var(--status-color);
      font-weight: bold;
    }

    .status-info {
      display: flex;
      align-items: center;
      gap: 0.5rem;
      font-size: 0.8rem;
      color: #8b949e;
      text-transform: uppercase;
      margin-bottom: 1rem;
    }

    .indicator {
      width: 8px;
      height: 8px;
      border-radius: 50%;
      background-color: var(--status-color);
      box-shadow: 0 0 8px var(--status-color);
    }

    .load-area {
      font-size: 0.8rem;
    }

    .load-bar {
      height: 4px;
      background: rgba(0,0,0,0.3);
      border-radius: 2px;
      margin-top: 0.5rem;
    }

    .load-fill {
      height: 100%;
      background-color: #3fb950;
      border-radius: 2px;
    }
  `]
})
export class DroneCardComponent {
  /**
   * @description Uso da nova API de inputs baseada em Signals (Angular v17.1+)
   */
  id = input.required<string>();
  name = input.required<string>();
  status = input.required<'OPERATIONAL' | 'WARNING' | 'IN_ROUTE'>();
  load = input.required<number>();
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
