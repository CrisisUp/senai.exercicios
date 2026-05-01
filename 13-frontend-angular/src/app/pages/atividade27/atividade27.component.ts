/**
 * @file atividade27.component.ts
 * @brief Atividade 27: O Auditor de Métodos (Custom Decorators).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Audit } from './decorators/audit.decorator';

@Component({
  selector: 'app-atividade27',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade27.component.html',
  styleUrl: './atividade27.component.css'
})
export class Atividade27Component {
  protected readonly logHistory = signal<string[]>([]);

  /**
   * @brief Simula um disparo de míssil interceptado pelo auditor.
   */
  @Audit()
  protected fireTacticalMissile(targetId: string, coordinate: {x: number, y: number}): void {
    const msg = `Míssil disparado contra alvo ${targetId} em [${coordinate.x}, ${coordinate.y}]`;
    this.addLog(msg);
  }

  /**
   * @brief Simula uma autorização de acesso interceptada.
   */
  @Audit()
  protected authorizePersonnel(name: string, level: number): boolean {
    const msg = `Acesso nível ${level} autorizado para o operador: ${name}`;
    this.addLog(msg);
    return true;
  }

  /**
   * @brief Simula um cálculo de criptografia pesado.
   */
  @Audit()
  protected generateEncryptionKey(bits: number): string {
    // Simula processamento
    let sum = 0;
    for (let i = 0; i < 1000000; i++) {
      sum += Math.sqrt(i);
    }
    const key = `KEY-${Math.random().toString(36).substr(2, 9).toUpperCase()}`;
    this.addLog(`Nova chave de ${bits} bits gerada.`);
    return key;
  }

  private addLog(msg: string): void {
    this.logHistory.update(prev => [`[SYSTEM] ${msg}`, ...prev]);
  }

  /* @section ArchitectureMap
   * Demonstra o uso de Meta-programação em Angular.
   * Os métodos de negócio estão limpos de lógica de logging e medição de tempo.
   * O Decorator @Audit injeta essas funcionalidades de forma declarativa.
   */
}

/*
 * RESUMO TEÓRICO
 * Decorators são uma forma de adicionar metadados e comportamento a classes, 
 * métodos e propriedades de forma estática. Eles são a base de como o próprio 
 * Angular funciona (@Component, @Injectable). Criar seus próprios decorators 
 * permite centralizar lógicas comuns (como auditoria, cache ou controle de erro) 
 * sem poluir a lógica de negócio dos componentes.
 */
