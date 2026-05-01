/**
 * @file remote-module-a.component.ts
 * @brief Módulo Remoto Simulado A (Micro-Frontend).
 * @author Cristiano
 * @date 2026
 */

import { Component } from '@angular/core';

@Component({
  selector: 'app-remote-a',
  standalone: true,
  template: `
    <div class="mfe-card orange">
      <h4>MODULE: LOGISTICS_CORE</h4>
      <p>Gerenciamento de inventário e distribuição global.</p>
      <div class="status">HEALTH: OPTIMAL</div>
    </div>
  `,
  styles: [`
    .mfe-card {
      padding: 1.5rem;
      border: 1px solid #d29922;
      background: rgba(210, 153, 34, 0.05);
      border-radius: 8px;
    }
    h4 { color: #d29922; margin: 0 0 0.5rem 0; }
    .status { font-size: 0.7rem; font-weight: bold; color: #3fb950; margin-top: 1rem; }
  `]
})
export class RemoteModuleAComponent {}
