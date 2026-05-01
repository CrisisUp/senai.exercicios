/**
 * @file atividade32.component.ts
 * @brief Atividade 32: A Consciência Coletiva (State Management Industrial).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { NexusStore } from './store/nexus.store';

@Component({
  selector: 'app-atividade32',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade32.component.html',
  styleUrl: './atividade32.component.css'
})
export class Atividade32Component {
  /**
   * @brief Injeção do Store Global.
   */
  protected readonly store = inject(NexusStore);

  // Fatias do Estado consumidas de forma reativa
  protected readonly alert = this.store.globalAlert;
  protected readonly nodes = this.store.activeNodes;
  protected readonly protocol = this.store.securityProtocol;

  protected triggerAlert(): void {
    this.store.updateAlert('VIOLAÇÃO DE PERÍMETRO NO SETOR 7G');
  }

  protected resolveAlert(): void {
    this.store.updateAlert(null);
  }

  protected changeProtocol(p: 'ALPHA' | 'BETA' | 'DELTA'): void {
    this.store.setProtocol(p);
  }

  protected addNode(): void {
    this.store.incrementNodes();
  }

  /* @section ArchitectureMap
   * O componente Atividade32 atua como um 'Consumer' e 'Dispatcher'.
   * Ele não possui estado local para os dados do sistema; ele apenas mapeia
   * interações do usuário para chamadas na NexusStore, que orquestra a verdade global.
   */
}

/*
 * RESUMO TEÓRICO
 * State Management em larga escala exige a separação entre UI e Dados.
 * O Pattern Signal Store oferece uma alternativa leve ao Redux (NgRx), 
 * mantendo a previsibilidade e imutabilidade, mas aproveitando a simplicidade 
 * e performance nativa dos Signals do Angular.
 */
