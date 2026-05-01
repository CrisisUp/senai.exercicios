/**
 * @date 2026
 */
import { Component, ElementRef, effect, input, output, viewChild } from '@angular/core';

/**
 * @file alert-modal.component.ts
 * @brief Componente de Alerta (Design Pattern: Modal Overlay).
 * @author Gemini CLI Elite
 * 
 * @description Utiliza a API nativa de <dialog> do HTML5 e a nova API de 
 * outputs baseada em Signals do Angular v21.
 */

@Component({
  selector: 'app-alert-modal',
  standalone: true,
  template: `
    <dialog 
      #dialogElement
      (cancel)="onClose()" 
      class="modal"
    >
      <div class="modal-content">
        <h2>🚨 ALERTA DE EMERGÊNCIA</h2>
        <p>{{ message() }}</p>
        <div class="modal-actions">
          <button (click)="onClose()" class="btn-confirm">
            CONFIRMAR CIÊNCIA [ESC]
          </button>
        </div>
      </div>
    </dialog>
  `,
  styles: [`
    .modal {
      border: none;
      border-radius: 12px;
      padding: 0;
      background-color: #161b22;
      color: #c9d1d9;
      box-shadow: 0 0 30px rgba(248, 81, 73, 0.5);
      max-width: 400px;
    }

    /* Estilização do Backdrop (Natividade de Elite) */
    .modal::backdrop {
      background-color: rgba(0, 0, 0, 0.8);
      backdrop-filter: blur(4px);
    }

    .modal-content {
      padding: 2rem;
      border: 1px solid #f85149;
      border-radius: 12px;
    }

    h2 {
      color: #f85149;
      margin-top: 0;
      font-size: 1.2rem;
    }

    .modal-actions {
      margin-top: 2rem;
      display: flex;
      justify-content: flex-end;
    }

    .btn-confirm {
      background-color: #f85149;
      color: white;
      border: none;
      padding: 0.75rem 1.5rem;
      border-radius: 6px;
      font-weight: bold;
      cursor: pointer;
      transition: filter 0.2s;
    }

    .btn-confirm:hover {
      filter: brightness(1.2);
    }
  `]
})
export class AlertModalComponent {
  /**
   * @description Mensagem customizada via Input Signal.
   */
  message = input.required<string>();

  /**
   * @description Controle de visibilidade via Input Signal.
   */
  isOpen = input<boolean>(false);

  /**
   * @description Evento de fechamento via Output Signal.
   */
  close = output<void>();

  /**
   * @description Referência para o elemento <dialog> nativo.
   */
  private dialog = viewChild<ElementRef<HTMLDialogElement>>('dialogElement');

  constructor() {
    /**
     * @brief Reage às mudanças do sinal 'isOpen' para abrir/fechar o modal.
     */
    effect(() => {
      const dialogEl = this.dialog()?.nativeElement;
      if (dialogEl) {
        if (this.isOpen()) {
          dialogEl.showModal();
        } else {
          dialogEl.close();
        }
      }
    });
  }

  protected onClose(): void {
    this.close.emit();
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
