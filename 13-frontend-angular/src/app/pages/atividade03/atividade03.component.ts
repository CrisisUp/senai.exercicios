import { Component, signal, computed } from '@angular/core';
import { FormsModule } from '@angular/forms';

/**
 * @file atividade03.component.ts
 * @brief Componente da Atividade 03: Geometria e Lógica.
 * @author Gemini CLI Elite
 * @date 2026-04-30
 * 
 * @description Demonstração de Box Model, cálculos matemáticos reativos
 * utilizando Signals e `computed` do Angular v21.
 */

@Component({
  selector: 'app-atividade03',
  standalone: true,
  imports: [FormsModule],
  templateUrl: './atividade03.component.html',
  styleUrl: './atividade03.component.css'
})
export class Atividade03Component {
  /**
   * @description Estado reativo da bateria (0-100%).
   */
  protected readonly battery = signal<number>(85);

  /**
   * @description Constante de autonomia (Requisito: Bateria * 1.5 km).
   */
  private readonly rangeMultiplier = 1.5;

  /**
   * @description Sinal computado que deriva a autonomia da bateria.
   * Reage automaticamente às mudanças no sinal `battery`.
   */
  protected readonly range = computed(() => 
    (this.battery() * this.rangeMultiplier).toFixed(2)
  );

  /**
   * @description Atualiza o estado da bateria a partir do input do usuário.
   */
  protected onBatteryChange(event: Event): void {
    const input = event.target as HTMLInputElement;
    this.battery.set(Number(input.value));
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
