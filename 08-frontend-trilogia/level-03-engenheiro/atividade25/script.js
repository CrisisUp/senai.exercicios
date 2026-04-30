/**
 * @file script.js
 * @brief Consciência Espacial via Geolocation API (Atividade 25).
 * @author Engenheiro de Elite
 */

const led = document.getElementById('gps-led');
const label = document.getElementById('gps-label');
const mapImg = document.getElementById('static-map');

/**
 * @brief Orquestra o escaneamento de posição via sensores do dispositivo.
 */
function sincronizarLocalizacao() {
    console.log("[GPS] Iniciando busca por sinal de satélite...");
    
    // UI: ESTADO SCANNING
    led.className = "led scanning";
    label.innerText = "SCANNING";
    document.getElementById('coords-log').innerText = "SINCRONIZANDO...";

    // 1. VERIFICAÇÃO DE SUPORTE
    if (!navigator.geolocation) {
        alert("ERRO: Este terminal não possui sensores de geolocalização.");
        return;
    }

    // 2. CONFIGURAÇÃO DE ELITE
    const options = {
        enableHighAccuracy: true, // Solicita precisão de hardware (GPS)
        timeout: 10000,           // 10 segundos de espera máxima
        maximumAge: 0             // Não aceita dados cacheados/antigos
    };

    // 3. CAPTURA DE COORDENADAS (Assíncrona)
    navigator.geolocation.getCurrentPosition(sucessoGPS, falhaGPS, options);
}

/**
 * @brief Callback disparado quando o sinal é travado.
 */
function sucessoGPS(position) {
    const { latitude, longitude, accuracy } = position.coords;

    console.log(`%c[GPS LOCK] LAT: ${latitude} | LON: ${longitude}`, "color: #2ea043; font-weight: bold;");

    // UI: ESTADO LOCKED
    led.className = "led locked";
    label.innerText = "LOCKED";
    
    // Atualização dos Displays
    document.getElementById('lat-val').innerText = latitude.toFixed(6);
    document.getElementById('lon-val').innerText = longitude.toFixed(6);
    document.getElementById('acc-val').innerText = accuracy.toFixed(0);
    document.getElementById('coords-log').innerText = `LOCKED: ${latitude.toFixed(4)}, ${longitude.toFixed(4)}`;

    // 4. INTEGRAÇÃO DE MAPA (Simulação de satélite real)
    // Usaremos o serviço OpenStreetMap (Estático)
    const zoom = 15;
    const urlMapa = `https://static-maps.yandex.ru/1.x/?lang=en_US&ll=${longitude},${latitude}&z=${zoom}&l=sat&size=600,400`;
    mapImg.src = urlMapa;
}

/**
 * @brief Callback disparado em caso de perda de sinal ou negação.
 */
function falhaGPS(error) {
    console.error("[GPS ERROR] " + error.message);
    led.className = "led idle";
    label.innerText = "NO SIGNAL";
    
    let msg = "FALHA NO SINAL: ";
    switch(error.code) {
        case error.PERMISSION_DENIED: msg += "Acesso negado pelo operador."; break;
        case error.TIMEOUT: msg += "Tempo de busca excedido."; break;
        default: msg += "Inconsistência de dados.";
    }
    
    alert(msg);
    document.getElementById('coords-log').innerText = "ERRO DE POSICIONAMENTO";
}

// Inicia escaneamento automático no boot
sincronizarLocalizacao();
