/**
 * @date 2026
 */
import { Component, HostListener, signal } from '@angular/core';
import { AlertModalComponent } from './components/alert-modal/alert-modal.component';

/**
 * @file atividade09.component.ts
 * @brief Componente da Atividade 09: Camadas e Atalhos.
 * @author Gemini CLI Elite
 * 
 * @description Demonstração de posicionamento CSS avançado, gestão de camadas (Z-index),
 * captura de eventos globais de teclado e comunicação bidirecional entre componentes.
 */

@Component({
  selector: 'app-atividade09',
  standalone: true,
  imports: [AlertModalComponent],
  templateUrl: './atividade09.component.html',
  styleUrl: './atividade09.component.css'
})
export class Atividade09Component {
  /**
   * @description Controle de estado da modal de alerta.
   */
  protected readonly isAlertOpen = signal<boolean>(false);

  /**
   * @description Histórico de logs operacionais.
   */
  protected readonly logs = signal<string[]>(['Sistema de Camadas Nexus v1.0 ONLINE.']);

  /**
   * @brief Atalhos de Teclado Industriais (Requisito de Elite).
   * Captura teclas globalmente no contexto do componente.
   */
  @HostListener('window:keydown', ['$event'])
  handleKeyDown(event: KeyboardEvent): void {
    const key = event.key.toLowerCase();

    // [A] para Alerta
    if (key === 'a') {
      this.isAlertOpen.set(true);
    }
    
    // [L] para Log Rápido
    if (key === 'l') {
      this.addLog('Log de campo disparado via atalho [L].');
    }

    // [ESC] para fechar é tratado nativamente pelo <dialog> e emitido pelo modal
  }

  protected addLog(message: string): void {
    const timestamp = new Date().toLocaleTimeString();
    this.logs.update(current => [`[${timestamp}] ${message}`, ...current]);
  }

  protected toggleAlert(state: boolean): void {
    this.isAlertOpen.set(state);
    if (!state) {
      this.addLog('Alerta de emergência reconhecido pelo operador.');
    }
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
