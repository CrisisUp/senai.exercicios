/**
 * @file atividade25.component.ts
 * @brief Atividade 25: O Elo de Tempo Real (WebSockets e Telemetria).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, signal, OnDestroy } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TelemetryService, TelemetryPacket } from './services/telemetry.service';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-atividade25',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade25.component.html',
  styleUrl: './atividade25.component.css'
})
export class Atividade25Component implements OnDestroy {
  private readonly telemetryService = inject(TelemetryService);
  private subscription: Subscription | null = null;

  // Estados Reativos
  protected readonly connectionStatus = this.telemetryService.connectionStatus;
  protected readonly packets = signal<TelemetryPacket[]>([]);
  protected readonly lastUpdate = signal<string>('NEVER');

  /**
   * @brief Inicia a escuta do túnel de dados.
   */
  protected connectToNexus(): void {
    if (this.subscription) return;

    this.subscription = this.telemetryService.connect().subscribe({
      next: (packet) => {
        this.packets.update(list => [packet, ...list].slice(0, 10));
        this.lastUpdate.set(new Date().toLocaleTimeString());
      },
      error: (err) => console.error('[WS ERROR]', err)
    });
  }

  /**
   * @brief Encerra o link de comunicação.
   */
  protected disconnect(): void {
    this.telemetryService.disconnect();
    this.subscription?.unsubscribe();
    this.subscription = null;
  }

  /**
   * @brief Envia comando de teste para o servidor.
   */
  protected pingSatellite(): void {
    this.telemetryService.sendCommand('PING_REQUEST');
  }

  ngOnDestroy(): void {
    this.disconnect();
  }

  /* @section ArchitectureMap
   * O componente atua como um 'Subscriber' do fluxo de dados WebSocket.
   * Utiliza RxJS para gerenciar o ciclo de vida da conexão e Signals
   * para refletir os pacotes de telemetria na interface de forma instantânea.
   */
}

/*
 * RESUMO TEÓRICO
 * WebSockets fornecem um canal de comunicação persistente, bidirecional e 
 * full-duplex sobre TCP. É a tecnologia de escolha para aplicações que exigem 
 * baixa latência e atualizações em tempo real (Real-Time Apps), como dashboards 
 * financeiros, sistemas de chat e consoles de comando industrial.
 */
