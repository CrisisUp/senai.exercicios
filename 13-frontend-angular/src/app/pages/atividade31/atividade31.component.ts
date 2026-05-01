/**
 * @file atividade31.component.ts
 * @brief Atividade 31: O Orquestrador Global (Dynamic Component Loading).
 * @author Cristiano
 * @date 2026
 */

import { Component, ViewChild, ViewContainerRef, signal, Type } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RemoteModuleAComponent } from './components/remote-module-a/remote-module-a.component';
import { RemoteModuleBComponent } from './components/remote-module-b/remote-module-b.component';

@Component({
  selector: 'app-atividade31',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade31.component.html',
  styleUrl: './atividade31.component.css'
})
export class Atividade31Component {
  /**
   * @brief Anchor point para o carregamento dinâmico.
   */
  @ViewChild('mfeContainer', { read: ViewContainerRef }) container!: ViewContainerRef;

  protected readonly activeMfe = signal<string | null>(null);

  /**
   * @brief Orquestra o carregamento de "Micro-Frontends".
   * Demonstra o uso de ViewContainerRef para injetar componentes em tempo de execução.
   */
  protected async loadMfe(type: 'LOGISTICS' | 'TELEMETRY'): Promise<void> {
    this.container.clear();
    this.activeMfe.set(type);

    let component: Type<any>;

    if (type === 'LOGISTICS') {
      // Simula o carregamento dinâmico (lazy import)
      const { RemoteModuleAComponent } = await import('./components/remote-module-a/remote-module-a.component');
      component = RemoteModuleAComponent;
    } else {
      const { RemoteModuleBComponent } = await import('./components/remote-module-b/remote-module-b.component');
      component = RemoteModuleBComponent;
    }

    this.container.createComponent(component);
    console.log(`[ORCHESTRATOR] Módulo ${type} injetado com sucesso.`);
  }

  /* @section ArchitectureMap
   * Implementa o padrão 'Shell/Kernel'.
   * O Shell (Atividade31) não possui dependências diretas de renderização.
   * Ele utiliza ViewContainerRef.createComponent para orquestrar o ciclo de vida
   * de módulos independentes (MFE Simulation).
   */
}

/*
 * RESUMO TEÓRICO
 * Dynamic Component Loading é a base técnica para Micro-Frontends no Angular.
 * Permite que a aplicação carregue e instancie componentes que não estão presentes 
 * no template inicial, possibilitando arquiteturas altamente modulares, 
 * dashboards customizáveis por usuário e integração com Module Federation.
 */
