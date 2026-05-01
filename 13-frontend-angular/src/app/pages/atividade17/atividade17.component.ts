/**
 * @file atividade17.component.ts
 * @brief Atividade 17: A Sentinela de Acesso (Route Guards).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule } from '@angular/router';
import { AuthMockService } from './services/auth-mock.service';

@Component({
  selector: 'app-atividade17',
  standalone: true,
  imports: [CommonModule, RouterModule],
  templateUrl: './atividade17.component.html',
  styleUrl: './atividade17.component.css'
})
export class Atividade17Component {
  protected readonly authService = inject(AuthMockService);

  protected toggleLogin(): void {
    this.authService.toggleAccess();
  }
}

/* @section ArchitectureMap
 * Componente de controle para demonstração de guards.
 * O estado de autenticação via AuthMockService determina se o Guard
 * permitirá a navegação para a sub-rota '/atividade17/restricted'.
 */

/*
 * RESUMO TEÓRICO
 * Guards de Rota (CanActivate, CanMatch) são fundamentais para segurança no lado do cliente.
 * Eles permitem interceptar o processo de navegação e decidir se o usuário pode carregar
 * ou visualizar uma determinada rota baseando-se em lógica de negócio assíncrona ou síncrona.
 */
