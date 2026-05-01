/**
 * @file vault.service.ts
 * @brief Serviço de Gestão de Estado Persistente (Patterns: State, Storage).
 * @author Cristiano
 * @date 2026
 */

import { Injectable, signal, effect } from '@angular/core';

export interface VaultKey {
  id: string;
  label: string;
  value: string;
  createdAt: string;
}

@Injectable({
  providedIn: 'root'
})
export class VaultService {
  private readonly STORAGE_KEY = 'NEXUS_VAULT_DATA';

  /**
   * @brief Estado reativo das chaves do cofre.
   * Inicializa a partir do LocalStorage caso existam dados prévios.
   */
  private readonly _keys = signal<VaultKey[]>(this.loadFromStorage());

  /**
   * @brief Exposição pública e protegida do estado.
   */
  public readonly keys = this._keys.asReadonly();

  constructor() {
    /**
     * @description Sincronização Automática (Persistent Effect).
     * Toda vez que o Signal _keys mudar, o effect persiste no LocalStorage.
     */
    effect(() => {
      localStorage.setItem(this.STORAGE_KEY, JSON.stringify(this._keys()));
      console.log("[VAULT] Estado sincronizado com o disco rígido local.");
    });
  }

  public addKey(label: string, value: string): void {
    const newKey: VaultKey = {
      id: Math.random().toString(36).substring(2, 9).toUpperCase(),
      label,
      value,
      createdAt: new Date().toLocaleString()
    };
    this._keys.update(current => [newKey, ...current]);
  }

  public removeKey(id: string): void {
    this._keys.update(current => current.filter(k => k.id !== id));
  }

  public clearVault(): void {
    this._keys.set([]);
  }

  private loadFromStorage(): VaultKey[] {
    const data = localStorage.getItem(this.STORAGE_KEY);
    return data ? JSON.parse(data) : [];
  }
}

/* @section ArchitectureMap
 * Implementa o pattern 'State Synchronization'.
 * O uso de effect() dentro do serviço garante que a persistência seja um 
 * efeito colateral transparente da mutação do estado reativo.
 */
