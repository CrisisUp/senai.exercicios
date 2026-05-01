/**
 * @file atividade34.component.ts
 * @brief Atividade 34: O Espelho de Prata (SSR & Client Hydration).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, signal, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PlatformService } from './services/platform.service';

@Component({
  selector: 'app-atividade34',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade34.component.html',
  styleUrl: './atividade34.component.css'
})
export class Atividade34Component implements OnInit {
  private readonly platform = inject(PlatformService);

  // Estados de Renderização
  protected readonly currentPlatform = signal<string>('DETECTANDO...');
  protected readonly isHydrated = signal<boolean>(false);
  protected readonly serverTimestamp = signal<string>('N/A');

  ngOnInit(): void {
    this.currentPlatform.set(this.platform.getEnvironmentName());

    if (this.platform.isBrowser()) {
      // No Browser, simulamos a conclusão da hidratação
      setTimeout(() => {
        this.isHydrated.set(true);
        console.log('[HYDRATION] DOM Reutilizado com sucesso pelo Angular.');
      }, 1000);
    } else {
      // No Servidor, gravaríamos o timestamp da geração do HTML
      this.serverTimestamp.set(new Date().toISOString());
    }
  }

  /* @section ArchitectureMap
   * Implementa o conceito de 'Client-side Hydration'.
   * O Servidor (SSR) gera o HTML estático para First Contentful Paint (LCP).
   * O Cliente (Angular) recebe o HTML e "hidrata" os eventos e o estado reativo 
   * sem destruir o DOM existente, garantindo performance e SEO de Elite.
   */
}

/*
 * RESUMO TEÓRICO
 * SSR (Server-Side Rendering) resolve o problema de Single Page Applications (SPA) 
 * invisíveis para crawlers de busca. A Hidratação (Hydration) é o processo onde 
 * o Angular no navegador assume o controle do HTML pré-renderizado, tornando-o 
 * interativo de forma suave, sem o "pulo" visual de recarregamento.
 */
