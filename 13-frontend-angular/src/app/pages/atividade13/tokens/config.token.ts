/**
 * @file config.token.ts
 * @brief Definição de Injection Tokens para configuração industrial.
 * @author Cristiano
 * @date 2026
 */

import { InjectionToken } from '@angular/core';

export interface AppConfig {
  apiUrl: string;
  retryAttempts: number;
  enableEncryption: boolean;
}

/**
 * @brief Token de Configuração Global.
 * Utilizado para injetar configurações que não mudam durante o runtime,
 * mas podem variar dependendo do ambiente (dev/prod).
 */
export const APP_CONFIG = new InjectionToken<AppConfig>('app.config');

/**
 * @brief Token de Versão do Sistema.
 * Exemplo simples de injeção de valor primitivo.
 */
export const SYSTEM_VERSION = new InjectionToken<string>('system.version');
