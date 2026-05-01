/**
 * @file atividade11.component.ts
 * @brief Atividade 11: O Pulso da Rede (RxJS & Lifecycle Hooks).
 * @author Cristiano
 * @date 2026
 */

import { Component, OnInit, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { interval, map, filter, scan, tap, Observable } from 'rxjs';
import { toSignal } from '@angular/core/rxjs-interop';

/**
 * @description Introdução ao Nível 11 (Arquiteto).
 * Foco: Sincronização de fluxos assíncronos RxJS com o sistema de Signals do Angular.
 * Implementa um monitor de pulso (heartbeat) com filtragem de ruído e acumulação de histórico.
 */

interface Heartbeat {
  timestamp: string;
  latency: number;
  status: 'ONLINE' | 'WARNING' | 'CONNECTING';
}

@Component({
  selector: 'app-atividade11',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade11.component.html',
  styleUrl: './atividade11.component.css'
})
export class Atividade11Component implements OnInit {
  /**
   * @brief Fluxo de Pulso Refinado (Pipeline RxJS).
   */
  private readonly heartbeat$: Observable<Heartbeat> = interval(2000).pipe(
    map(() => ({
      timestamp: new Date().toLocaleTimeString(),
      latency: Math.floor(Math.random() * 60) + 5, // 5-65ms
      status: 'ONLINE' as const
    })),
    filter(beat => beat.latency <= 55),
    tap(beat => console.log(`[NETWORK] Batimento recebido: ${beat.latency}ms`))
  );

  /**
   * @brief Interoperabilidade RxJS -> Signal.
   */
  protected readonly pulse = toSignal(this.heartbeat$, {
    initialValue: { timestamp: '--:--:--', latency: 0, status: 'CONNECTING' as const }
  });

  /**
   * @brief Acumulador de Histórico via RxJS.
   */
  protected readonly history = toSignal(
    this.heartbeat$.pipe(
      scan((acc, curr) => [curr, ...acc].slice(0, 5), [] as Heartbeat[])
    ),
    { initialValue: [] as Heartbeat[] }
  );

  ngOnInit(): void {
    console.log("[NEXUS ARCHITECT] Monitor de Pulso Avançado ONLINE.");
  }

  /* @section ArchitectureMap
   * O pipeline RxJS processa os dados (Filtragem e Acumulação) ANTES de chegar no Signal.
   */
}

/*
 * RESUMO TEÓRICO
 * Operadores RxJS como filter() e scan() permitem processar fluxos de dados complexos 
 * de forma declarativa. No Angular moderno, preferimos tratar a lógica no stream
 * e apenas consumir o resultado final via Signals, otimizando o ciclo de detecção de mudanças.
 */
