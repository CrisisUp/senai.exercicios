/**
 * @file plugin.service.ts
 * @brief Serviço de Orquestração de Plugins Dinâmicos.
 * @author Cristiano
 * @date 2026
 */

import { Injectable, Type, signal } from '@angular/core';

export interface PluginMetadata {
  id: string;
  name: string;
  description: string;
  version: string;
  componentPath: string;
}

@Injectable({
  providedIn: 'root'
})
export class PluginService {
  /**
   * @brief Catálogo de Plugins disponíveis para o sistema Nexus.
   */
  private readonly _availablePlugins = signal<PluginMetadata[]>([
    {
      id: 'SCANNER_V3',
      name: 'Omni-Scanner Pro',
      description: 'Análise espectral de assinaturas térmicas e biológicas.',
      version: '3.4.2',
      componentPath: './components/plugin-scanner/plugin-scanner.component'
    },
    {
      id: 'TERM_X',
      name: 'Neural Terminator',
      description: 'Protocolo de encerramento de processos zumbis e limpeza de cache.',
      version: '1.0.0',
      componentPath: './components/plugin-terminator/plugin-terminator.component'
    }
  ]);

  public readonly availablePlugins = this._availablePlugins.asReadonly();

  /**
   * @brief Carrega o componente do plugin dinamicamente.
   */
  public async loadPluginComponent(plugin: PluginMetadata): Promise<Type<any>> {
    console.log(`[PLUGIN_ENGINE] Carregando código fonte para: ${plugin.id}`);
    
    // Simula delay de rede/parsing
    await new Promise(resolve => setTimeout(resolve, 600));

    let module: any;
    if (plugin.id === 'SCANNER_V3') {
      module = await import('../components/plugin-scanner/plugin-scanner.component');
      return module.PluginScannerComponent;
    } else {
      module = await import('../components/plugin-terminator/plugin-terminator.component');
      return module.PluginTerminatorComponent;
    }
  }
}

/* @section ArchitectureMap
 * Implementa a base de 'Dynamic Plugin Architecture'.
 * O serviço desacopla a UI da lista de funcionalidades, permitindo que novos 
 * módulos sejam registrados e carregados em runtime sem recompilar o shell.
 */
