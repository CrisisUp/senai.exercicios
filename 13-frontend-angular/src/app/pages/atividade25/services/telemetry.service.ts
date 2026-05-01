/**
 * @file telemetry.service.ts
 * @brief Serviço de Telemetria via Simulação de WebSocket (Full-Duplex).
 * @author Cristiano
 * @date 2026
 */

import { Injectable, signal } from '@angular/core';
import { Subject, Observable, interval, map, takeUntil, finalize } from 'rxjs';

export interface TelemetryPacket {
  id: string;
  source: string;
  payload: number;
  timestamp: string;
}

@Injectable({
  providedIn: 'root'
})
export class TelemetryService {
  /**
   * @brief Estado da conexão (Simulado).
   */
  public readonly connectionStatus = signal<'DISCONNECTED' | 'CONNECTING' | 'CONNECTED'>('DISCONNECTED');
  
  private socket$ = new Subject<TelemetryPacket>();
  private disconnect$ = new Subject<void>();

  /**
   * @brief Inicia a conexão simulada (Protocolo WS://).
   */
  public connect(): Observable<TelemetryPacket> {
    this.connectionStatus.set('CONNECTING');
    
    // Simula delay de handshake de rede
    setTimeout(() => {
      this.connectionStatus.set('CONNECTED');
      this.startHeartbeat();
    }, 1500);

    return this.socket$.asObservable().pipe(
      takeUntil(this.disconnect$),
      finalize(() => this.connectionStatus.set('DISCONNECTED'))
    );
  }

  /**
   * @brief Envia comando para o "satélite" (Downlink).
   */
  public sendCommand(cmd: string): void {
    if (this.connectionStatus() === 'CONNECTED') {
      console.log(`[WS UPLINK] Enviando comando: ${cmd}`);
      // Simula uma resposta do servidor baseada no comando
      this.socket$.next({
        id: 'ACK-' + Math.random().toString(36).substr(2, 5),
        source: 'GROUND_CONTROL',
        payload: 100,
        timestamp: new Date().toLocaleTimeString()
      });
    }
  }

  public disconnect(): void {
    this.disconnect$.next();
    this.connectionStatus.set('DISCONNECTED');
    console.log('[WS] Conexão encerrada pelo operador.');
  }

  private startHeartbeat(): void {
    interval(2000).pipe(
      takeUntil(this.disconnect$),
      map(() => ({
        id: 'PKT-' + Math.random().toString(36).substr(2, 5),
        source: 'SATELLITE_NEXUS_I',
        payload: Math.floor(Math.random() * 1000) / 10,
        timestamp: new Date().toLocaleTimeString()
      }))
    ).subscribe(packet => this.socket$.next(packet));
  }
}

/* @section ArchitectureMap
 * Implementa o padrão 'Observer' sobre um túnel de comunicação simulado.
 * O Subject socket$ atua como o buffer de entrada de pacotes (Downlink), 
 * enquanto o método sendCommand simula o envio de dados (Uplink).
 */
