/**
 * @file atividade26.component.ts
 * @brief Atividade 26: O Sincronizador de Órbita (Signals Avançados).
 * @author Cristiano
 * @date 2026
 */

import { Component, signal, linkedSignal, resource, computed } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

interface SatelliteConfig {
  id: string;
  name: string;
  defaultPower: number;
}

interface SatelliteMetadata {
  orbit: string;
  uptime: string;
  fuel: string;
}

@Component({
  selector: 'app-atividade26',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './atividade26.component.html',
  styleUrl: './atividade26.component.css'
})
export class Atividade26Component {
  /**
   * @description Lista de satélites disponíveis para monitoramento.
   */
  protected readonly satellites = signal<SatelliteConfig[]>([
    { id: 'NX-01', name: 'Alpha Prime', defaultPower: 85 },
    { id: 'NX-02', name: 'Beta Zero', defaultPower: 45 },
    { id: 'NX-03', name: 'Gamma Ray', defaultPower: 120 }
  ]);

  /**
   * @description Satélite atualmente selecionado pelo operador.
   */
  protected readonly selectedSatelliteId = signal<string>('NX-01');

  /**
   * @brief Signal Vinculado (linkedSignal).
   */
  protected readonly powerLevel = linkedSignal({
    source: this.selectedSatelliteId,
    computation: (id) => {
      const sat = this.satellites().find(s => s.id === id);
      return sat ? sat.defaultPower : 0;
    }
  });

  /**
   * @brief Recurso Assíncrono (resource).
   * Note: Na versão atual do Angular (2026), a propriedade é 'params' (reativa) 
   * e o loader recebe um objeto contendo os 'params' resolvidos.
   */
  protected readonly satelliteMetadata = resource({
    params: () => ({ id: this.selectedSatelliteId() }),
    loader: async ({ params }) => {
      console.log(`[RESOURCE] Buscando metadados para: ${params.id}`);
      
      await new Promise(resolve => setTimeout(resolve, 1000));
      
      const mockDb: Record<string, SatelliteMetadata> = {
        'NX-01': { orbit: 'LEO', uptime: '99.98%', fuel: '72%' },
        'NX-02': { orbit: 'MEO', uptime: '94.50%', fuel: '12%' },
        'NX-03': { orbit: 'GEO', uptime: '99.99%', fuel: '98%' }
      };
      
      return mockDb[params.id] || { orbit: 'N/A', uptime: '0%', fuel: '0%' };
    }
  });

  protected readonly currentSatName = computed(() => 
    this.satellites().find(s => s.id === this.selectedSatelliteId())?.name
  );

  /**
   * @brief Ajusta o nível de potência manualmente.
   */
  protected adjustPower(delta: number): void {
    this.powerLevel.set(this.powerLevel() + delta);
  }
}
