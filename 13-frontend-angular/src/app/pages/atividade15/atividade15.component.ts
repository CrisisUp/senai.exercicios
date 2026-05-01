/**
 * @file atividade15.component.ts
 * @brief Atividade 15: O Conversor Tático (Custom Pipes).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TelemetriaPipe } from './pipes/telemetria.pipe';

@Component({
  selector: 'app-atividade15',
  standalone: true,
  imports: [CommonModule, TelemetriaPipe],
  templateUrl: './atividade15.component.html',
  styleUrl: './atividade15.component.css'
})
export class Atividade15Component {
  /**
   * @description Dados brutos coletados de sensores Nexus.
   */
  protected readonly sensors = signal([
    { name: 'Velocidade Drone', value: 45.8762, unit: 'km/h', precision: 1 },
    { name: 'Altitude Operacional', value: 1250.5, unit: 'm', precision: 0 },
    { name: 'Tensão Bateria', value: 14.423, unit: 'V', precision: 2 },
    { name: 'Carga Patrimonial', value: 12500.99, unit: 'R$', precision: 2 },
    { name: 'Latência Satélite', value: 0.042, unit: 'ms', precision: 3 }
  ]);
}

/* @section ArchitectureMap
 * O componente atua como provedor de dados brutos (Raw Data).
 * A responsabilidade de formatação e apresentação (View Logic) 
 * é totalmente isolada no TelemetriaPipe.
 */

/*
 * RESUMO TEÓRICO
 * Pipes são ideais para transformações de dados que se repetem em vários locais da aplicação.
 * Eles promovem o princípio DRY (Don't Repeat Yourself) e mantêm o template 
 * limpo e legível. Pipes puros (Pure Pipes) garantem alta performance por evitar 
 * re-processamentos desnecessários.
 */
