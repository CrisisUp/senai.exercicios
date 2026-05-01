/**
 * @file nexus.store.ts
 * @brief Store Global de Elite baseada em Signals (Pattern: Signal Store).
 * @author Cristiano
 * @date 2026
 */

import { Injectable, signal, computed } from '@angular/core';

export interface NexusState {
  systemTitle: string;
  globalAlert: string | null;
  activeNodes: number;
  securityProtocol: 'ALPHA' | 'BETA' | 'DELTA';
}

@Injectable({
  providedIn: 'root'
})
export class NexusStore {
  /**
   * @brief Estado Privado (O Cofre).
   */
  private readonly _state = signal<NexusState>({
    systemTitle: 'NEXUS_ENTERPRISE_OS',
    globalAlert: null,
    activeNodes: 12,
    securityProtocol: 'ALPHA'
  });

  /**
   * @brief Seletores Reativos (Read-only views).
   */
  public readonly systemTitle = computed(() => this._state().systemTitle);
  public readonly globalAlert = computed(() => this._state().globalAlert);
  public readonly activeNodes = computed(() => this._state().activeNodes);
  public readonly securityProtocol = computed(() => this._state().securityProtocol);

  /**
   * @brief Redutores/Ações de Estado (Mutations).
   */
  public updateAlert(message: string | null): void {
    this._state.update(s => ({ ...s, globalAlert: message }));
    console.log(`[STORE] Alerta Global: ${message || 'NORMAL'}`);
  }

  public incrementNodes(): void {
    this._state.update(s => ({ ...s, activeNodes: s.activeNodes + 1 }));
  }

  public setProtocol(protocol: 'ALPHA' | 'BETA' | 'DELTA'): void {
    this._state.update(s => ({ ...s, securityProtocol: protocol }));
  }

  /* @section ArchitectureMap
   * Implementa o pattern 'Signal Store'.
   * Centraliza o estado da aplicação em um Single Source of Truth (SSoT).
   * Utiliza computed() para expor fatias do estado, garantindo que componentes 
   * reajam apenas ao que lhes interessa (Fine-grained Reactivity).
   */
}
