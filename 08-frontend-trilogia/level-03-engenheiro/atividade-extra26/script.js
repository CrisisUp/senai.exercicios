/**
 * @date 2026
 */
/**
 * @file script.js
 * @brief Lógica Industrial de Drag and Drop (Atividade 26).
 * @author Engenheiro de Elite
 */

const packages = document.querySelectorAll('.package');
const dropZones = document.querySelectorAll('.drop-zone');
const logDisplay = document.getElementById('dispatch-log');

// 1. CONFIGURAÇÃO DAS CARGAS (Draggables)
packages.forEach(pkg => {
    pkg.addEventListener('dragstart', (e) => {
        // Adiciona classe visual
        pkg.classList.add('dragging');
        
        // DATA TRANSFER: Guarda o ID para o momento do DROP
        e.dataTransfer.setData('text/plain', pkg.id);
        
        console.log(`[DRAG] Iniciado arraste da carga: ${pkg.id}`);
    });

    pkg.addEventListener('dragend', () => {
        pkg.classList.remove('dragging');
    });
});

// 2. CONFIGURAÇÃO DOS HANGARES (Drop Targets)
dropZones.forEach(zone => {
    // VITAL: Prevenir o default para permitir o drop
    zone.addEventListener('dragover', (e) => {
        e.preventDefault(); 
        zone.classList.add('drop-zone-active');
    });

    zone.addEventListener('dragleave', () => {
        zone.classList.remove('drop-zone-active');
    });

    zone.addEventListener('drop', (e) => {
        e.preventDefault();
        zone.classList.remove('drop-zone-active');

        // RECUPERAÇÃO DO DADO: Qual item foi solto?
        const pkgId = e.dataTransfer.getData('text/plain');
        const pkgElement = document.getElementById(pkgId);
        const hangarNome = zone.dataset.hangar;

        if (pkgElement) {
            // MOVE O ELEMENTO NO DOM (Mágica da Logística)
            zone.appendChild(pkgElement);
            
            // FEEDBACK INDUSTRIAL
            const msg = `SUCESSO: ${pkgId} DESPACHADO PARA HANGAR ${hangarNome}`;
            logDisplay.innerText = msg;
            console.log(`%c[DROP] ${msg}`, "color: #2ea043; font-weight: bold;");
        }
    });
});

console.log("[SYSTEM] Fluxo de Drag & Drop Industrial Ativo.");

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
