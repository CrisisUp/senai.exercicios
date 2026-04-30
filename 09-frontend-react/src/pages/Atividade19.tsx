import React, { useState } from 'react';
import styles from './Atividade19.module.css';

interface WeatherData {
  city: string;
  temp: number;
  description: string;
}

/**
 * @page Atividade19
 * @brief Monitor de Clima Global usando Async/Await e APIs Reais.
 */
const Atividade19: React.FC = () => {
  const [cityInput, setCityInput] = useState('');
  const [weather, setWeather] = useState<WeatherData | null>(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const buscarClima = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!cityInput.trim()) return;

    setLoading(true);
    setError(null);
    setWeather(null);

    try {
      // 1. Geocoding: Busca latitude e longitude da cidade
      const geoRes = await fetch(`https://geocoding-api.open-meteo.com/v1/search?name=${cityInput}&count=1&language=pt&format=json`);
      const geoData = await geoRes.json();

      if (!geoData.results || geoData.results.length === 0) {
        throw new Error("CIDADE NÃO ENCONTRADA NA REDE SATELITAL.");
      }

      const { latitude, longitude, name } = geoData.results[0];

      // 2. Weather: Busca o clima atual
      const weatherRes = await fetch(`https://api.open-meteo.com/v1/forecast?latitude=${latitude}&longitude=${longitude}&current_weather=true`);
      const weatherData = await weatherRes.json();

      setWeather({
        city: name,
        temp: weatherData.current_weather.temperature,
        description: "CONDIÇÕES OPERACIONAIS NOMINAIS"
      });
    } catch (err: any) {
      setError(err.message || "FALHA NA CONEXÃO COM O NUCLEO METEOROLÓGICO.");
    } finally {
      setLoading(false);
    }
  };

  const getBgClass = () => {
    if (!weather) return styles.normal;
    return weather.temp > 25 ? styles.quente : styles.frio;
  };

  return (
    <div className={`${styles.container} ${getBgClass()}`}>
      <header className={styles.header}>
        <h1>O Nexus Vivo</h1>
        <p>Integração de APIs Reais com Async/Await e Try/Catch.</p>
      </header>

      <main>
        <div className={styles.card}>
          <form onSubmit={buscarClima} className={styles.searchBox}>
            <input 
              type="text" 
              placeholder="Digite a cidade (ex: Dubai, Tokyo...)" 
              value={cityInput}
              onChange={(e) => setCityInput(e.target.value)}
            />
            <button type="submit" disabled={loading}>
              {loading ? 'BUSCANDO...' : 'SINCRONIZAR'}
            </button>
          </form>

          <div className={styles.weatherDisplay}>
            {loading && <div className={styles.loading}>[ SINCRONIZANDO COM SATÉLITE... ]</div>}
            
            {error && <div className={styles.error}>[ ERRO ] {error}</div>}

            {weather && (
              <>
                <div className={styles.city}>{weather.city}</div>
                <div className={styles.temp}>{weather.temp}°C</div>
                <div className={styles.info}>{weather.description}</div>
              </>
            )}

            {!loading && !error && !weather && (
              <div className={styles.info}>Aguardando coordenadas de destino...</div>
            )}
          </div>
        </div>

        <footer className={styles.theoryBox}>
          <h4>Nota do Arquiteto: Async/Await</h4>
          <p>
            O <code>async/await</code> transforma o código assíncrono em algo linear e fácil de ler. 
            O bloco <code>try/catch</code> é essencial: se a API falhar ou a internet cair, 
            o sistema captura o erro e evita o "crash" da interface, mantendo a experiência do usuário resiliente.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade19;
