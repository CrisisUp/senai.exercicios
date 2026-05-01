/**
 * @file plugin-scanner.component.ts
 * @brief Plugin de Scanner de Elite.
 * @author Cristiano
 * @date 2026
 */

import { Component } from '@angular/core';

@Component({
  selector: 'app-plugin-scanner',
  standalone: true,
  template: `
    <div class="plugin-host scanner">
      <div class="header">
        <span class="p-icon">🔍</span>
        <h5>OMNI_SCAN_ACTIVE</h5>
      </div>
      <div class="scan-line"></div>
      <div class="p-data">
        TARGET: INFRA_STRUCTURE_7<br>
        THREAT_LEVEL: 2%
      </div>
    </div>
  `,
  styles: [`
    .plugin-host {
      background: #000;
      border: 1px solid #d29922;
      padding: 1rem;
      border-radius: 4px;
      font-family: monospace;
      position: relative;
      overflow: hidden;
    }
    .header { display: flex; align-items: center; gap: 8px; margin-bottom: 1rem; }
    h5 { margin: 0; color: #d29922; }
    .scan-line {
      height: 2px;
      background: rgba(210, 153, 34, 0.4);
      position: absolute;
      width: 100%;
      left: 0;
      top: 0;
      animation: sweep 2s infinite linear;
    }
    .p-data { font-size: 0.7rem; color: #8b949e; line-height: 1.4; }
    @keyframes sweep {
      0% { top: 0; }
      100% { top: 100%; }
    }
  `]
})
export class PluginScannerComponent {}
