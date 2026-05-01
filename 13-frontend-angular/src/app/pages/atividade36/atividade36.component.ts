/**
 * @file atividade36.component.ts
 * @brief Atividade 36: O Cérebro Enterprise (Desafio Integrador de Elite).
 * @author Cristiano
 * @date 2026
 */

import { 
  Component, inject, signal, effect, 
  ViewChild, ViewContainerRef, Type, 
  OnDestroy, ChangeDetectionStrategy 
} from '@angular/core';
import { CommonModule } from '@angular/common';
import { NexusStore } from '../atividade32/store/nexus.store';
import { PluginService, PluginMetadata } from '../atividade35/services/plugin.service';
import { VoiceCommandService } from '../atividade28/services/voice-command.service';
import { Audit } from '../atividade27/decorators/audit.decorator';

@Component({
  selector: 'app-atividade36',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade36.component.html',
  styleUrl: './atividade36.component.css',
  changeDetection: ChangeDetectionStrategy.OnPush
})
export class Atividade36Component implements OnDestroy {
  // Injeção de Dependências de Elite
  protected readonly store = inject(NexusStore);
  protected readonly pluginService = inject(PluginService);
  protected readonly voiceService = inject(VoiceCommandService);

  @ViewChild('primeHost', { read: ViewContainerRef }) host!: ViewContainerRef;

  // Estados Locais e do Store
  protected readonly alert = this.store.globalAlert;
  protected readonly protocol = this.store.securityProtocol;
  protected readonly isListening = this.voiceService.isListening;
  protected readonly lastCommand = this.voiceService.lastTranscript;
  protected readonly currentModuleId = signal<string | null>(null);

  constructor() {
    /**
     * @description Orquestração por Voz Integrada ao Estado Global.
     */
    effect(() => {
      const cmd = this.lastCommand().toLowerCase();
      
      if (cmd.includes('carregar scanner')) this.executeModuleLoad('SCANNER_V3');
      if (cmd.includes('carregar exterminador')) this.executeModuleLoad('TERM_X');
      if (cmd.includes('ativar alerta')) this.store.updateAlert('EMERGÊNCIA_NÍVEL_ELITE');
      if (cmd.includes('limpar alertas')) this.store.updateAlert(null);
    });
  }

  /**
   * @brief Orquestra o carregamento de módulos baseado no Catálogo do PluginService.
   */
  @Audit()
  protected async executeModuleLoad(pluginId: string): Promise<void> {
    const plugin = this.pluginService.availablePlugins().find(p => p.id === pluginId);
    if (!plugin || this.currentModuleId() === pluginId) return;

    this.host.clear();
    this.voiceService.speak(`Injetando módulo ${plugin.name} no núcleo central.`);
    
    try {
      const component = await this.pluginService.loadPluginComponent(plugin);
      this.host.createComponent(component);
      this.currentModuleId.set(pluginId);
    } catch (err) {
      console.error('[CORE_FAILURE] Erro na injeção de binário:', err);
    }
  }

  protected startVoiceLink(): void {
    this.voiceService.listen();
  }

  ngOnDestroy(): void {
    this.host?.clear();
  }

  /* @section ArchitectureMap
   * Fusão Enterprise (Nível 36):
   * 1. Global Store -> Sincroniza alertas entre todos os componentes da malha.
   * 2. Plugin Engine -> Carregamento assíncrono de binários sob demanda.
   * 3. Speech API -> Interface natural para orquestração de módulos.
   * 4. AOP (Decorators) -> Auditoria de comandos críticos de infraestrutura.
   * 5. OnPush -> Otimização de performance para dashboards de alta densidade.
   */
}

/*
 * RESUMO TEÓRICO
 * O Desafio Integrador de Elite coroa a jornada Angular Mastery. 
 * Ele prova que a arquitetura moderna do Angular (Signals + Standalone + DI) 
 * é capaz de criar sistemas modulares (MFE), reativos e sensoriais que 
 * atendem aos requisitos mais rigorosos de performance e manutenibilidade 
 * do mercado de software Enterprise mundial.
 */
