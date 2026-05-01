/**
 * @file atividade14.component.ts
 * @brief Atividade 14: O Scanner de Segurança (Custom Directives).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ScannerStatusDirective, SecurityLevel } from './directives/scanner-status.directive';

@Component({
  selector: 'app-atividade14',
  standalone: true,
  imports: [CommonModule, ScannerStatusDirective],
  templateUrl: './atividade14.component.html',
  styleUrl: './atividade14.component.css'
})
export class Atividade14Component {
  /**
   * @description Estado reativo do scanner.
   */
  protected readonly currentLevel = signal<SecurityLevel>('SAFE');

  /**
   * @brief Simula a alteração de níveis de segurança.
   */
  protected cycleSecurity(): void {
    const levels: SecurityLevel[] = ['SAFE', 'CAUTION', 'DANGER', 'BREACH'];
    const currentIndex = levels.indexOf(this.currentLevel());
    const nextIndex = (currentIndex + 1) % levels.length;
    this.currentLevel.set(levels[nextIndex]);
    
    console.log(`[SECURITY] Alerta alterado para: ${this.currentLevel()}`);
  }
}

/* @section ArchitectureMap
 * O componente gerencia apenas o estado reativo (currentLevel).
 * A lógica de renderização industrial, animação e eventos de DOM 
 * é delegada para a diretiva [appScannerStatus].
 */

/*
 * RESUMO TEÓRICO
 * Diretivas de Atributo permitem estender o comportamento de elementos HTML
 * existentes sem a necessidade de criar novos componentes (Wrapperless).
 * O uso de @HostBinding e @HostListener garante que a diretiva tenha controle 
 * total sobre o elemento onde ela é aplicada.
 */
