/**
 * @file script.js
 * @brief Orquestração de WebSockets e Comunicação Bidirecional (Atividade 30).
 * @author Engenheiro de Elite
 */

const feed = document.getElementById('telemetry-feed');
const badge = document.getElementById('link-status');
const input = document.getElementById('cmd-input');

let socket = null;

/**
 * @brief Inicializa a conexão persistente com o Nexus Server.
 */
function conectarNexus() {
    console.log("[WS] Iniciando handshake com o servidor de telemetria...");
    
    // 1. ABERTURA DO CANAL (Usando servidor de eco para teste)
    socket = new WebSocket('wss://echo.websocket.org');

    // 2. EVENTO: ON OPEN (Conexão Estabelecida)
    socket.onopen = () => {
        badge.innerText = "LINK OPEN";
        badge.className = "status-badge open";
        registrarNoFeed("CONEXÃO ESTABELECIDA COM NEXUS GLOBAL.");
        console.log("%c[SUCCESS] Canal Bi-direcional Ativo.", "color: #2ea043; font-weight: bold;");
        
        // Simula o primeiro envio automático (Identificação)
        socket.send(JSON.stringify({ type: "AUTH", client: "DUBAI-CENTRAL" }));
    };

    // 3. EVENTO: ON MESSAGE (Dado Recebido)
    socket.onmessage = (event) => {
        // No gRPC/WS de elite, o dado chega bruto e nós o tratamos
        registrarNoFeed(`RECEBIDO: ${event.data}`);
    };

    // 4. EVENTO: ON ERROR
    socket.onerror = (error) => {
        console.error("[WS ERROR] Falha no link: ", error);
        badge.innerText = "LINK ERROR";
        badge.className = "status-badge closed";
    };

    // 5. EVENTO: ON CLOSE
    socket.onclose = () => {
        badge.innerText = "LINK CLOSED";
        badge.className = "status-badge closed";
        registrarNoFeed("CONEXÃO ENCERRADA PELO SERVIDOR.");
        
        // Auto-reconnect após 5 segundos (Padrão Industrial)
        setTimeout(conectarNexus, 5000);
    };
}

/**
 * @brief Envia comandos táticos através do túnel aberto.
 */
function enviarComando() {
    const comando = input.value.trim().toUpperCase();
    
    if (socket && socket.readyState === WebSocket.OPEN && comando !== "") {
        const pacote = `CMD_REQUEST: [${comando}]`;
        
        // ENVIO BINÁRIO/TEXTUAL
        socket.send(pacote);
        
        registrarNoFeed(`ENVIADO: ${pacote}`);
        input.value = "";
    } else {
        alert("ERRO: Link de satélite offline ou comando vazio.");
    }
}

/**
 * @brief Auxiliar para log visual no feed do operador.
 */
function registrarNoFeed(msg) {
    const p = document.createElement('p');
    p.innerText = `> [${new Date().toLocaleTimeString()}] ${msg}`;
    feed.appendChild(p);
    
    // Auto-scroll para manter a telemetria visível
    feed.scrollTop = feed.scrollHeight;
}

// Inicialização do Boot de Rede
conectarNexus();

/*
 * @section ResumoTeorico
 * 1. PERSISTÊNCIA: Diferente do HTTP, o WebSocket mantém o handshake TCP aberto.
 * 2. FULL-DUPLEX: Servidor e Cliente falam ao mesmo tempo, sem esperar o outro.
 * 3. READY_STATE: Vital monitorar se o socket está OPEN antes de tentar o .send().
 */
