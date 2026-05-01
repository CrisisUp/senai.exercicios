/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Lógica de Persistência via JSON e LocalStorage (Atividade 10).
 */

// 1. CARREGAMENTO INICIAL (Recuperando a memória)
window.onload = () => {
    // Recupera o nome do operador
    const nomeSalvo = localStorage.getItem('nexus_operador');
    if (nomeSalvo) {
        document.getElementById('perfil-status').innerText = `Operador Identificado: ${nomeSalvo}`;
        console.log(`[STORAGE] Perfil carregado: ${nomeSalvo}`);
    }

    // Recupera os logs históricos
    carregarLogs();
};

/**
 * @brief Salva o nome do operador no "disco" do navegador.
 */
function salvarPerfil() {
    const input = document.getElementById('input-operador');
    const nome = input.value.trim();

    if (nome) {
        localStorage.setItem('nexus_operador', nome);
        document.getElementById('perfil-status').innerText = `Operador Identificado: ${nome}`;
        input.value = "";
        console.log("[STORAGE] Nome do operador persistido.");
    }
}

/**
 * @brief Adiciona um log e persiste no array JSON.
 */
function adicionarLog() {
    const input = document.getElementById('input-log');
    const mensagem = input.value.trim();

    if (mensagem) {
        // 1. Pega os logs existentes (ou cria um novo array se não existir)
        const logsRaw = localStorage.getItem('nexus_logs');
        let logs = logsRaw ? JSON.parse(logsRaw) : [];

        // 2. Adiciona o novo evento com timestamp
        const novoEvento = {
            hora: new Date().toLocaleTimeString(),
            texto: mensagem
        };
        logs.push(novoEvento);

        // 3. Salva de volta convertendo para TEXTO (JSON.stringify)
        localStorage.setItem('nexus_logs', JSON.stringify(logs));

        input.value = "";
        carregarLogs(); // Atualiza a visão
    }
}

/**
 * @brief Lê o JSON do storage e renderiza no terminal.
 */
function carregarLogs() {
    const terminal = document.getElementById('log-terminal');
    const logsRaw = localStorage.getItem('nexus_logs');
    
    if (logsRaw) {
        const logs = JSON.parse(logsRaw); // Converte de volta para OBJETO
        terminal.innerHTML = ""; // Limpa visão atual

        logs.forEach(log => {
            const p = document.createElement('p');
            p.innerHTML = `<span style="color: #58a6ff">[${log.hora}]</span> > ${log.texto}`;
            terminal.appendChild(p);
        });

        // Rola automaticamente para o fim do terminal
        terminal.scrollTop = terminal.scrollHeight;
    }
}

function limparTudo() {
    if (confirm("Deseja apagar toda a memória local do Nexus?")) {
        localStorage.clear();
        location.reload(); // Recarrega para limpar a UI
    }
}

console.log("[SYSTEM] Engine de Persistência JSON Ativa.");

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
