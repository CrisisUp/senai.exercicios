/**
 * @file plugin-terminator.component.ts
 * @brief Plugin de Limpeza de Sistema.
 * @author Cristiano
 * @date 2026
 */

import { Component } from '@angular/core';

@Component({
  selector: 'app-plugin-terminator',
  standalone: true,
  template: `
    <div class="plugin-host terminator">
      <div class="header">
        <span class="p-icon">💀</span>
        <h5>NEURAL_TERMINATOR_OS</h5>
      </div>
      <div class="status-box">
        CLEANING_ZOMBIES... DONE<br>
        CACHE_PURGED: 4.2GB
      </div>
    </div>
  `,
  styles: [`
    .plugin-host {
      background: #000;
      border: 1px solid #f85149;
      padding: 1rem;
      border-radius: 4px;
      font-family: monospace;
    }
    .header { display: flex; align-items: center; gap: 8px; margin-bottom: 1rem; }
    h5 { margin: 0; color: #f85149; }
    .status-box { font-size: 0.7rem; color: #3fb950; font-weight: bold; }
  `]
})
export class PluginTerminatorComponent {}
