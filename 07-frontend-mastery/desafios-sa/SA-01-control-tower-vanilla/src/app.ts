/**
 * @file app.ts
 * @brief Orquestrador Master do SkyCargo Control Tower (Vanilla Edition).
 * @author Engenheiro de Elite
 */

// 1. CONTRATOS DE DADOS
interface IDrone {
    id: string;
    status: 'OPERACIONAL' | 'EM ROTA' | 'ALERTA';
    lat: number;
    lon: number;
}

// 2. UTILITÁRIOS DE PERFORMANCE (Ativ 07)
function throttle<T extends (...args: any[]) => any>(func: T, delay: number) {
    let lastCall = 0;
    return (...args: Parameters<T>) => {
        const now = Date.now();
        if (now - lastCall < delay) return;
        lastCall = now;
        return func(...args);
    };
}

// 3. SELEÇÃO SEGURA DE DOM (Ativ 06)
const btnSync = document.getElementById('btn-sync') as HTMLButtonElement | null;
const btnTheme = document.getElementById('btn-theme') as HTMLButtonElement | null;
const droneListContainer = document.getElementById('drone-list');
const logsStream = document.getElementById('logs-stream');
const coordsDisplay = document.getElementById('coords-display');
const clockDisplay = document.getElementById('clock');
const syncStatus = document.getElementById('sync-status');

// 4. LÓGICA DE AUDITORIA (Logs)
function pushLog(msg: string, level: 'INFO' | 'WARN' | 'SEC' = 'INFO'): void {
    if (!logsStream) return;
    
    const p = document.createElement('p');
    p.style.marginBottom = "5px";
    const colors = { INFO: 'var(--text-secondary)', WARN: 'var(--status-alert)', SEC: 'var(--status-warning)' };
    p.innerHTML = `<span style="color: ${colors[level]}">> [${new Date().toLocaleTimeString()}] ${msg}</span>`;
    
    logsStream.prepend(p);
}

// 5. COMUNICAÇÃO COM NEXUS (Ativ 08)
async function fetchNexusData(): Promise<IDrone[]> {
    pushLog("Handshake com Nexus Vault...", "SEC");
    
    // Simulação de latência de rede
    await new Promise(r => setTimeout(resolve => r(true), 1500));

    if (Math.random() < 0.05) throw new Error("VAULT_TIMEOUT");

    return [
        { id: "ALPHA-707", status: "OPERACIONAL", lat: -23.550, lon: -46.633 },
        { id: "BETA-404", status: "ALERTA", lat: -23.560, lon: -46.640 },
        { id: "GAMMA-909", status: "EM ROTA", lat: -23.545, lon: -46.620 }
    ];
}

// 6. RENDERIZAÇÃO DINÂMICA
function renderDrones(drones: IDrone[]): void {
    if (!droneListContainer) return;
    
    // Uso de DocumentFragment para performance (Evita múltiplos repaints)
    const fragment = document.createDocumentFragment();
    droneListContainer.innerHTML = ""; // Limpa atual

    drones.forEach(drone => {
        const div = document.createElement('div');
        div.className = "drone-item";
        const statusClass = drone.status === 'OPERACIONAL' ? 'status-online' : (drone.status === 'ALERTA' ? 'status-alert' : 'status-offline');
        
        div.innerHTML = `
            <div>
                <strong>${drone.id}</strong><br>
                <small style="color: var(--text-secondary)">Pos: ${drone.lat.toFixed(3)}, ${drone.lon.toFixed(3)}</small>
            </div>
            <span class="status-badge ${statusClass}">${drone.status}</span>
        `;

        div.addEventListener('mouseenter', () => {
            if (coordsDisplay) coordsDisplay.innerText = `LOCKED: LAT ${drone.lat} | LON ${drone.lon}`;
        });

        fragment.appendChild(div);
    });

    droneListContainer.appendChild(fragment);
}

// 7. ORQUESTRADOR DE SINCRONIA (Throttled)
const handleSync = throttle(async () => {
    if (!btnSync || !syncStatus) return;

    btnSync.disabled = true;
    syncStatus.innerText = "LINK: SYNCING";
    syncStatus.className = "status-badge status-offline";

    try {
        const data = await fetchNexusData();
        renderDrones(data);
        pushLog("Sincronia concluída: 3 drones localizados.", "INFO");
        syncStatus.innerText = "LINK: OK";
        syncStatus.className = "status-badge status-online";
    } catch (e) {
        pushLog("FALHA DE CONEXÃO COM NEXUS VAULT!", "WARN");
        syncStatus.innerText = "LINK: ERROR";
        syncStatus.className = "status-badge status-alert";
    } finally {
        btnSync.disabled = false;
    }
}, 5000); // Impede cliques frenéticos (Cooldown de 5s)

// 8. INICIALIZAÇÃO E EVENTOS
if (btnSync) btnSync.addEventListener('click', handleSync);

if (btnTheme) {
    btnTheme.addEventListener('click', () => {
        document.body.classList.toggle('light-mode');
        pushLog("Operador alterou o tema visual.", "INFO");
    });
}

// Relógio do Sistema em Tempo Real
setInterval(() => {
    if (clockDisplay) clockDisplay.innerText = new Date().toLocaleTimeString();
}, 1000);

// Primeira Carga
handleSync();

console.log("\x1b[1;36m[SYSTEM]\x1b[0m SkyCargo Control Tower v2.0 Initialized.");
