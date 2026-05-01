/**
 * @file atividade30.component.ts
 * @brief Atividade 30: O Simulador de Voo (Desafio Integrador Nível Engenheiro).
 * @author Cristiano
 * @date 2026
 */

import { 
  Component, ElementRef, ViewChild, AfterViewInit, 
  signal, effect, inject, OnDestroy, ChangeDetectionStrategy 
} from '@angular/core';
import { CommonModule } from '@angular/common';
import { VoiceCommandService } from '../atividade28/services/voice-command.service';
import { Audit } from '../atividade27/decorators/audit.decorator';

interface FlightPoint {
  x: number;
  y: number;
  altitude: number;
}

@Component({
  selector: 'app-atividade30',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './atividade30.component.html',
  styleUrl: './atividade30.component.css',
  changeDetection: ChangeDetectionStrategy.OnPush
})
export class Atividade30Component implements AfterViewInit, OnDestroy {
  private readonly voiceService = inject(VoiceCommandService);
  
  @ViewChild('flightCanvas') canvasRef!: ElementRef<HTMLCanvasElement>;
  private ctx!: CanvasRenderingContext2D;
  private worker: Worker | null = null;
  private animationId: number | null = null;

  // Estados de Missão
  protected readonly flightPath = signal<FlightPoint[]>([]);
  protected readonly isSimulating = signal<boolean>(false);
  protected readonly statusMessage = signal<string>('AGUARDANDO COMANDO DE VOZ');

  constructor() {
    /**
     * @description Efeito de Comando de Voz Integrado.
     */
    effect(() => {
      const cmd = this.voiceService.lastTranscript().toLowerCase();
      if (cmd.includes('iniciar simulação')) this.startSimulation();
      if (cmd.includes('abortar')) this.abortMission();
    });
  }

  ngAfterViewInit(): void {
    this.ctx = this.canvasRef.nativeElement.getContext('2d')!;
    this.drawBaseGrid();
  }

  /**
   * @brief Inicia o processamento paralelo da rota via Web Worker.
   */
  @Audit()
  protected startSimulation(): void {
    if (this.isSimulating()) return;
    
    this.isSimulating.set(true);
    this.statusMessage.set('CALCULANDO TRAJETÓRIA ÓTIMA...');
    this.voiceService.speak('Iniciando cálculos de trajetória multithread.');

    // Reutilizando lógica de Worker para cálculo de trajetória
    this.worker = new Worker(new URL('../atividade24/worker/routing.worker', import.meta.url));
    
    this.worker.onmessage = ({ data }) => {
      if (data.type === 'RESULT') {
        this.generateFlightData();
      }
    };

    this.worker.postMessage({ complexity: 50000000 });
  }

  private generateFlightData(): void {
    const points: FlightPoint[] = [];
    for (let i = 0; i < 20; i++) {
      points.push({
        x: 50 + (i * 25),
        y: 350 - (Math.sin(i * 0.5) * 100 + Math.random() * 50),
        altitude: Math.floor(Math.random() * 5000) + 1000
      });
    }
    this.flightPath.set(points);
    this.statusMessage.set('ROTA CALCULADA. INICIANDO VOO.');
    this.voiceService.speak('Rota calculada. Iniciando visualização de voo.');
    this.animateFlight();
  }

  private animateFlight(): void {
    let step = 0;
    const path = this.flightPath();
    
    const render = () => {
      if (step >= path.length) {
        this.isSimulating.set(false);
        this.statusMessage.set('MISSÃO CONCLUÍDA.');
        this.voiceService.speak('Simulação de voo concluída com sucesso.');
        return;
      }

      this.drawFrame(path.slice(0, step + 1));
      step++;
      this.animationId = requestAnimationFrame(render);
    };
    render();
  }

  private drawFrame(currentPath: FlightPoint[]): void {
    const { width, height } = this.canvasRef.nativeElement;
    this.ctx.clearRect(0, 0, width, height);
    this.drawBaseGrid();

    // Desenha a linha de trajetória
    this.ctx.strokeStyle = '#58a6ff';
    this.ctx.lineWidth = 3;
    this.ctx.setLineDash([5, 5]);
    this.ctx.beginPath();
    
    currentPath.forEach((p, i) => {
      if (i === 0) this.ctx.moveTo(p.x, p.y);
      else this.ctx.lineTo(p.x, p.y);
    });
    this.ctx.stroke();

    // Desenha a unidade Nexus (Drone) no ponto atual
    const last = currentPath[currentPath.length - 1];
    this.ctx.fillStyle = '#f1e05a';
    this.ctx.shadowBlur = 15;
    this.ctx.shadowColor = '#f1e05a';
    this.ctx.beginPath();
    this.ctx.arc(last.x, last.y, 6, 0, Math.PI * 2);
    this.ctx.fill();
    this.ctx.shadowBlur = 0;

    // Telemetria local no Canvas
    this.ctx.fillStyle = '#fff';
    this.ctx.font = '10px monospace';
    this.ctx.fillText(`ALT: ${last.altitude}ft`, last.x + 10, last.y - 10);
  }

  private drawBaseGrid(): void {
    this.ctx.strokeStyle = '#161b22';
    this.ctx.lineWidth = 1;
    this.ctx.setLineDash([]);
    for(let i=0; i<600; i+=40) {
      this.ctx.beginPath(); this.ctx.moveTo(i, 0); this.ctx.lineTo(i, 400); this.ctx.stroke();
      this.ctx.beginPath(); this.ctx.moveTo(0, i); this.ctx.lineTo(600, i); this.ctx.stroke();
    }
  }

  protected abortMission(): void {
    if (this.animationId) cancelAnimationFrame(this.animationId);
    this.worker?.terminate();
    this.isSimulating.set(false);
    this.statusMessage.set('MISSÃO ABORTADA PELO OPERADOR.');
    this.voiceService.speak('Protocolo de abortagem executado.');
  }

  protected startVoice(): void {
    this.voiceService.listen();
  }

  ngOnDestroy(): void {
    if (this.animationId) cancelAnimationFrame(this.animationId);
    this.worker?.terminate();
  }

  /* @section ArchitectureMap
   * Fusão de Tecnologias (Nível 30):
   * 1. Web Workers -> Processamento pesado de rota tática.
   * 2. HTML5 Canvas -> Renderização acelerada da trajetória.
   * 3. Web Speech -> Interface Zero-Touch para comando e controle.
   * 4. Custom Decorators -> Auditoria automática de performance de missão.
   * 5. Signals -> Orquestração de estado entre threads e interfaces.
   */
}

/*
 * RESUMO TEÓRICO
 * O Desafio Integrador do Nível Engenheiro valida a capacidade de projetar sistemas 
 * que operam no limite do navegador. Ao combinar processamento paralelo, 
 * renderização imperativa e interfaces sensoriais, o engenheiro prova que o Angular 
 * não é apenas para formulários, mas para sistemas de visualização de missão crítica.
 */
