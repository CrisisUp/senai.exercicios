import { Component, signal, computed } from '@angular/core';
import { FormsModule } from '@angular/forms';

/**
 * @file atividade05.component.ts
 * @brief Componente da Atividade 05: Inteligência e Flexibilidade.
 * @author Gemini CLI Elite
 * @date 2026-04-30
 * 
 * @description Demonstração de formulários, Flexbox e lógica condicional reativa
 * utilizando Signals e a nova Control Flow Syntax do Angular v21.
 */

@Component({
  selector: 'app-atividade05',
  standalone: true,
  imports: [FormsModule],
  templateUrl: './atividade05.component.html',
  styleUrl: './atividade05.component.css'
})
export class Atividade05Component {
  /**
   * @description Estados reativos via Signals.
   */
  protected readonly callsign = signal<string>('SKY-RAPTOR');
  protected readonly tempCallsign = signal<string>('');
  protected readonly battery = signal<number>(100);

  /**
   * @description Lógica Condicional Computada (Requisito de Elite).
   */
  protected readonly isCritical = computed(() => this.battery() < 20);

  /**
   * @brief Atualiza o registro oficial do drone (Callsign).
   */
  protected updateCallsign(): void {
    if (this.tempCallsign().trim()) {
      this.callsign.set(this.tempCallsign().toUpperCase());
      this.tempCallsign.set('');
    }
  }

  /**
   * @brief Gerenciamento de Carga com limites de segurança.
   */
  protected modifyBattery(amount: number): void {
    this.battery.update(current => {
      const next = current + amount;
      return Math.min(Math.max(next, 0), 100);
    });
  }

  /**
   * @brief Handler para o input de texto do formulário.
   */
  protected onInputChange(event: Event): void {
    const input = event.target as HTMLInputElement;
    this.tempCallsign.set(input.value);
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
