/**
 * @file nexus-card.component.ts
 * @brief Componente de Moldura Industrial (Content Projection).
 * @author Cristiano
 * @date 2026
 */

import { Component, input } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-nexus-card',
  standalone: true,
  imports: [CommonModule],
  template: `
    <div class="card-container" [class.highlight]="isPriority()">
      <header class="card-header">
        <span class="sector-tag">{{ sector() }}</span>
        <ng-content select="[card-icon]"></ng-content>
      </header>
      
      <main class="card-content">
        <ng-content></ng-content>
      </main>
      
      <footer class="card-footer">
        <ng-content select="[card-actions]"></ng-content>
      </footer>
    </div>
  `,
  styles: [`
    .card-container {
      background: #161b22;
      border: 1px solid #30363d;
      border-radius: 8px;
      padding: 1rem;
      transition: all 0.3s ease;
      position: relative;
      overflow: hidden;
    }
    .card-container.highlight {
      border-color: #f85149;
      box-shadow: 0 0 15px rgba(248, 81, 73, 0.15);
    }
    .card-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 1rem;
    }
    .sector-tag {
      font-size: 0.65rem;
      background: #30363d;
      color: #8b949e;
      padding: 2px 6px;
      border-radius: 4px;
      text-transform: uppercase;
    }
    .card-content {
      color: #e6edf3;
      margin-bottom: 1rem;
    }
    .card-footer {
      border-top: 1px solid #30363d;
      padding-top: 0.8rem;
      display: flex;
      justify-content: flex-end;
      gap: 0.5rem;
    }
  `]
})
export class NexusCardComponent {
  sector = input<string>('GENERAL');
  isPriority = input<boolean>(false);
}

/* @section ArchitectureMap
 * Implementa Projeção de Conteúdo Multi-slot.
 * <ng-content select="[card-icon]"> -> Projeção Nomeada via Atributo.
 * <ng-content> -> Projeção Padrão (Default Slot).
 */
