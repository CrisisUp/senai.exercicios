/**
 * @file platform.service.ts
 * @brief Serviço de Detecção de Plataforma (Isomorphic Logic).
 * @author Cristiano
 * @date 2026
 */

import { Injectable, inject, PLATFORM_ID } from '@angular/core';
import { isPlatformBrowser, isPlatformServer } from '@angular/common';

@Injectable({
  providedIn: 'root'
})
export class PlatformService {
  private readonly platformId = inject(PLATFORM_ID);

  /**
   * @brief Verifica se o código está rodando no Navegador.
   */
  public isBrowser(): boolean {
    return isPlatformBrowser(this.platformId);
  }

  /**
   * @brief Verifica se o código está rodando no Servidor (SSR).
   */
  public isServer(): boolean {
    return isPlatformServer(this.platformId);
  }

  /**
   * @brief Retorna o nome do ambiente atual.
   */
  public getEnvironmentName(): string {
    if (this.isBrowser()) return 'BROWSER (CLIENT)';
    if (this.isServer()) return 'NODE.JS (SERVER)';
    return 'UNKNOWN';
  }
}

/* @section ArchitectureMap
 * Implementa lógica isomórfica (Universal).
 * O uso de PLATFORM_ID permite que o Angular execute código de forma segura 
 * tanto no servidor quanto no cliente, evitando erros de 'window is not defined' 
 * durante o processo de SSR.
 */
