/**
 * @file auth.interceptor.ts
 * @brief Interceptor Funcional para Segurança e Auditoria de Protocolos.
 * @author Cristiano
 * @date 2026
 */

import { HttpInterceptorFn, HttpRequest, HttpHandlerFn, HttpEvent, HttpResponse } from '@angular/common/http';
import { tap, finalize } from 'rxjs';

/**
 * @brief Interceptor de Escolta (Security & Audit).
 * Adiciona tokens de autorização e rastreia o tempo de resposta das APIs Nexus.
 */
export const authInterceptor: HttpInterceptorFn = (req: HttpRequest<unknown>, next: HttpHandlerFn) => {
  const startTime = Date.now();
  const authToken = 'NEXUS-ELITE-SECURE-TOKEN-2026';

  /**
   * @description Clonagem da requisição para inclusão de headers de segurança (Imutabilidade).
   */
  const secureReq = req.clone({
    setHeaders: {
      'Authorization': `Bearer ${authToken}`,
      'X-Nexus-Audit': 'ACTIVE'
    }
  });

  console.log(`[HTTP AUDIT] Outgoing Request: ${req.method} ${req.url}`);

  return next(secureReq).pipe(
    tap({
      next: (event: HttpEvent<unknown>) => {
        if (event instanceof HttpResponse) {
          const elapsed = Date.now() - startTime;
          console.log(`[HTTP AUDIT] Response Received: ${req.url} | Latency: ${elapsed}ms`);
        }
      },
      error: (error) => {
        console.error(`[HTTP AUDIT] CRITICAL FAILURE: ${req.url}`, error);
      }
    }),
    finalize(() => {
      // Lógica de encerramento de monitoramento
    })
  );
};

/* @section ArchitectureMap
 * Implementa o pattern 'Chain of Responsibility'.
 * O Interceptor intercepta a requisição, injeta segurança e monitora a resposta
 * de forma transparente para os serviços consumidores.
 */
