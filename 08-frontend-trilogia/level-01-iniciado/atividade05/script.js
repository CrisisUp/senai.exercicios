/**
 * @file script.js
 * @brief Lógica Condicional e Manipulação Dinâmica (Atividade 05).
 */

let bateria = 100;

/**
 * @brief Monitora o estado da bateria e aplica alertas visuais.
 */
function validarIntegridade() {
    const painel = document.getElementById('status-panel');
    const msg = document.getElementById('status-msg');
    const batDisplay = document.getElementById('bat-val');

    batDisplay.innerText = bateria;

    // ESTRUTURA CONDICIONAL (A tomada de decisão)
    if (bateria < 20) {
        painel.className = "status-card perigo";
        msg.innerText = "ALERTA: BATERIA CRÍTICA";
        console.warn("[SYSTEM] Risco de queda detectado!");
    } else if (bateria < 50) {
        painel.className = "status-card normal";
        msg.innerText = "NÍVEL BAIXO";
        console.log("[SYSTEM] Recomenda-se recarga em breve.");
    } else {
        painel.className = "status-card normal";
        msg.innerText = "OPERACIONAL";
        console.log("[SYSTEM] Sistemas estáveis.");
    }
}

/**
 * @brief Captura o valor do input e atualiza o nome do drone.
 */
function atualizarNome() {
    const input = document.getElementById('callsign-input');
    const displayNome = document.getElementById('drone-name');

    if (input.value !== "") {
        displayNome.innerText = input.value.toUpperCase();
        console.log(`[CONFIG] Novo Callsign: ${input.value}`);
        input.value = ""; // Limpa o campo
    } else {
        alert("Erro: O nome do drone não pode estar vazio.");
    }
}

function simularGasto() {
    bateria = bateria - 30;
    if (bateria < 0) bateria = 0;
    validarIntegridade();
}

function simularCarga() {
    bateria = 100;
    validarIntegridade();
}

// Inicialização
validarIntegridade();
