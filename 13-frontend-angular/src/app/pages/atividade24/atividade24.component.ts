/**
 * @file atividade24.component.ts
 * @brief Atividade 24: O Processador Paralelo (Multithreading com Web Workers).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal, OnDestroy } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-atividade24',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade24.component.html',
  styleUrl: './atividade24.component.css'
})
export class Atividade24Component implements OnDestroy {
  private worker: Worker | null = null;

  // Estados Reativos
  protected readonly isProcessing = signal<boolean>(false);
  protected readonly progress = signal<number>(0);
  protected readonly result = signal<any>(null);
  protected readonly uiCounter = signal<number>(0);

  constructor() {
    this.startUiMonitor();
  }

  /**
   * @brief Inicia o processamento pesado em segundo plano.
   */
  protected startHeavyTask(): void {
    if (typeof Worker !== 'undefined') {
      this.isProcessing.set(true);
      this.progress.set(0);
      this.result.set(null);

      // Instanciação do Worker usando o padrão moderno do Angular
      this.worker = new Worker(new URL('./worker/routing.worker', import.meta.url));

      this.worker.onmessage = ({ data }) => {
        if (data.type === 'PROGRESS') {
          this.progress.set(data.value);
        } else if (data.type === 'RESULT') {
          this.result.set(data);
          this.isProcessing.set(false);
          this.worker?.terminate();
        }
      };

      this.worker.onerror = (err) => {
        console.error('[NEXUS ERROR] Falha no thread do Worker:', err);
        this.isProcessing.set(false);
      };

      this.worker.postMessage({ complexity: 200000000 }); // 200 milhões de iterações
    } else {
      console.warn('[NEXUS] Web Workers não suportados neste ambiente.');
    }
  }

  /**
   * @brief Contador simples para provar que a UI continua fluida.
   */
  private startUiMonitor(): void {
    setInterval(() => {
      this.uiCounter.update(c => c + 1);
    }, 100);
  }

  ngOnDestroy(): void {
    this.worker?.terminate();
  }

  /* @section ArchitectureMap
   * Implementa o padrão de 'Offloading'.
   * Main Thread (Angular) -> Gerencia UI e Reatividade.
   * Background Thread (Worker) -> Executa algoritmos CPU-Intensive.
   * A comunicação ocorre via mensagens (postMessage), garantindo isolamento total de memória.
   */
}

/*
 * RESUMO TEÓRICO
 * Web Workers permitem a execução de scripts em threads separadas do thread principal 
 * da UI. Isso é crucial para aplicações de Engenharia que processam telemetria, 
 * criptografia ou cálculos geométricos complexos, evitando o temido "freeze" da interface
 * e garantindo uma experiência de usuário (UX) de 60 FPS constante.
 */
