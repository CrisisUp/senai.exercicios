import React, { useState, useEffect, useCallback } from 'react';
import styles from './Atividade25.module.css';

interface Coords {
  lat: number | null;
  lon: number | null;
  accuracy: number | null;
}

type GPSStatus = 'IDLE' | 'SCANNING' | 'LOCKED' | 'ERROR';

/**
 * @page Atividade25
 * @brief Consciência Espacial via Web Geolocation API.
 */
const Atividade25: React.FC = () => {
  const [coords, setCoords] = useState<Coords>({ lat: null, lon: null, accuracy: null });
  const [status, setStatus] = useState<GPSStatus>('IDLE');
  const [errorMsg, setErrorMsg] = useState<string>('');

  const sincronizarLocalizacao = useCallback(() => {
    setStatus('SCANNING');
    setErrorMsg('');

    if (!navigator.geolocation) {
      setStatus('ERROR');
      setErrorMsg('ERRO: SENSOR GPS NÃO DETECTADO NESTE TERMINAL.');
      return;
    }

    const options: PositionOptions = {
      enableHighAccuracy: true,
      timeout: 10000,
      maximumAge: 0
    };

    navigator.geolocation.getCurrentPosition(
      (position) => {
        setCoords({
          lat: position.coords.latitude,
          lon: position.coords.longitude,
          accuracy: position.coords.accuracy
        });
        setStatus('LOCKED');
      },
      (error) => {
        setStatus('ERROR');
        switch (error.code) {
          case error.PERMISSION_DENIED:
            setErrorMsg('ACESSO NEGADO: PERMISSÃO DE GPS REJEITADA.');
            break;
          case error.TIMEOUT:
            setErrorMsg('TIMEOUT: SINAL DE SATÉLITE MUITO FRACO.');
            break;
          default:
            setErrorMsg('FALHA CRÍTICA: ERRO NA SINCRONIA GEOGRÁFICA.');
        }
      },
      options
    );
  }, []);

  useEffect(() => {
    sincronizarLocalizacao();
  }, [sincronizarLocalizacao]);

  const getMapUrl = () => {
    if (coords.lat === null || coords.lon === null) {
      // Mapa padrão (vazio/carregando)
      return "https://via.placeholder.com/600x400/010409/00f2ff?text=SINCRONIZANDO+COORDENADAS...";
    }
    // Usando Yandex Static Maps para visual de satélite (conforme original)
    return `https://static-maps.yandex.ru/1.x/?lang=en_US&ll=${coords.lon},${coords.lat}&z=15&l=sat&size=600,400`;
  };

  const getLedClass = () => {
    switch (status) {
      case 'SCANNING': return styles.ledScanning;
      case 'LOCKED': return styles.ledLocked;
      default: return styles.ledIdle;
    }
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Consciência Espacial</h1>
        <p>Monitoramento de Coordenadas Globais via Geolocation API.</p>
      </header>

      <main>
        <div className={styles.gpsStatus}>
          <div className={`${styles.led} ${getLedClass()}`}></div>
          <span>GPS STATUS: {status === 'ERROR' ? errorMsg : status}</span>
        </div>

        <div className={styles.mapBox}>
          <figure className={styles.mapFigure}>
            <div className={styles.crosshair}></div>
            <img 
              src={getMapUrl()} 
              alt="Mapa Tático Satelital" 
              className={styles.staticMap}
            />
            <figcaption className={styles.mapCaption}>
              {status === 'LOCKED' 
                ? `FOCO: ${coords.lat?.toFixed(6)}, ${coords.lon?.toFixed(6)}`
                : "AGUARDANDO TRAVA DE SATÉLITE..."}
            </figcaption>
          </figure>
        </div>

        <div className={styles.geoStats}>
          <div className={styles.stat}>
            <label>Latitude</label>
            <span>{coords.lat?.toFixed(6) || "0.000000"}</span>
          </div>
          <div className={styles.stat}>
            <label>Longitude</label>
            <span>{coords.lon?.toFixed(6) || "0.000000"}</span>
          </div>
          <div className={styles.stat}>
            <label>Precisão</label>
            <span>{coords.accuracy?.toFixed(0) || "0"}m</span>
          </div>
        </div>

        <button className={styles.btnAction} onClick={sincronizarLocalizacao}>
          RE-SINCRONIZAR POSIÇÃO
        </button>

        <footer className={styles.theoryBox}>
          <h4>Nota do Engenheiro: Geoprocessamento Web</h4>
          <p>
            A <strong>Geolocation API</strong> permite que aplicações web acessem o hardware de posicionamento do dispositivo.
            Utilizamos o <code>enableHighAccuracy</code> para forçar o uso do GPS em vez de apenas triangulação de rede.
            <br /><br />
            Em sistemas industriais, a precisão (accuracy) é vital: um erro de 100 metros pode significar a perda de um drone. 
            O React nos permite reagir instantaneamente a cada mudança de posição, mantendo o mapa tático sempre centralizado.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade25;
