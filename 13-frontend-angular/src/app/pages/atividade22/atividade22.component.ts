/**
 * @file atividade22.component.ts
 * @brief Atividade 22: O Alvo Tático (Interação Nativa e Coordenadas).
 * @author Cristiano
 * @date 2026
 */

import { Component, ElementRef, ViewChild, AfterViewInit, signal, HostListener } from '@angular/core';
import { CommonModule } from '@angular/common';

interface TacticalTarget {
  x: number;
  y: number;
  label: string;
  timestamp: string;
}

@Component({
  selector: 'app-atividade22',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade22.component.html',
  styleUrl: './atividade22.component.css'
})
export class Atividade22Component implements AfterViewInit {
  @ViewChild('mapCanvas') canvasRef!: ElementRef<HTMLCanvasElement>;
  
  private ctx!: CanvasRenderingContext2D;

  /**
   * @description Lista de alvos marcados pelo operador.
   */
  protected readonly targets = signal<TacticalTarget[]>([]);
  
  /**
   * @description Coordenada atual do mouse (Telemetria).
   */
  protected readonly cursorCoord = signal({ x: 0, y: 0 });

  ngAfterViewInit(): void {
    this.ctx = this.canvasRef.nativeElement.getContext('2d')!;
    this.drawGrid();
  }

  /**
   * @brief Captura cliques no Canvas para marcar alvos táticos.
   */
  protected handleMapClick(event: MouseEvent): void {
    const rect = this.canvasRef.nativeElement.getBoundingClientRect();
    const x = Math.round(event.clientX - rect.left);
    const y = Math.round(event.clientY - rect.top);

    const newTarget: TacticalTarget = {
      x,
      y,
      label: `TGT-${(this.targets().length + 1).toString().padStart(3, '0')}`,
      timestamp: new Date().toLocaleTimeString()
    };

    this.targets.update(prev => [...prev, newTarget]);
    this.drawTargetOnCanvas(newTarget);
    console.log(`[TACTICAL] Alvo travado em: X=${x}, Y=${y}`);
  }

  /**
   * @brief Rastreia o movimento do mouse para telemetria em tempo real.
   */
  protected handleMouseMove(event: MouseEvent): void {
    const rect = this.canvasRef.nativeElement.getBoundingClientRect();
    this.cursorCoord.set({
      x: Math.round(event.clientX - rect.left),
      y: Math.round(event.clientY - rect.top)
    });
  }

  private drawGrid(): void {
    const { width, height } = this.canvasRef.nativeElement;
    this.ctx.strokeStyle = '#1a1a1a';
    this.ctx.lineWidth = 1;

    for (let x = 0; x <= width; x += 50) {
      this.ctx.beginPath();
      this.ctx.moveTo(x, 0);
      this.ctx.lineTo(x, height);
      this.ctx.stroke();
    }

    for (let y = 0; y <= height; y += 50) {
      this.ctx.beginPath();
      this.ctx.moveTo(0, y);
      this.ctx.lineTo(width, y);
      this.ctx.stroke();
    }
  }

  private drawTargetOnCanvas(target: TacticalTarget): void {
    // Desenha a mira (Crosshair)
    this.ctx.strokeStyle = '#f85149';
    this.ctx.lineWidth = 2;
    
    // Círculo externo
    this.ctx.beginPath();
    this.ctx.arc(target.x, target.y, 10, 0, Math.PI * 2);
    this.ctx.stroke();

    // Linhas cruzadas
    this.ctx.beginPath();
    this.ctx.moveTo(target.x - 15, target.y);
    this.ctx.lineTo(target.x + 15, target.y);
    this.ctx.moveTo(target.x, target.y - 15);
    this.ctx.lineTo(target.x, target.y + 15);
    this.ctx.stroke();

    // Label
    this.ctx.fillStyle = '#f85149';
    this.ctx.font = '10px monospace';
    this.ctx.fillText(target.label, target.x + 18, target.y + 10);
  }

  protected clearMap(): void {
    const { width, height } = this.canvasRef.nativeElement;
    this.ctx.clearRect(0, 0, width, height);
    this.drawGrid();
    this.targets.set([]);
    console.log("[TACTICAL] Mapa limpo. Protocolo de redefinição concluído.");
  }

  /* @section ArchitectureMap
   * O fluxo de interação demonstra a ponte entre o sistema de eventos do Angular
   * (Event Binding no HTML) e a API imperativa do Canvas.
   * As coordenadas são normalizadas usando getBoundingClientRect() para garantir
   * precisão independente do layout ou scroll.
   */
}

/*
 * RESUMO TEÓRICO
 * A captura de eventos nativos em elementos gráficos é a base para interfaces de 
 * comando e controle (C2). Ao contrário do DOM, o Canvas não possui "elementos" 
 * clicáveis; cabe ao Engenheiro traduzir coordenadas de tela em lógica de negócio.
 */
