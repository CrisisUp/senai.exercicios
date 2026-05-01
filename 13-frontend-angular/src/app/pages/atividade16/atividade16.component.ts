/**
 * @file atividade16.component.ts
 * @brief Atividade 16: O Protocolo de Escolta (HTTP Interceptors).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HttpClient } from '@angular/common/http';
import { catchError, of } from 'rxjs';

@Component({
  selector: 'app-atividade16',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade16.component.html',
  styleUrl: './atividade16.component.css'
})
export class Atividade16Component {
  private readonly http = inject(HttpClient);

  protected readonly requestStatus = signal<'IDLE' | 'LOADING' | 'SUCCESS' | 'ERROR'>('IDLE');
  protected readonly auditLogs = signal<string[]>([]);
  protected readonly responseData = signal<any>(null);

  /**
   * @brief Dispara uma requisição protegida para simular a auditoria.
   */
  protected executeSecureRequest(): void {
    this.requestStatus.set('LOADING');
    this.addAuditLog('Disparando requisição tática...');

    // Usando JSONPlaceholder como mock industrial
    this.http.get('https://jsonplaceholder.typicode.com/posts/1').pipe(
      catchError(err => {
        this.requestStatus.set('ERROR');
        this.addAuditLog(`FALHA NA CONEXÃO: ${err.message}`);
        return of(null);
      })
    ).subscribe(data => {
      if (data) {
        this.responseData.set(data);
        this.requestStatus.set('SUCCESS');
        this.addAuditLog('Protocolo de resposta concluído com sucesso.');
      }
    });
  }

  private addAuditLog(msg: string): void {
    const time = new Date().toLocaleTimeString();
    this.auditLogs.update(logs => [`[${time}] ${msg}`, ...logs]);
  }
}

/* @section ArchitectureMap
 * O componente não injeta headers nem faz logging de tempo.
 * Ele apenas consome o HttpClient. O Interceptor age nos bastidores,
 * garantindo conformidade de segurança e performance em todas as chamadas.
 */

/*
 * RESUMO TEÓRICO
 * Interceptors são middleware para requisições HTTP. No Angular moderno, 
 * eles são funções puras que permitem a "Aspect-Oriented Programming" (AOP), 
 * tratando preocupações transversais (Segurança, Logging, Caching) em um único lugar.
 */
