/**
 * @file restricted-zone.component.ts
 * @brief Componente Protegido por Guard de Rota.
 * @author Cristiano
 * @date 2026
 */

import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-restricted-zone',
  standalone: true,
  imports: [CommonModule],
  template: `
    <div class="secure-container">
      <header>
        <h2>🛡️ ÁREA DE ACESSO RESTRITO</h2>
        <span class="clearance">CLEARANCE: LEVEL 5</span>
      </header>
      <main>
        <p>Você acessou o núcleo de dados criptografados do Nexus. Esta área só é visível para operadores autenticados.</p>
        <div class="data-stream">
          <code>DECRYPTING_FLIGHT_LOGS_2026... OK</code>
        </div>
      </main>
    </div>
  `,
  styles: [`
    .secure-container {
      background: #000;
      border: 1px solid #f85149;
      padding: 2rem;
      border-radius: 8px;
      animation: scanline 4s linear infinite;
    }
    .clearance {
      background: #f85149;
      color: #fff;
      font-size: 0.7rem;
      padding: 2px 6px;
      border-radius: 4px;
    }
    .data-stream {
      margin-top: 1rem;
      color: #3fb950;
      font-family: monospace;
    }
    @keyframes scanline {
      0% { box-shadow: 0 0 5px rgba(248, 81, 73, 0.1); }
      50% { box-shadow: 0 0 20px rgba(248, 81, 73, 0.3); }
      100% { box-shadow: 0 0 5px rgba(248, 81, 73, 0.1); }
    }
  `]
})
export class RestrictedZoneComponent {}
