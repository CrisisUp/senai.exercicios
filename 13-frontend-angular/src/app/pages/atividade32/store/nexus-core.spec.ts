/**
 * @file nexus-core.spec.ts
 * @brief Suíte de Testes de Elite para o Núcleo Nexus.
 * @author Cristiano (Auditado por Gemini CLI)
 */

import { TestBed } from '@angular/core/testing';
import { NexusStore } from './nexus.store';
import { PluginService } from '../../atividade35/services/plugin.service';

describe('💎 NEXUS_PRIME_CORE: PROTOLO DE RESILIÊNCIA', () => {
  let store: NexusStore;
  let pluginService: PluginService;

  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [NexusStore, PluginService]
    });
    store = TestBed.inject(NexusStore);
    pluginService = TestBed.inject(PluginService);
  });

  describe('🧠 NexusStore (Signal State Management)', () => {
    it('deve iniciar com o protocolo ALPHA e 12 nodes ativos', () => {
      expect(store.securityProtocol()).toBe('ALPHA');
      expect(store.activeNodes()).toBe(12);
    });

    it('deve atualizar o alerta global e manter a reatividade', () => {
      const msg = 'INTEGRIDADE_VIOLADA';
      store.updateAlert(msg);
      expect(store.globalAlert()).toBe(msg);
    });

    it('deve incrementar nodes de forma atômica', () => {
      const initial = store.activeNodes();
      store.incrementNodes();
      expect(store.activeNodes()).toBe(initial + 1);
    });

    it('deve garantir a troca de protocolos de segurança', () => {
      store.setProtocol('DELTA');
      expect(store.securityProtocol()).toBe('DELTA');
    });
  });

  describe('⚙️ PluginService (Dynamic Orchestration)', () => {
    it('deve carregar o catálogo inicial de plugins de elite', () => {
      const catalog = pluginService.availablePlugins();
      expect(catalog.length).toBeGreaterThan(0);
      expect(catalog[0].id).toBe('SCANNER_V3');
    });

    it('deve resolver o componente dinâmico do scanner com sucesso', async () => {
      const scannerPlugin = pluginService.availablePlugins()[0];
      const componentType = await pluginService.loadPluginComponent(scannerPlugin);
      expect(componentType).toBeDefined();
      expect(componentType.name).toBe('PluginScannerComponent');
    });
  });
});
