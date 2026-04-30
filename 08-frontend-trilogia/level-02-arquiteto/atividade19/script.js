/**
 * @file script.js
 * @brief Orquestração de APIs Reais com Async/Await (Atividade 19).
 */

/**
 * @brief Função Mestre de Sincronização Meteorológica.
 */
async function sincronizarClima() {
    const input = document.getElementById('city-input');
    const displayArea = document.getElementById('display-area');
    const loader = document.getElementById('loader');
    const body = document.getElementById('dynamic-bg');

    const cidade = input.value.trim();
    if (!cidade) {
        alert("ERRO: Informe a cidade para sincronia.");
        return;
    }

    // 1. ESTADO DE CARREGAMENTO
    displayArea.style.opacity = "0.3";
    loader.style.display = "block";
    console.log(`[NETWORK] Iniciando Handshake para: ${cidade}`);

    try {
        // 2. ETAPA 1: Geocodificação (Transformar nome em Lat/Lon)
        const geoRes = await fetch(`https://geocoding-api.open-meteo.com/v1/search?name=${cidade}&count=1&language=pt&format=json`);
        const geoData = await geoRes.json();

        if (!geoData.results) throw new Error("Cidade não localizada no mapa global.");
        const { latitude, longitude, name } = geoData.results[0];

        // 3. ETAPA 2: Busca de Clima Real
        const weatherRes = await fetch(`https://api.open-meteo.com/v1/forecast?latitude=${latitude}&longitude=${longitude}&current_weather=true`);
        const weatherData = await weatherRes.json();
        
        const temp = weatherData.current_weather.temperature;

        // 4. ATUALIZAÇÃO DA INTERFACE (Lógica Reativa)
        document.getElementById('city-name').innerText = name.toUpperCase();
        document.getElementById('temp-val').innerText = temp;
        document.getElementById('lat-val').innerText = latitude.toFixed(2);
        document.getElementById('lon-val').innerText = longitude.toFixed(2);
        document.getElementById('weather-desc').innerText = "CONEXÃO ESTÁVEL VIA SATÉLITE";

        // 5. TROCA DE TEMA (Visual Inteligente)
        if (temp > 25) {
            body.className = "bg-hot";
            console.log("[SYSTEM] Ambiente de alta temperatura detectado.");
        } else {
            body.className = "bg-cold";
            console.log("[SYSTEM] Operação em clima frio.");
        }

    } catch (error) {
        // TRATAMENTO DE ELITE: Captura qualquer falha nas etapas acima
        console.error("[CRITICAL] " + error.message);
        document.getElementById('city-name').innerText = "FALHA NO LINK";
        document.getElementById('weather-desc').innerText = error.message;
        body.className = ""; // Volta ao neutro
    } finally {
        // FINALIZAÇÃO
        loader.style.display = "none";
        displayArea.style.opacity = "1";
        input.value = ""; // Limpa campo
    }
}

console.log("[SYSTEM] Meteorological Engine v3.0 Online.");
