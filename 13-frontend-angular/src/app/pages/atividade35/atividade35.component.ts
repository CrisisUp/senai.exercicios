/**
 * @file atividade35.component.ts
 * @brief Atividade 35: O Motor de Plugins (Plugin Architecture).
 * @author Cristiano
 * @date 2026
 */

import { Component, ViewChild, ViewContainerRef, inject, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PluginService, PluginMetadata } from './services/plugin.service';

@Component({
  selector: 'app-atividade35',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade35.component.html',
  styleUrl: './atividade35.component.css'
})
export class Atividade35Component {
  private readonly pluginService = inject(PluginService);

  /**
   * @brief Anchor point para a injeção do plugin selecionado.
   */
  @ViewChild('pluginHost', { read: ViewContainerRef }) host!: ViewContainerRef;

  protected readonly plugins = this.pluginService.availablePlugins;
  protected readonly activePluginId = signal<string | null>(null);
  protected readonly isLoading = signal<boolean>(false);

  /**
   * @brief Orquestra o ciclo de vida do plugin.
   */
  protected async activatePlugin(plugin: PluginMetadata): Promise<void> {
    if (this.activePluginId() === plugin.id) return;

    this.isLoading.set(true);
    this.host.clear();
    
    try {
      const component = await this.pluginService.loadPluginComponent(plugin);
      this.host.createComponent(component);
      this.activePluginId.set(plugin.id);
    } catch (err) {
      console.error('[PLUGIN_ERROR] Falha ao carregar binário:', err);
    } finally {
      this.isLoading.set(false);
    }
  }

  protected clearHost(): void {
    this.host.clear();
    this.activePluginId.set(null);
  }

  /* @section ArchitectureMap
   * Implementa 'Inversion of Control' para funcionalidades.
   * O Shell não conhece os componentes dos plugins em tempo de compilação.
   * A integração é feita via Dynamic Imports e ViewContainerRef, permitindo
   * extensibilidade infinita sem inflar o bundle principal.
   */
}

/*
 * RESUMO TEÓRICO
 * A Arquitetura de Plugins é o padrão ouro para sistemas de larga escala que 
 * precisam ser extensíveis por terceiros ou por times independentes. 
 * Ao utilizar Dynamic Component Loading, garantimos que apenas o código 
 * necessário seja baixado, respeitando os princípios de Lean Engineering.
 */
