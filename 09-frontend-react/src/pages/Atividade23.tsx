/**
 * @file Atividade23.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState, useRef, useEffect } from 'react';
import styles from './Atividade23.module.css';

/**
 * @page Atividade23
 * @brief Sinais Sonoros: Mastering Web Audio API no React.
 */
const Atividade23: React.FC = () => {
  const [isEngineActive, setIsEngineActive] = useState(false);
  const [volume, setVolume] = useState(0.5);
  
  const audioCtxRef = useRef<AudioContext | null>(null);
  const masterGainRef = useRef<GainNode | null>(null);

  /**
   * @brief Inicializa o motor de áudio.
   * Navegadores exigem interação do usuário para ativar o AudioContext.
   */
  const inicializarAudio = () => {
    if (audioCtxRef.current) return;

    const Context = window.AudioContext || (window as unknown as { webkitAudioContext: typeof AudioContext }).webkitAudioContext;
    const ctx = new Context();
    
    const gainNode = ctx.createGain();
    gainNode.gain.value = volume;
    gainNode.connect(ctx.destination);

    audioCtxRef.current = ctx;
    masterGainRef.current = gainNode;
    setIsEngineActive(true);
  };

  /**
   * @brief Síntese de sinal sonoro puro.
   */
  const tocarBipe = (freq: number, tipo: OscillatorType = 'sine', duracao: number = 0.2) => {
    const ctx = audioCtxRef.current;
    const masterGain = masterGainRef.current;
    if (!ctx || !masterGain) return;

    const osc = ctx.createOscillator();
    const nodeGain = ctx.createGain();

    osc.type = tipo;
    osc.frequency.setValueAtTime(freq, ctx.currentTime);

    // Envelope de Amplitude (ADSR simplificado para evitar cliques)
    nodeGain.gain.setValueAtTime(0, ctx.currentTime);
    nodeGain.gain.linearRampToValueAtTime(masterGain.gain.value, ctx.currentTime + 0.01);
    nodeGain.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + duracao);

    osc.connect(nodeGain);
    nodeGain.connect(ctx.destination); // Conecta direto ou via masterGain se preferir

    osc.start();
    osc.stop(ctx.currentTime + duracao);
  };

  const tocarSinal = (tipo: 'NORMAL' | 'WARNING' | 'CRITICAL') => {
    if (!isEngineActive) {
      inicializarAudio();
      // Pequeno delay para garantir que o contexto iniciou antes do primeiro bipe
      setTimeout(() => dispararSom(tipo), 50);
    } else {
      dispararSom(tipo);
    }
  };

  const dispararSom = (tipo: 'NORMAL' | 'WARNING' | 'CRITICAL') => {
    switch (tipo) {
      case 'NORMAL':
        tocarBipe(880, 'sine', 0.1);
        break;
      case 'WARNING':
        tocarBipe(440, 'triangle', 0.4);
        break;
      case 'CRITICAL': {
        // Sirene Industrial
        [0, 0.6, 1.2].forEach((delay) => {
          setTimeout(() => tocarBipe(440, 'sawtooth', 0.3), delay * 1000);
          setTimeout(() => tocarBipe(880, 'sawtooth', 0.3), (delay + 0.3) * 1000);
        });
        break;
      }
    }
  };

  const handleVolumeChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const newVol = parseFloat(e.target.value);
    setVolume(newVol);
    if (masterGainRef.current && audioCtxRef.current) {
      masterGainRef.current.gain.setTargetAtTime(newVol, audioCtxRef.current.currentTime, 0.05);
    }
  };

  // Cleanup ao desmontar
  useEffect(() => {
    return () => {
      if (audioCtxRef.current) {
        audioCtxRef.current.close();
      }
    };
  }, []);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Sinais Sonoros Táticos</h1>
        <p>Sintetizador de Áudio em Tempo Real (Web Audio API).</p>
      </header>

      <main className={styles.audioPanel}>
        <section className={styles.card}>
          <div className={`${styles.led} ${isEngineActive ? styles.ledActive : ''}`}></div>
          <div className={styles.engineText}>
            AUDIO ENGINE: {isEngineActive ? 'OPERATIONAL' : 'IDLE'}
          </div>
          
          {!isEngineActive && (
            <button className={styles.btnStart} onClick={inicializarAudio}>
              ATIVAR SUBSISTEMA DE ÁUDIO
            </button>
          )}

          <div className={styles.volumeControl}>
            <label htmlFor="volume">Volume Mestre</label>
            <input 
              type="range" 
              id="volume" 
              min="0" 
              max="1" 
              step="0.01" 
              value={volume} 
              className={styles.slider}
              onChange={handleVolumeChange}
            />
            <span className={styles.volumeVal}>{Math.round(volume * 100)}%</span>
          </div>
        </section>

        <section className={styles.tacticalButtons}>
          <button className={styles.btnTactical} onClick={() => tocarSinal('NORMAL')}>
            DETECÇÃO NOMINAL (BIPE)
          </button>
          <button className={styles.btnTactical} onClick={() => tocarSinal('WARNING')}>
            ALERTA DE PROXIMIDADE
          </button>
          <button className={`${styles.btnTactical} ${styles.btnAlert}`} onClick={() => tocarSinal('CRITICAL')}>
            EMERGÊNCIA CRÍTICA (SIRENE)
          </button>
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: Síntese vs Samples</h4>
          <p>
            Em sistemas de missão crítica, usamos a <strong>Web Audio API</strong> para gerar som via código (síntese) 
            em vez de carregar arquivos MP3. Isso garante:
            <br /><br />
            1. <strong>Latência Zero</strong>: O som é gerado instantaneamente pela CPU/GPU.
            <br />
            2. <strong>Controle Total</strong>: Podemos alterar a frequência (Pitch) e o timbre em tempo real.
            <br />
            3. <strong>Resiliência</strong>: O sistema funciona mesmo sem conexão de rede para baixar arquivos de áudio.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade23;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
