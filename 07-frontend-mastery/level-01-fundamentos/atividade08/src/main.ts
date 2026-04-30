/**
 * @file main.ts
 * @brief Orquestração Assíncrona e Fetch API para o SkyCargo OS.
 * @author Engenheiro de Elite
 */

// 1. Contratos de Dados (Interfaces)
interface IDrone {
    id: string;
    modelo: string;
    bateria: number;
}

// 2. Serviço de Comunicação com o Nexus (Simulação de API)
class NexusService {
    /**
     * @brief Busca drones ativos do Vault.
     * Simula uma chamada de rede com latência configurável.
     */
    static async fetchDrones(): Promise<IDrone[]> {
        // Simulação de delay de rede (2 segundos)
        await new Promise(resolve => setTimeout(resolve, 2000));

        // Simulação de resposta bem-sucedida ou erro aleatório (90% sucesso)
        if (Math.random() < 0.1) {
            throw new Error("ERR_CONNECTION_REFUSED: Nexus Vault offline.");
        }

        return [
            { id: "ALPHA-707", modelo: "Interceptor v3", bateria: 85 },
            { id: "BETA-404", modelo: "Cargo Lifter", bateria: 12 },
            { id: "GAMMA-909", modelo: "Stealth Scout", bateria: 99 }
        ];
    }
}

// 3. Gerenciamento de UI
const btnSync = document.getElementById('btn-sync') as HTMLButtonElement | null;
const loader = document.getElementById('loader');
const display = document.getElementById('data-display');
const netLogs = document.getElementById('network-logs');
const layerStatus = document.getElementById('layer-status');

/**
 * @brief Adiciona log de rede na interface.
 */
function logNet(msg: string, isError: boolean = false): void {
    if (netLogs) {
        const p = document.createElement('p');
        p.style.color = isError ? "var(--status-alert)" : "var(--text-secondary)";
        p.innerText = `[${new Date().toLocaleTimeString()}] > ${msg}`;
        netLogs.prepend(p);
    }
}

/**
 * @brief Orquestrador Principal do Sincronismo (O Coração Assíncrono).
 */
async function realizarSincronia(): Promise<void> {
    if (!btnSync || !loader || !display || !layerStatus) return;

    // A. Preparação (Estado de Carregamento)
    btnSync.disabled = true;
    loader.style.display = "block";
    layerStatus.innerText = "SYNCING...";
    layerStatus.style.color = "var(--status-warning)";
    display.innerHTML = "<p>Estabelecendo túnel seguro com o Nexus Vault...</p>";
    logNet("Iniciando Handshake TLS 1.3...");

    try {
        // B. Execução da Requisição (Aguardando Promessa)
        const drones = await NexusService.fetchDrones();

        // C. Sucesso: Renderização Dinâmica
        logNet("Pacote recebido. Descriptografando JSON...");
        display.innerHTML = "<h2>Drones Localizados no Vault:</h2>";
        
        const list = document.createElement('ul');
        list.style.listStyle = "none";
        list.style.marginTop = "20px";

        drones.forEach(d => {
            const li = document.createElement('li');
            li.style.padding = "10px";
            li.style.borderBottom = "1px solid var(--border-color)";
            li.innerHTML = `<strong>${d.id}</strong> - ${d.modelo} (${d.bateria}%)`;
            list.appendChild(li);
        });

        display.appendChild(list);
        layerStatus.innerText = "CONNECTED";
        layerStatus.style.color = "var(--status-success)";
        logNet("Sincronia concluída com sucesso.");

    } catch (error) {
        // D. Tratamento de Erro (Resiliência)
        const errMsg = error instanceof Error ? error.message : "Erro desconhecido.";
        display.innerHTML = `<p class="error-msg">FALHA NA SINCRONIA: ${errMsg}</p>`;
        layerStatus.innerText = "CONNECTION FAILED";
        layerStatus.style.color = "var(--status-alert)";
        logNet(`ERRO CRÍTICO: ${errMsg}`, true);

    } finally {
        // E. Limpeza (Finalização)
        btnSync.disabled = false;
        loader.style.display = "none";
    }
}

// 4. Binding
if (btnSync) {
    btnSync.addEventListener('click', realizarSincronia);
}

console.log("\x1b[1;32m[SYSTEM]\x1b[0m Nexus Link Engine Ativo.");

/*
 * @section ResumoTeorico
 * 1. ASYNC/AWAIT: Permite pausar a execução da função sem pausar a thread principal.
 * 2. PROMISE.ALL (Nota): Se tivéssemos 10 vaults, usaríamos Promise.all para 
 *    buscá-los simultaneamente, ganhando performance massiva.
 * 3. TRY/CATCH/FINALLY: A estrutura de elite para garantir que a UI sempre 
 *    volte para um estado estável (ex: esconder o loader), mesmo se houver erro.
 */
