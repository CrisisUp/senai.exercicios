/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Processamento Avançado: Regex, Datas e Strings (Atividade 17).
 */

/**
 * @brief Valida o ID do drone usando Expressões Regulares (Regex).
 * Padrão exigido: 5 Letras Maiúsculas, um traço, 3 Números (Ex: ALPHA-707)
 */
function validarID() {
    const input = document.getElementById('drone-id');
    const msg = document.getElementById('validation-msg');
    const valor = input.value.trim(); // Limpeza de strings (Atividade 17)

    // A REGEX DE ELITE
    const regexPadrão = /^[A-Z]{5}-\d{3}$/;

    if (valor === "") {
        msg.innerText = "Aguardando entrada...";
        msg.className = "feedback";
    } else if (regexPadrão.test(valor)) {
        msg.innerText = "ID VALIDADO: PADRÃO INDUSTRIAL CORRETO.";
        msg.className = "feedback valid";
        console.log(`[VALIDATION] ID Aceito: ${valor}`);
    } else {
        msg.innerText = "ERRO: O PADRÃO DEVE SER 'ABCDE-123'.";
        msg.className = "feedback invalid";
    }
}

/**
 * @brief Formata a data atual no padrão brasileiro industrial.
 */
function obterDataFormatada() {
    const agora = new Date();
    
    // Métodos de Data (Atividade 17)
    const dia = String(agora.getDate()).padStart(2, '0');
    const mes = String(agora.getMonth() + 1).padStart(2, '0'); // Mês inicia em 0
    const ano = agora.getFullYear();
    const hora = String(agora.getHours()).padStart(2, '0');
    const min = String(agora.getMinutes()).padStart(2, '0');
    const seg = String(agora.getSeconds()).padStart(2, '0');

    return `${dia}/${mes}/${ano} - ${hora}:${min}:${seg}`;
}

/**
 * @brief Registra um log saneado e com timestamp.
 */
function registrarLog() {
    const logInput = document.getElementById('log-input');
    const auditView = document.getElementById('audit-log');
    
    // Saneamento de String: remove espaços extras e normaliza para MAIÚSCULO
    let textoLog = logInput.value.trim().toUpperCase();

    if (textoLog !== "") {
        const timestamp = obterDataFormatada();
        
        // Adiciona ao terminal com a nova data e o texto processado
        const novaEntrada = `\n> [${timestamp}] ${textoLog}`;
        auditView.textContent += novaEntrada;

        // Limpa e rola o scroll
        logInput.value = "";
        auditView.scrollTop = auditView.scrollHeight;
        
        console.log(`[AUDIT] Log registrado: ${textoLog}`);
    }
}

// Inicialização: Atualiza o tempo na tela
document.getElementById('current-time').innerText = obterDataFormatada();
// Atualização contínua do tempo (Ativ 08 + 17)
setInterval(() => {
    document.getElementById('current-time').innerText = obterDataFormatada();
}, 1000);

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
