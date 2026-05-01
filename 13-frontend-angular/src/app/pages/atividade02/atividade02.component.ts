import { Component, signal } from '@angular/core';

/**
 * @file atividade02.component.ts
 * @brief Componente da Atividade 02: O Inventário Digital.
 * @author Gemini CLI Elite
 * @date 2026-04-30
 *
 * @description Demonstração de listas, variáveis tipadas e reatividade fina
 * utilizando Signals e a nova Control Flow Syntax do Angular v21.
 */

interface Drone {
  id: string;
  name: string;
  status: 'active' | 'warning';
}

@Component({
  selector: 'app-atividade02',
  standalone: true,
  templateUrl: './atividade02.component.html',
  styleUrl: './atividade02.component.css'
})
export class Atividade02Component {
  /**
   * @description Constantes e Signals (JS Atitude)
   */
  protected readonly systemVersion = 'v3.0.0-angular';
  protected readonly operatorName = signal('Cristiano');

  /**
   * @description Lista de drones gerenciada via Signal reativo.
   */
  protected readonly drones = signal<Drone[]>([
    { id: 'D-001', name: 'SkyHawk Zero', status: 'active' },
    { id: 'D-002', name: 'StormRunner', status: 'warning' },
    { id: 'D-003', name: 'ThunderBolt', status: 'active' },
  ]);
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
