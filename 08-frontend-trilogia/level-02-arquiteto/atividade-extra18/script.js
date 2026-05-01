/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Orquestração Assíncrona via Promises e Event Loop (Atividade 18).
 */

/**
 * @brief Simula um Handshake de Satélite.
 * Retorna uma Promise que resolve após 3 segundos ou falha aleatoriamente.
 */
function requisitarLinkSatelite() {
    return new Promise((resolve, reject) => {
        console.log("[PROMISE] Handshake iniciado...");
        
        // Simula latência de rede industrial
        setTimeout(() => {
            const sucesso = Math.random() > 0.15; // 85% de chance de sucesso

            if (sucesso) {
                resolve({
                    id: "HANGAR-01-DX",
                    integridade: "99.8%",
                    tipo: "SATELLITE-LINK"
                });
            } else {
                reject("TIMEOUT: Falha na resposta do satélite.");
            }
        }, 3000);
    });
}

/**
 * @brief Orquestrador de UI para o processo de conexão.
 */
function iniciarHandshake() {
    const btn = document.getElementById('btn-connect');
    const led = document.getElementById('status-led');
    const statusTxt = document.getElementById('status-text');
    const skeleton = document.getElementById('skeleton');
    const dataView = document.getElementById('data-view');

    // 1. ESTADO: CONNECTING
    btn.disabled = true;
    led.className = "led connecting";
    statusTxt.innerText = "ESTABELECENDO LINK...";
    skeleton.style.display = "block";
    dataView.style.display = "none";

    // 2. CONSUMINDO A PROMESSA
    requisitarLinkSatelite()
        .then(dados => {
            // SUCESSO: Resolve()
            led.className = "led online";
            statusTxt.innerText = "LINK ESTABELECIDO";
            
            document.getElementById('link-type').innerText = dados.tipo;
            document.getElementById('integrity-val').innerText = dados.integridade;
            
            skeleton.style.display = "none";
            dataView.style.display = "block";
            console.log("%c[NETWORK] Conexão estável.", "color: #2ea043; font-weight: bold;");
        })
        .catch(erro => {
            // FALHA: Reject()
            led.className = "led error";
            statusTxt.innerText = "FALHA NO SINAL";
            console.error("[NETWORK] " + erro);
            alert("ERRO CRÍTICO: " + erro);
        })
        .finally(() => {
            // SEMPRE EXECUTA AO FINAL (Limpeza)
            btn.disabled = false;
            console.log("[SYSTEM] Ciclo de requisição finalizado.");
        });
}

console.log("[SYSTEM] Engine Assíncrona Ativa.");

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
