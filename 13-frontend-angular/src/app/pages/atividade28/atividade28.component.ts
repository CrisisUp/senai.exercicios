/**
 * @file atividade28.component.ts
 * @brief Atividade 28: O Comando de Voz (Web Speech API).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, effect, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { VoiceCommandService } from './services/voice-command.service';

@Component({
  selector: 'app-atividade28',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade28.component.html',
  styleUrl: './atividade28.component.css'
})
export class Atividade28Component {
  private readonly voiceService = inject(VoiceCommandService);

  // Estados Locais
  protected readonly isListening = this.voiceService.isListening;
  protected readonly lastTranscript = this.voiceService.lastTranscript;
  protected readonly alertMessage = signal<string>('');

  constructor() {
    /**
     * @description Orquestrador de Comandos (Reactive Logic).
     * Analisa a transcrição de voz e executa ações de sistema.
     */
    effect(() => {
      const text = this.lastTranscript().toLowerCase();
      
      if (text.includes('ativar protocolo delta')) {
        this.executeProtocol('DELTA', 'Sequência de ativação tática iniciada.');
      } else if (text.includes('emergência')) {
        this.executeProtocol('EMERGÊNCIA', 'Protocolo de alerta vermelho ativado. Evacuando sistema.');
      } else if (text.includes('ajuda')) {
        this.voiceService.speak('Eu sou o Nexus. Comande o sistema usando sua voz.');
      }
    });
  }

  protected startListening(): void {
    this.voiceService.listen();
  }

  private executeProtocol(code: string, message: string): void {
    this.alertMessage.set(`[PROTOCOLO ${code} ATIVADO]`);
    this.voiceService.speak(message);
    
    // Limpa o alerta após 5 segundos
    setTimeout(() => this.alertMessage.set(''), 5000);
  }

  /* @section ArchitectureMap
   * O componente atua como o 'Cérebro' do sistema de voz.
   * Ele consome o estado bruto do VoiceCommandService e aplica
   * lógica de negócio (reconhecimento de intenção) via Effects.
   */
}

/*
 * RESUMO TEÓRICO
 * A integração com Native APIs (como Web Speech) permite que aplicações Angular 
 * transcendam a interface visual tradicional. O uso de Signals e Effects para 
 * monitorar fluxos de entrada nativa (voz, sensores) garante que a lógica 
 * permaneça declarativa e fácil de manter em ecossistemas industriais.
 */
