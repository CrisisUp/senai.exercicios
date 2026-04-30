/**
 * @file script.js
 * @brief Renderização em Lote com DocumentFragment (Atividade 14).
 */

const grid = document.getElementById('main-grid');
const timerDisplay = document.getElementById('render-timer');
const counterDisplay = document.getElementById('sensor-count');

/**
 * @brief Gera múltiplos sensores de forma atômica e performática.
 * @param quantidade Número de sensores a serem criados.
 */
function gerarSensores(quantidade) {
    const t0 = performance.now(); // Marca o início da execução

    // 1. O FRAGMENTO: Container invisível na memória
    const fragmento = document.createDocumentFragment();

    for (let i = 1; i <= quantidade; i++) {
        // Criamos o elemento
        const sensor = document.createElement('div');
        sensor.className = "sensor-box";
        
        // Geramos dados aleatórios de telemetria
        const valor = (Math.random() * 100).toFixed(2);
        
        sensor.innerHTML = `
            <strong>SENSOR_${Math.floor(Math.random() * 9999)}</strong><br>
            READING: ${valor} units<br>
            STATUS: ACTIVE
        `;

        // 2. ANEXAR AO FRAGMENTO (Ainda não tocou no DOM real)
        fragmento.appendChild(sensor);
    }

    // 3. TIRO ÚNICO: Insere 100 itens no DOM de uma só vez
    // Isso causa apenas 1 Reflow em vez de 100.
    grid.appendChild(fragmento);

    const t1 = performance.now(); // Marca o fim
    
    // Atualização das métricas de Elite
    timerDisplay.innerText = (t1 - t0).toFixed(2) + "ms";
    counterDisplay.innerText = grid.children.length;

    console.log(`[PERF] ${quantidade} sensores renderizados em ${t1 - t0}ms.`);
}

function limparSensores() {
    grid.innerHTML = "";
    counterDisplay.innerText = "0";
    timerDisplay.innerText = "0ms";
}

// Inicializa com uma carga leve
gerarSensores(12);
