import { Component, OnInit, signal } from '@angular/core';

/**
 * @file atividade01.component.ts
 * @brief Componente da Atividade 01: O Nascimento da Web (Tríade Fundamental).
 * @author Gemini CLI Elite
 * @date 2026-04-30
 * 
 * @description Este componente porta o conceito da atividade original (HTML/CSS/JS)
 * para a arquitetura Standalone do Angular v21, utilizando Signals para reatividade.
 */

@Component({
  selector: 'app-atividade01',
  standalone: true,
  templateUrl: './atividade01.component.html',
  styleUrl: './atividade01.component.css'
})
export class Atividade01Component implements OnInit {
  /**
   * @description Signal reativo contendo a mensagem de status do sistema.
   */
  protected readonly systemMessage = signal('Iniciando sequência de boot da Tríade Fundamental (Versão Angular)...');

  ngOnInit(): void {
    /**
     * @description Simulação do script.js original com logs industriais no console.
     */
    console.log("%c[SYSTEM] Nexus OS v1.0.0 Online (Angular Elite Engine)", "color: #dd0031; font-weight: bold; font-size: 20px;");
    console.log("Sequência de boot concluída. Componente Standalone renderizado com sucesso.");
    
    // Alerta comentado conforme o padrão do Módulo 09 (React)
    // alert("Sinal de vida detectado: Nexus OS (Angular) pronto para operar.");
  }
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
