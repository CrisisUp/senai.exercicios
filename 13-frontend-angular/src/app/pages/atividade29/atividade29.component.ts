/**
 * @file atividade29.component.ts
 * @brief Atividade 29: A Coreografia de Silício (Web Animations API).
 * @author Cristiano
 * @date 2026
 */

import { Component, ElementRef, ViewChild, signal } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-atividade29',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade29.component.html',
  styleUrl: './atividade29.component.css'
})
export class Atividade29Component {
  @ViewChild('deployUnit') unitRef!: ElementRef<HTMLElement>;

  protected readonly isDeployed = signal<boolean>(false);
  protected readonly isPulsing = signal<boolean>(false);
  private currentAnimation: Animation | null = null;

  /**
   * @brief Executa o protocolo de implantação (Deployment).
   * Utiliza a Web Animations API para controle preciso de timing e easing.
   */
  protected toggleDeployment(): void {
    const el = this.unitRef.nativeElement;
    const newState = !this.isDeployed();
    
    // Keyframes para a transição de estado
    const keyframes = newState 
      ? [
          { transform: 'scale(0.5) rotate(0deg)', opacity: 0, borderRadius: '50%' },
          { transform: 'scale(1.1) rotate(180deg)', opacity: 1, borderRadius: '12px' },
          { transform: 'scale(1) rotate(180deg)', opacity: 1, borderRadius: '8px' }
        ]
      : [
          { transform: 'scale(1) rotate(180deg)', opacity: 1, borderRadius: '8px' },
          { transform: 'scale(1.2) rotate(90deg)', opacity: 0.5, borderRadius: '20%' },
          { transform: 'scale(0) rotate(0deg)', opacity: 0, borderRadius: '50%' }
        ];

    const animation = el.animate(keyframes, {
      duration: 800,
      easing: 'cubic-bezier(0.175, 0.885, 0.32, 1.275)',
      fill: 'forwards'
    });

    animation.onfinish = () => {
      this.isDeployed.set(newState);
      console.log(`%c[WAAPI] Protocolo de ${newState ? 'Implantação' : 'Recolhimento'} concluído.`, 'color: #58a6ff');
    };
  }

  /**
   * @brief Ativa o modo de alerta (Pulse).
   * Demonstra o controle programático de iterações e cancelamento.
   */
  protected togglePulse(): void {
    if (this.currentAnimation) {
      this.currentAnimation.cancel();
      this.currentAnimation = null;
      this.isPulsing.set(false);
      return;
    }

    const el = this.unitRef.nativeElement;
    this.isPulsing.set(true);

    this.currentAnimation = el.animate([
      { boxShadow: '0 0 0px #f85149', borderColor: '#30363d' },
      { boxShadow: '0 0 30px #f85149', borderColor: '#f85149' },
      { boxShadow: '0 0 0px #f85149', borderColor: '#30363d' }
    ], {
      duration: 1000,
      iterations: Infinity
    });
  }

  /* @section ArchitectureMap
   * Integração Angular-WAAPI:
   * ViewChild -> Captura a referência nativa do elemento.
   * animate() -> Dispara animações aceleradas por hardware (GPU).
   * Animation Object -> Permite controle de fluxo (play, pause, cancel, finish).
   */
}

/*
 * RESUMO TEÓRICO
 * Web Animations API (WAAPI) é o motor nativo de animação dos navegadores modernos.
 * Ela combina o poder das animações CSS (performance) com a flexibilidade do 
 * JavaScript (lógica sequencial, callbacks, sincronização dinâmica). 
 * É a ferramenta ideal para interfaces industriais que reagem a estados complexos
 * de hardware ou telemetria.
 */
