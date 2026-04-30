/**
 * @file script.js
 * @brief Orquestração de Service Workers e Monitor de Rede (Atividade 29).
 * @author Engenheiro de Elite
 */

const netStatus = document.getElementById('net-status');
const storageLabel = document.getElementById('storage-status');

// 1. REGISTRO DO SERVICE WORKER
if ('serviceWorker' in navigator) {
    window.addEventListener('load', () => {
        navigator.serviceWorker.register('js/sw.js')
            .then(reg => {
                console.log("%c[SUCCESS] Service Worker Registrado.", "color: #2ea043; font-weight: bold;");
                storageLabel.innerText = "VALIDATED (LOCAL CACHE)";
                storageLabel.style.color = "#2ea043";
            })
            .catch(err => {
                console.error("[ERROR] Falha ao registrar Worker: ", err);
                storageLabel.innerText = "FAILED";
            });
    });
}

// 2. MONITORAMENTO DE CONECTIVIDADE
function atualizarInterfaceRede() {
    const isOnline = navigator.onLine;
    
    if (isOnline) {
        document.body.classList.remove('offline');
        netStatus.innerText = "ONLINE";
        console.log("%c[NETWORK] Link de Satélite Restabelecido.", "color: #2ea043;");
    } else {
        document.body.classList.add('offline');
        netStatus.innerText = "OFFLINE (MODO RESILIENTE)";
        console.warn("[NETWORK] Perda de sinal. Ativando Cache Local.");
    }
}

// Escuta mudanças de rede em tempo real
window.addEventListener('online', atualizarInterfaceRede);
window.addEventListener('offline', atualizarInterfaceRede);

// Inicializa status
atualizarInterfaceRede();

console.log("[SYSTEM] Protocolo de Resiliência Ativo.");
