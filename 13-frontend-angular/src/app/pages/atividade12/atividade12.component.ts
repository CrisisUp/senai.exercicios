/**
 * @file atividade12.component.ts
 * @brief Atividade 12: O Molde de Aço (Component Projection).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { NexusCardComponent } from './components/nexus-card/nexus-card.component';

@Component({
  selector: 'app-atividade12',
  standalone: true,
  imports: [CommonModule, NexusCardComponent],
  templateUrl: './atividade12.component.html',
  styleUrl: './atividade12.component.css'
})
export class Atividade12Component {
  protected readonly alerts = signal([
    { id: 1, title: 'Infiltração Detectada', desc: 'Setor 7B apresenta variação de umidade.', priority: true, sector: 'SECURITY' },
    { id: 2, title: 'Carga Pendente', desc: 'Drone DX-04 aguardando autorização de decolagem.', priority: false, sector: 'LOGISTICS' },
    { id: 3, title: 'Update Sistema', desc: 'Firmware v2.4 disponível para instalação.', priority: false, sector: 'MAINTENANCE' }
  ]);

  protected acknowledge(id: number): void {
    console.log(`[SYSTEM] Alerta ${id} reconhecido.`);
    this.alerts.update(list => list.filter(a => a.id !== id));
  }
}

/* @section ArchitectureMap
 * Demonstra o consumo de componentes genéricos via Projeção de Conteúdo.
 * O Atividade12Component (Parent) define o QUE será exibido,
 * enquanto o NexusCardComponent (Child) define COMO será moldado.
 */

/*
 * RESUMO TEÓRICO
 * Projeção de Conteúdo (<ng-content>) é a base para a criação de Design Systems
 * reutilizáveis. Ela permite que componentes sejam flexíveis o suficiente para 
 * aceitar qualquer marcação HTML externa, mantendo a consistência visual.
 */
