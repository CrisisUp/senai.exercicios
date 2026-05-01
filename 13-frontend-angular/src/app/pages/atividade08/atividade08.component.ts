import { Component, inject } from '@angular/core';
import { FleetService } from './services/fleet.service';

/**
 * @file atividade08.component.ts
 * @brief Componente da Atividade 08: Sistemas Vivos.
 * @author Gemini CLI Elite
 * @date 2026-04-30
 * 
 * @description Demonstração de animações industriais (Keyframes), Services (DI)
 * e automação de interface utilizando a arquitetura Standalone do Angular v21.
 */

@Component({
  selector: 'app-atividade08',
  standalone: true,
  templateUrl: './atividade08.component.html',
  styleUrl: './atividade08.component.css'
})
export class Atividade08Component {
  /**
   * @description Injeção de Dependência Moderna via inject().
   * O FleetService gerencia os dados e a simulação de bateria.
   */
  protected readonly fleetService = inject(FleetService);

  /**
   * @description Shortcut para acessar o signal de drones do serviço.
   */
  protected readonly drones = this.fleetService.drones;
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
