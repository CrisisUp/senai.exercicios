/**
 * @file atividade33.component.ts
 * @brief Atividade 33: O Componente Universal (Angular Elements / Web Components).
 * @author Cristiano
 * @date 2026
 */

import { Component, CUSTOM_ELEMENTS_SCHEMA, signal, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';

/**
 * @brief Simulação de Registro de Web Component Nativo.
 * Em um cenário real de Angular Elements, o componente seria exportado
 * como um Custom Element usando createCustomElement().
 * Aqui, vamos simular a integração bidirecional.
 */
class NexusStatusIndicator extends HTMLElement {
  static get observedAttributes() { return ['status']; }

  constructor() {
    super();
    this.attachShadow({ mode: 'open' });
  }

  connectedCallback() {
    this.render();
  }

  attributeChangedCallback() {
    this.render();
  }

  render() {
    const status = this.getAttribute('status') || 'OFFLINE';
    const color = status === 'ACTIVE' ? '#3fb950' : '#f85149';
    
    this.shadowRoot!.innerHTML = `
      <style>
        .indicator {
          display: inline-flex;
          align-items: center;
          gap: 8px;
          padding: 4px 12px;
          background: rgba(0,0,0,0.3);
          border: 1px solid ${color};
          border-radius: 20px;
          color: ${color};
          font-family: monospace;
          font-size: 0.75rem;
          font-weight: bold;
          text-transform: uppercase;
        }
        .dot {
          width: 8px;
          height: 8px;
          background: ${color};
          border-radius: 50%;
          box-shadow: 0 0 10px ${color};
        }
      </style>
      <div class="indicator">
        <div class="dot"></div>
        <span>${status}</span>
      </div>
    `;
  }
}

// Registro global do Web Component (Simulação de integração Enterprise)
if (!customElements.get('nexus-status-indicator')) {
  customElements.define('nexus-status-indicator', NexusStatusIndicator);
}

@Component({
  selector: 'app-atividade33',
  standalone: true,
  imports: [CommonModule],
  schemas: [CUSTOM_ELEMENTS_SCHEMA], // Obrigatório para aceitar tags não-Angular
  templateUrl: './atividade33.component.html',
  styleUrl: './atividade33.component.css'
})
export class Atividade33Component implements OnInit {
  protected readonly systemStatus = signal<'ACTIVE' | 'FAILURE'>('ACTIVE');

  ngOnInit(): void {
    console.log('[ELEMENTS] Orquestrador de Web Components inicializado.');
  }

  protected toggleSystem(): void {
    this.systemStatus.update(s => s === 'ACTIVE' ? 'FAILURE' : 'ACTIVE');
  }

  /* @section ArchitectureMap
   * Integração Cross-Framework via Web Components:
   * 1. CUSTOM_ELEMENTS_SCHEMA -> Permite o uso de tags customizadas no template Angular.
   * 2. Shadow DOM -> Garante encapsulamento total de estilos do Web Component.
   * 3. Attribute Binding -> Angular controla o estado do Web Component via inputs padrão de HTML.
   */
}

/*
 * RESUMO TEÓRICO
 * Angular Elements permite converter componentes Angular em Web Components (Custom Elements).
 * Isso é vital para arquiteturas Enterprise onde componentes Angular precisam 
 * ser consumidos por outras tecnologias (React, Vue, Vanilla JS), promovendo a 
 * "Universalidade do Código" e reduzindo o lock-in de framework.
 */
