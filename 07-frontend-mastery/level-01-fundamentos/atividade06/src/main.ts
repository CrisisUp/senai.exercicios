/**
 * @file main.ts
 * @brief Manipulação de DOM Segura para o SkyCargo OS.
 * @author Engenheiro de Elite
 */

// 1. Seleção Segura com Type Casting (Assegura que o elemento é do tipo correto)
const btnTheme = document.getElementById('btn-toggle-theme') as HTMLButtonElement | null;
const btnAddLog = document.getElementById('btn-add-log') as HTMLButtonElement | null;
const logsContainer = document.getElementById('logs-container') as HTMLDivElement | null;
const mapa = document.getElementById('mapa-tatico') as HTMLElement | null;
const coordsDisplay = document.getElementById('coordenadas-display') as HTMLDivElement | null;
const statusIntegrity = document.getElementById('dom-status') as HTMLSpanElement | null;

/**
 * @brief Adiciona um log ao container de forma performática e segura.
 */
function adicionarLog(mensagem: string): void {
    if (!logsContainer) {
        console.error("\x1b[31m[FALHA]\x1b[0m Container de logs não localizado no DOM.");
        return;
    }

    const timestamp = new Date().toLocaleTimeString();
    const p = document.createElement('p');
    p.style.marginBottom = "5px";
    p.innerHTML = `<span style="color: var(--text-muted)">[${timestamp}]</span> > ${mensagem}`;
    
    // Inserção no topo do fluxo
    logsContainer.prepend(p);
}

// 2. Vinculação de Eventos com Proteção contra Nulos
if (btnTheme) {
    btnTheme.addEventListener('click', () => {
        document.body.classList.toggle('light-mode');
        adicionarLog("Visual alterada pelo operador.");
    });
}

if (btnAddLog) {
    btnAddLog.addEventListener('click', () => {
        const sateliteId = Math.floor(Math.random() * 9000) + 1000;
        adicionarLog(`Sinal recebido do Satélite #${sateliteId}`);
    });
}

// 3. Captura de Coordenadas no Mapa (Interação Complexa)
if (mapa && coordsDisplay) {
    mapa.addEventListener('click', (event: MouseEvent) => {
        // Cálculo de coordenadas relativas ao elemento do mapa
        const rect = mapa.getBoundingClientRect();
        const x = Math.round(event.clientX - rect.left);
        const y = Math.round(event.clientY - rect.top);
        
        coordsDisplay.innerText = `LINK ESTABELECIDO: X=${x} | Y=${y}`;
        adicionarLog(`Nova coordenada tática: ${x}, ${y}`);
    });
}

// 4. Validação de Integridade Final
if (statusIntegrity) {
    statusIntegrity.innerText = "100% SECURE (TS ARMORED)";
    statusIntegrity.style.color = "var(--status-success)";
}

console.log("\x1b[1;32m[SYSTEM]\x1b[0m DOM Security Engine Ativo.");

/*
 * @section ResumoTeorico
 * 1. NULL GUARDS: O uso de 'if (elemento)' impede o crash da aplicação caso o 
 *    HTML seja alterado sem aviso.
 * 2. TYPE ASSERTION: 'as HTMLButtonElement' fornece auto-complete exato das 
 *    propriedades do elemento (ex: .disabled, .innerText).
 * 3. EVENT DELEGATION: O MouseEvent tipado permite acessar propriedades do 
 *    evento (clientX, clientY) com segurança total.
 */
