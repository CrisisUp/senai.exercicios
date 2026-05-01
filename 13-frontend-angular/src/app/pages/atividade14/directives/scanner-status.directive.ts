/**
 * @file scanner-status.directive.ts
 * @brief Diretiva de Atributo Customizada para Status de Scanner.
 * @author Cristiano
 * @date 2026
 */

import { Directive, ElementRef, HostBinding, HostListener, input, effect } from '@angular/core';

export type SecurityLevel = 'SAFE' | 'CAUTION' | 'DANGER' | 'BREACH';

@Directive({
  selector: '[appScannerStatus]',
  standalone: true
})
export class ScannerStatusDirective {
  /**
   * @brief Input reativo (Signal) para o nível de segurança.
   */
  level = input<SecurityLevel>('SAFE');

  /**
   * @brief HostBinding para manipular classes CSS do elemento hospedeiro.
   */
  @HostBinding('class.scanner-active') isActive = false;

  constructor(private el: ElementRef) {
    /**
     * @description Reage a mudanças no nível de segurança via Signal Effect.
     */
    effect(() => {
      this.applyIndustrialStyle(this.level());
    });
  }

  /**
   * @brief Captura eventos do mouse para feedback tátil de interface.
   */
  @HostListener('mouseenter')
  onMouseEnter(): void {
    this.isActive = true;
    this.el.nativeElement.style.transform = 'scale(1.02)';
  }

  @HostListener('mouseleave')
  onMouseLeave(): void {
    this.isActive = false;
    this.el.nativeElement.style.transform = 'scale(1)';
  }

  private applyIndustrialStyle(level: SecurityLevel): void {
    const native = this.el.nativeElement;
    
    // Reset de estilos base
    native.style.transition = 'all 0.4s cubic-bezier(0.175, 0.885, 0.32, 1.275)';
    native.style.borderLeft = '4px solid transparent';

    switch (level) {
      case 'SAFE':
        native.style.borderColor = '#238636';
        native.style.backgroundColor = 'rgba(35, 134, 54, 0.05)';
        break;
      case 'CAUTION':
        native.style.borderColor = '#d29922';
        native.style.backgroundColor = 'rgba(210, 153, 34, 0.05)';
        break;
      case 'DANGER':
        native.style.borderColor = '#f85149';
        native.style.backgroundColor = 'rgba(248, 81, 73, 0.05)';
        break;
      case 'BREACH':
        native.style.borderColor = '#ab7df8';
        native.style.backgroundColor = 'rgba(171, 125, 248, 0.1)';
        native.classList.add('glitch-effect');
        break;
    }
  }
}

/* @section ArchitectureMap
 * Implementa padrão 'Decorator' via Diretiva de Atributo.
 * Utiliza @HostBinding e @HostListener para encapsular comportamento visual
 * e interativo sem poluir o componente principal.
 */
