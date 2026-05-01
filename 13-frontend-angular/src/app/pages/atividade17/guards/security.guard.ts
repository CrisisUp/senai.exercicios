/**
 * @file security.guard.ts
 * @brief Guard de Rota Funcional para Proteção de Zonas Restritas.
 * @author Cristiano
 * @date 2026
 */

import { inject } from '@angular/core';
import { CanActivateFn, Router } from '@angular/router';
import { AuthMockService } from '../services/auth-mock.service';

/**
 * @brief Sentinela de Rota (Guard).
 * Impede o carregamento de componentes restritos se o operador não possuir 
 * o token de autorização ativo no AuthMockService.
 */
export const securityGuard: CanActivateFn = (route, state) => {
  const authService = inject(AuthMockService);
  const router = inject(Router);

  if (authService.checkCredentialSync()) {
    console.log(`[SENTINEL] Acesso autorizado para zona: ${state.url}`);
    return true;
  }

  console.warn(`[SENTINEL] TENTATIVA DE INVASÃO DETECTADA EM: ${state.url}. Redirecionando...`);
  
  // Redireciona para a página principal da atividade caso não esteja autorizado
  return router.parseUrl('/atividade17');
};

/* @section ArchitectureMap
 * Utiliza o padrão funcional (Injectable Guards estão deprecated).
 * O Guard atua como um filtro no pipeline de navegação do Router.
 */
