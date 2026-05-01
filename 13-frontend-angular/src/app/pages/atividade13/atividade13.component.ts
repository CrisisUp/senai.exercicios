/**
 * @file atividade13.component.ts
 * @brief Atividade 13: A Chave de Criptografia (Advanced DI).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { APP_CONFIG, SYSTEM_VERSION, AppConfig } from './tokens/config.token';

/**
 * @description Demonstração de Injeção de Dependência Avançada usando Tokens.
 * Em sistemas de elite, evitamos depender de classes concretas quando 
 * valores de configuração ou comportamentos variam por ambiente.
 */

@Component({
  selector: 'app-atividade13',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade13.component.html',
  styleUrl: './atividade13.component.css',
  providers: [
    // Definindo os provedores localmente para demonstração
    {
      provide: APP_CONFIG,
      useValue: {
        apiUrl: 'https://api.nexus-industrial.io/v1',
        retryAttempts: 3,
        enableEncryption: true
      }
    },
    {
      provide: SYSTEM_VERSION,
      useValue: '2.5.0-ELITE'
    }
  ]
})
export class Atividade13Component {
  /**
   * @brief Injeção via inject() com Tokens.
   */
  protected readonly config = inject(APP_CONFIG);
  protected readonly version = inject(SYSTEM_VERSION);

  /* @section ArchitectureMap
   * O Angular resolve os tokens APP_CONFIG e SYSTEM_VERSION 
   * procurando na hierarquia de injetores. Definimos os valores 
   * no array 'providers' do próprio componente para isolamento tático.
   */
}

/*
 * RESUMO TEÓRICO
 * InjectionToken é a ferramenta definitiva para desacoplar configuração de lógica.
 * Diferente de classes, tokens permitem injetar interfaces, objetos literais e 
 * valores primitivos, garantindo a "Inversão de Dependência" (SOLID).
 */
