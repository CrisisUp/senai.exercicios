/**
 * @file voice-command.service.ts
 * @brief Serviço de Integração com Web Speech API (Recognition & Synthesis).
 * @author Cristiano
 * @date 2026
 */

import { Injectable, signal } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class VoiceCommandService {
  /**
   * @brief Estado reativo do serviço de voz.
   */
  public readonly isListening = signal<boolean>(false);
  public readonly lastTranscript = signal<string>('');
  
  private recognition: any;

  constructor() {
    this.initSpeechRecognition();
  }

  /**
   * @brief Inicializa a API de reconhecimento de voz do navegador.
   */
  private initSpeechRecognition(): void {
    const SpeechRecognition = (window as any).SpeechRecognition || (window as any).webkitSpeechRecognition;
    
    if (SpeechRecognition) {
      this.recognition = new SpeechRecognition();
      this.recognition.continuous = false;
      this.recognition.lang = 'pt-BR';
      this.recognition.interimResults = false;

      this.recognition.onstart = () => this.isListening.set(true);
      this.recognition.onend = () => this.isListening.set(false);
      
      this.recognition.onresult = (event: any) => {
        const transcript = event.results[0][0].transcript;
        this.lastTranscript.set(transcript);
        console.log(`[VOICE] Transcrição detectada: ${transcript}`);
      };

      this.recognition.onerror = (err: any) => {
        console.error('[VOICE] Erro no reconhecimento:', err.error);
        this.isListening.set(false);
      };
    } else {
      console.warn('[VOICE] Web Speech API não suportada neste navegador.');
    }
  }

  /**
   * @brief Ativa o microfone para escuta tática.
   */
  public listen(): void {
    if (this.recognition && !this.isListening()) {
      this.recognition.start();
    }
  }

  /**
   * @brief Converte texto em fala sintetizada (Voz de Sistema).
   */
  public speak(text: string): void {
    const utterance = new SpeechSynthesisUtterance(text);
    utterance.lang = 'pt-BR';
    utterance.rate = 1.0;
    utterance.pitch = 0.8; // Tom industrial/robótico
    window.speechSynthesis.speak(utterance);
    console.log(`[VOICE] Sintetizando: ${text}`);
  }
}

/* @section ArchitectureMap
 * O serviço atua como uma fachada (Facade) para APIs nativas do navegador.
 * Encapsula a complexidade do SpeechRecognition (event-based) e expõe 
 * um estado limpo via Signals para os componentes Nexus.
 */
