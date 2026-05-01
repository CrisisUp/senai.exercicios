/**
 * @file atividade21.component.ts
 * @brief Atividade 21: O Radar Digital (Canvas & ViewChild).
 * @author Cristiano
 * @date 2026
 */

import { Component, ElementRef, ViewChild, AfterViewInit, signal, effect, OnDestroy } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-atividade21',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade21.component.html',
  styleUrl: './atividade21.component.css'
})
export class Atividade21Component implements AfterViewInit, OnDestroy {
  /**
   * @brief Referência ao elemento Canvas no DOM.
   * ViewChild permite interagir diretamente com APIs de baixo nível do navegador.
   */
  @ViewChild('radarCanvas') canvasRef!: ElementRef<HTMLCanvasElement>;
  
  private ctx!: CanvasRenderingContext2D;
  private animationId!: number;

  /**
   * @description Estado reativo da varredura do radar.
   */
  protected readonly angle = signal<number>(0);
  protected readonly detectedObjects = signal<{x: number, y: number, alpha: number}[]>([]);

  constructor() {
    /**
     * @description Efeito para reagir a detecções (Simulação).
     */
    effect(() => {
      // Toda vez que o ângulo completa uma volta, podemos simular novas detecções
      if (this.angle() === 0) {
        this.simulateDetections();
      }
    });
  }

  ngAfterViewInit(): void {
    const canvas = this.canvasRef.nativeElement;
    this.ctx = canvas.getContext('2d')!;
    this.startRadarSweep();
  }

  private startRadarSweep(): void {
    const animate = () => {
      this.angle.update(a => (a + 1) % 360);
      this.drawRadar();
      this.animationId = requestAnimationFrame(animate);
    };
    animate();
  }

  private drawRadar(): void {
    const canvas = this.canvasRef.nativeElement;
    const { width, height } = canvas;
    const centerX = width / 2;
    const centerY = height / 2;
    const radius = Math.min(centerX, centerY) - 10;

    // 1. Limpeza com rastro (fade effect)
    this.ctx.fillStyle = 'rgba(0, 10, 0, 0.1)';
    this.ctx.fillRect(0, 0, width, height);

    // 2. Desenho dos círculos concêntricos
    this.ctx.strokeStyle = '#004400';
    this.ctx.lineWidth = 1;
    for (let i = 1; i <= 4; i++) {
      this.ctx.beginPath();
      this.ctx.arc(centerX, centerY, (radius / 4) * i, 0, Math.PI * 2);
      this.ctx.stroke();
    }

    // 3. Desenho da linha de varredura (Sweep)
    const rad = (this.angle() * Math.PI) / 180;
    this.ctx.strokeStyle = '#00ff00';
    this.ctx.lineWidth = 2;
    this.ctx.beginPath();
    this.ctx.moveTo(centerX, centerY);
    this.ctx.lineTo(
      centerX + Math.cos(rad) * radius,
      centerY + Math.sin(rad) * radius
    );
    this.ctx.stroke();

    // 4. Desenho de objetos detectados
    this.drawDetectedObjects();
  }

  private simulateDetections(): void {
    const newObjects = Array.from({ length: 3 }, () => ({
      x: 100 + Math.random() * 200,
      y: 100 + Math.random() * 200,
      alpha: 1.0
    }));
    this.detectedObjects.set(newObjects);
  }

  private drawDetectedObjects(): void {
    this.detectedObjects.update(objs => 
      objs.map(o => ({ ...o, alpha: Math.max(0, o.alpha - 0.005) }))
          .filter(o => o.alpha > 0)
    );

    for (const obj of this.detectedObjects()) {
      this.ctx.fillStyle = `rgba(255, 255, 255, ${obj.alpha})`;
      this.ctx.beginPath();
      this.ctx.arc(obj.x, obj.y, 4, 0, Math.PI * 2);
      this.ctx.fill();
    }
  }

  ngOnDestroy(): void {
    if (this.animationId) {
      cancelAnimationFrame(this.animationId);
    }
  }

  /* @section ArchitectureMap
   * Integração Angular-Canvas:
   * ViewChild -> Captura ElementRef.
   * requestAnimationFrame -> Loop de renderização fora do Change Detection (ideal para performance).
   * Signals -> Sincronizam a lógica de simulação com a interface.
   */
}

/*
 * RESUMO TEÓRICO
 * O uso de ViewChild e ElementRef permite que o desenvolvedor Angular escape da 
 * abstração do DOM virtual para interagir com APIs nativas de alta performance.
 * Em aplicações industriais (Engenharia de Elite), isso é essencial para visualização 
 * de dados massivos, gráficos 2D/3D e processamento de imagem em tempo real.
 */
