/**
 * @file remote-module-b.component.ts
 * @brief Módulo Remoto Simulado B (Micro-Frontend).
 * @author Cristiano
 * @date 2026
 */

import { Component } from '@angular/core';

@Component({
  selector: 'app-remote-b',
  standalone: true,
  template: `
    <div class="mfe-card blue">
      <h4>MODULE: TELEMETRY_HUB</h4>
      <p>Análise de sensores e link de satélite em tempo real.</p>
      <div class="status">UPLINK: ACTIVE</div>
    </div>
  `,
  styles: [`
    .mfe-card {
      padding: 1.5rem;
      border: 1px solid #58a6ff;
      background: rgba(88, 166, 255, 0.05);
      border-radius: 8px;
    }
    h4 { color: #58a6ff; margin: 0 0 0.5rem 0; }
    .status { font-size: 0.7rem; font-weight: bold; color: #ab7df8; margin-top: 1rem; }
  `]
})
export class RemoteModuleBComponent {}
