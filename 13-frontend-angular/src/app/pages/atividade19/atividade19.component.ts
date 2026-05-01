/**
 * @file atividade19.component.ts
 * @brief Atividade 19: O Núcleo de Performance (OnPush & Defer).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HeavyMonitorComponent } from './components/heavy-monitor/heavy-monitor.component';

@Component({
  selector: 'app-atividade19',
  standalone: true,
  imports: [CommonModule, HeavyMonitorComponent],
  templateUrl: './atividade19.component.html',
  styleUrl: './atividade19.component.css'
})
export class Atividade19Component {
  /**
   * @description Controle para disparar o carregamento lazy via @defer.
   */
  protected readonly isSystemReady = signal<boolean>(false);

  protected bootSystem(): void {
    this.isSystemReady.set(true);
    console.log("[NEXUS PERF] Disparando protocolo de inicialização diferida.");
  }
}

/* @section ArchitectureMap
 * Implementa @defer (Deferrable Views) para adiar o carregamento de componentes pesados.
 * Utiliza @placeholder para UI imediata e @loading para feedback de download.
 * O componente pesado (HeavyMonitor) utiliza OnPush para otimizar o ciclo de vida.
 */

/*
 * RESUMO TEÓRICO
 * @defer é a revolução do Angular 17/18 para Lazy Loading de componentes no nível do template.
 * Reduz o bundle size inicial e melhora o Core Web Vitals (LCP/FID).
 * Combinado com OnPush, garante que a aplicação permaneça fluida mesmo com dashboards complexos.
 */
