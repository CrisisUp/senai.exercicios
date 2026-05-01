/**
 * @file atividade20.component.ts
 * @brief Atividade 20: O Cofre de Dados (State Management Final).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { VaultService } from './services/vault.service';

@Component({
  selector: 'app-atividade20',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './atividade20.component.html',
  styleUrl: './atividade20.component.css'
})
export class Atividade20Component {
  protected readonly vault = inject(VaultService);
  
  // Inputs do formulário local
  protected keyLabel = signal<string>('');
  protected keyValue = signal<string>('');

  protected saveToVault(): void {
    if (this.keyLabel().trim() && this.keyValue().trim()) {
      this.vault.addKey(this.keyLabel(), this.keyValue());
      this.keyLabel.set('');
      this.keyValue.set('');
      console.log("[NEXUS] Nova credencial forjada e persistida.");
    }
  }

  protected deleteFromVault(id: string): void {
    this.vault.removeKey(id);
    console.log(`[NEXUS] Credencial ${id} incinerada.`);
  }
}

/* @section ArchitectureMap
 * Fechamento do Nível Arquiteto.
 * O componente atua como uma interface de entrada, delegando a persistência
 * e a lógica de negócio para o VaultService. O uso de Signals em todo o fluxo
 * garante que a UI reflita o LocalStorage instantaneamente.
 */

/*
 * RESUMO TEÓRICO
 * State Management com Signals é a forma recomendada de gerenciar estados complexos
 * em aplicações Angular modernas. Elimina a necessidade de bibliotecas externas (como NgRx)
 * para a maioria dos casos de uso, mantendo o código idiomático e performático.
 */
