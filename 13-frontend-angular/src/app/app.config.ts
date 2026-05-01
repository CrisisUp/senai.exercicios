/**
 * @file app.config.ts
 * @brief Configuração Global da Aplicação com HttpClient e Interceptors.
 * @author Cristiano
 * @date 2026
 */
import { ApplicationConfig, provideBrowserGlobalErrorListeners } from '@angular/core';
import { provideRouter } from '@angular/router';
import { provideHttpClient, withInterceptors } from '@angular/common/http';
import { authInterceptor } from './pages/atividade16/interceptors/auth.interceptor';

import { routes } from './app.routes';

export const appConfig: ApplicationConfig = {
  providers: [
    provideBrowserGlobalErrorListeners(),
    provideRouter(routes),
    provideHttpClient(
      withInterceptors([authInterceptor])
    )
  ]
};

/* @section ArchitectureMap
 * Configura o pipeline de infraestrutura global.
 * O HttpClient é configurado com interceptores funcionais, padrão moderno do Angular 18+.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
