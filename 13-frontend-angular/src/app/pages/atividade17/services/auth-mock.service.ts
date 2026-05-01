/**
 * @file auth-mock.service.ts
 * @brief Serviço de Autenticação Mock para Validação de Acesso.
 * @author Cristiano
 * @date 2026
 */

import { Injectable, signal } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class AuthMockService {
  /**
   * @brief Estado de autenticação global.
   */
  private readonly _isAuthenticated = signal<boolean>(false);
  public readonly isAuthenticated = this._isAuthenticated.asReadonly();

  /**
   * @brief Alterna o estado de acesso (Simulação Industrial).
   */
  public toggleAccess(): void {
    this._isAuthenticated.update(state => !state);
    console.log(`[AUTH] Acesso de Nível 3: ${this._isAuthenticated() ? 'CONCEDIDO' : 'REVOGADO'}`);
  }

  /**
   * @brief Verifica credenciais de forma síncrona.
   */
  public checkCredentialSync(): boolean {
    return this._isAuthenticated();
  }
}

/* @section ArchitectureMap
 * Singleton Service que atua como 'Source of Truth' para o estado 
 * de autorização da sessão Nexus.
 */
