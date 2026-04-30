import React, { useState, useEffect, useRef } from 'react';
import styles from './Atividade27.module.css';

type VisionMode = 'normal' | 'night' | 'thermal' | 'grayscale';

/**
 * @page Atividade27
 * @brief Visão Tática: Mastering MediaDevices API no React.
 */
const Atividade27: React.FC = () => {
  const [mode, setMode] = useState<VisionMode>('normal');
  const [streamStatus, setStreamStatus] = useState<'OFFLINE' | 'ONLINE' | 'DENIED'>('OFFLINE');
  const [snapshots, setSnapshots] = useState<string[]>([]);
  
  const videoRef = useRef<HTMLVideoElement>(null);
  const canvasRef = useRef<HTMLCanvasElement>(null);

  /**
   * @brief Inicializa o link de vídeo com o hardware.
   */
  const startStream = async () => {
    try {
      const stream = await navigator.mediaDevices.getUserMedia({
        video: { width: 1280, height: 720 },
        audio: false
      });

      if (videoRef.current) {
        videoRef.current.srcObject = stream;
        setStreamStatus('ONLINE');
      }
    } catch (err) {
      console.error("[CRITICAL] Falha no link de vídeo:", err);
      setStreamStatus('DENIED');
    }
  };

  /**
   * @brief Interrompe o fluxo de vídeo e limpa os recursos.
   */
  const stopStream = () => {
    if (videoRef.current && videoRef.current.srcObject) {
      const stream = videoRef.current.srcObject as MediaStream;
      const tracks = stream.getTracks();
      tracks.forEach(track => track.stop());
      videoRef.current.srcObject = null;
      setStreamStatus('OFFLINE');
    }
  };

  useEffect(() => {
    startStream();
    return () => stopStream();
  }, []);

  const getVisionClass = () => {
    switch (mode) {
      case 'night': return styles.visionNight;
      case 'thermal': return styles.visionThermal;
      case 'grayscale': return styles.visionGrayscale;
      default: return '';
    }
  };

  const captureSnapshot = () => {
    const video = videoRef.current;
    const canvas = canvasRef.current;
    if (!video || !canvas) return;

    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    // Sincroniza tamanho do canvas com o vídeo atual
    canvas.width = video.videoWidth;
    canvas.height = video.videoHeight;

    // Aplica o filtro atual ao canvas para que a foto saia com o modo de visão
    const filterMap: Record<VisionMode, string> = {
      normal: 'none',
      night: 'sepia(1) hue-rotate(70deg) brightness(1.2) contrast(1.2) grayscale(0.5)',
      thermal: 'invert(1) hue-rotate(180deg) brightness(1.1) contrast(1.5)',
      grayscale: 'grayscale(1) brightness(0.8) contrast(1.2)'
    };
    ctx.filter = filterMap[mode];

    ctx.drawImage(video, 0, 0, canvas.width, canvas.height);
    const dataUrl = canvas.toDataURL('image/png');
    setSnapshots(prev => [dataUrl, ...prev]);
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Visão Tática FPV</h1>
        <p>Monitoramento Óptico em Tempo Real (MediaDevices API).</p>
      </header>

      <main>
        <div className={styles.streamContainer}>
          <video 
            ref={videoRef} 
            autoPlay 
            playsInline 
            className={`${styles.videoStream} ${getVisionClass()}`}
          />
          
          <div className={styles.overlay}>
            <div className={styles.overlayTop}>
              <span>SIGNAL: {streamStatus}</span>
              <span>HD 720P</span>
            </div>
            <div className={styles.overlayBottom}>
              <span>MODE: {mode.toUpperCase()}</span>
              <span>REC ●</span>
            </div>
          </div>

          {streamStatus === 'DENIED' && (
            <div style={{ position: 'absolute', top: '50%', left: '50%', transform: 'translate(-50%, -50%)', color: '#ef4444' }}>
              ACESSO À CÂMERA NEGADO PELO OPERADOR
            </div>
          )}
        </div>

        <div className={styles.controls}>
          <button className={styles.btnAction} onClick={() => setMode('normal')}>VISÃO NORMAL</button>
          <button className={styles.btnAction} onClick={() => setMode('night')}>VISÃO NOTURNA</button>
          <button className={styles.btnAction} onClick={() => setMode('thermal')}>VISÃO TÉRMICA</button>
          <button className={styles.btnAction} onClick={() => setMode('grayscale')}>B&W TÁTICO</button>
          <button className={`${styles.btnAction} ${styles.btnCapture}`} onClick={captureSnapshot}>CAPTURAR EVIDÊNCIA</button>
        </div>

        <canvas ref={canvasRef} style={{ display: 'none' }} />

        {snapshots.length > 0 && (
          <div className={styles.gallery}>
            {snapshots.map((src, idx) => (
              <img key={idx} src={src} alt={`Snapshot ${idx}`} />
            ))}
          </div>
        )}

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: Fluxos Multimídia</h4>
          <p>
            A <strong>MediaDevices API</strong> é o ponto de contato direto com o hardware óptico do terminal. 
            No React, gerenciamos o ciclo de vida do fluxo (<i>stream</i>) através do <code>useEffect</code>, 
            garantindo que a câmera seja desligada quando o usuário sair da página (cleanup).
            <br /><br />
            Os <strong>Filtros CSS</strong> aplicados diretamente sobre o elemento <code>&lt;video&gt;</code> 
            permitem processamento visual em tempo real sem sobrecarga de CPU, aproveitando a aceleração da GPU do navegador.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade27;
