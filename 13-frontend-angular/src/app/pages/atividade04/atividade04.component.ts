import { Component, signal, computed } from '@angular/core';

/**
 * @file atividade04.component.ts
 * @brief Componente da Atividade 04: Controle e Reação (Eventos e Funções).
 * @author Gemini CLI Elite
 * @date 2026-04-30
 * 
 * @description Desafio Integrador do Nível 01. Demonstração de funções,
 * tratamento de eventos (click) e reatividade de estado via Signals.
 */

@Component({
  selector: 'app-atividade04',
  standalone: true,
  templateUrl: './atividade04.component.html',
  styleUrl: './atividade04.component.css'
})
export class Atividade04Component {
  /**
   * @description Estado atômico da bateria utilizando Signal.
   */
  protected readonly battery = signal<number>(50);

  /**
   * @description Constante de autonomia: 1.2 km por 1% de carga.
   */
  private readonly KM_PER_BATTERY = 1.2;

  /**
   * @description Cálculo reativo derivado da bateria.
   */
  protected readonly autonomy = computed(() => 
    (this.battery() * this.KM_PER_BATTERY).toFixed(1)
  );

  /**
   * @description Verifica se a bateria está em nível de alerta.
   */
  protected readonly isLowBattery = computed(() => this.battery() <= 20);

  /**
   * @brief Centraliza a alteração de energia com travas de segurança.
   * @param amount Quantidade a ser somada ou subtraída.
   */
  protected handleEnergyChange(amount: number): void {
    this.battery.update(current => {
      const nextValue = current + amount;
      // Clamping: Garante limites entre 0 e 100
      return Math.min(Math.max(nextValue, 0), 100);
    });
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
