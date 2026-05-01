/**
 * @file atividade18.component.ts
 * @brief Atividade 18: A Forja de Missões (Reactive Forms Avançados).
 * @author Cristiano
 * @date 2026
 */

import { Component, inject, signal, computed } from '@angular/core';
import { CommonModule } from '@angular/common';
import { 
  ReactiveFormsModule, 
  FormBuilder, 
  FormGroup, 
  FormArray, 
  Validators, 
  AbstractControl, 
  ValidationErrors 
} from '@angular/forms';

/**
 * @brief Validador Customizado de Elite.
 * Verifica se o código da missão segue o padrão NEXUS-XXXX (onde X é dígito).
 */
function nexusCodeValidator(control: AbstractControl): ValidationErrors | null {
  const pattern = /^NEXUS-\d{4}$/;
  const valid = pattern.test(control.value);
  return valid ? null : { invalidNexusCode: true };
}

@Component({
  selector: 'app-atividade18',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  templateUrl: './atividade18.component.html',
  styleUrl: './atividade18.component.css'
})
export class Atividade18Component {
  private readonly fb = inject(FormBuilder);

  /**
   * @brief Estrutura do Formulário Reativo.
   */
  protected readonly missionForm: FormGroup = this.fb.group({
    missionCode: ['', [Validators.required, nexusCodeValidator]],
    commander: ['', [Validators.required, Validators.minLength(3)]],
    priority: ['LOW', Validators.required],
    checkpoints: this.fb.array([]) // Dynamic array of checkpoints
  });

  /**
   * @brief Getter para facilitar acesso ao FormArray no template.
   */
  get checkpoints(): FormArray {
    return this.missionForm.get('checkpoints') as FormArray;
  }

  /**
   * @brief Adiciona um novo checkpoint dinamicamente.
   */
  protected addCheckpoint(): void {
    const checkpointGroup = this.fb.group({
      location: ['', Validators.required],
      action: ['RECON', Validators.required]
    });
    this.checkpoints.push(checkpointGroup);
  }

  /**
   * @brief Remove um checkpoint específico.
   */
  protected removeCheckpoint(index: number): void {
    this.checkpoints.removeAt(index);
  }

  /**
   * @brief Processa o envio do formulário.
   */
  protected submitMission(): void {
    if (this.missionForm.valid) {
      console.log("[FORGE] Missão forjada com sucesso:", this.missionForm.value);
      alert('MISSÃO SINCRONIZADA COM O NÚCLEO NEXUS.');
      this.missionForm.reset({ priority: 'LOW' });
      this.checkpoints.clear();
    } else {
      console.warn("[FORGE] Falha na validação do protocolo de missão.");
    }
  }

  /* @section ArchitectureMap
   * O Reactive Forms provê controle total sobre o estado do formulário.
   * FormArray permite expansão dinâmica da interface para coleta de dados complexos.
   * Validação síncrona customizada garante integridade dos dados antes do envio.
   */
}

/*
 * RESUMO TEÓRICO
 * Reactive Forms são baseados em streams de dados (Observables) e objetos imutáveis.
 * Oferecem escalabilidade e testabilidade superior em comparação ao Template-driven.
 * O uso de FormArray é a solução padrão do Angular para lidar com listas dinâmicas de inputs.
 */
