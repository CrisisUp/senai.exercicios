/**
 * @file script.js
 * @brief Gerenciamento de Logística Tátil via Drag and Drop API.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

document.addEventListener('DOMContentLoaded', () => {
    const cargoItems = document.querySelectorAll('.cargo-item');
    const dropZone = document.getElementById('drop-zone');
    const manifestList = document.getElementById('manifest-list');
    const currentWeightEl = document.getElementById('current-weight');
    const missionStatusEl = document.getElementById('mission-status');
    const progressBar = document.getElementById('weight-progress');
    const terminalLog = document.getElementById('terminal-log');

    const MAX_WEIGHT = 300;
    let currentWeight = 0;

    /**
     * @section Eventos de Origem (Draggable Items)
     */
    cargoItems.forEach(item => {
        item.addEventListener('dragstart', (e) => {
            item.classList.add('dragging');
            
            // Preparando o envelope de dados (DataTransfer)
            const cargoData = {
                id: item.dataset.id,
                type: item.dataset.type,
                weight: parseInt(item.dataset.weight)
            };
            
            e.dataTransfer.setData('application/json', JSON.stringify(cargoData));
            e.dataTransfer.effectAllowed = 'move';
            
            log(`Iniciando transporte da carga ${cargoData.id}...`);
        });

        item.addEventListener('dragend', () => {
            item.classList.remove('dragging');
        });
    });

    /**
     * @section Eventos de Destino (Drop Zone)
     */
    dropZone.addEventListener('dragover', (e) => {
        // ESSENCIAL: Previne o comportamento padrão para permitir o drop
        e.preventDefault();
        e.dataTransfer.dropEffect = 'move';
    });

    dropZone.addEventListener('dragenter', (e) => {
        e.preventDefault();
        dropZone.classList.add('drag-over');
    });

    dropZone.addEventListener('dragleave', () => {
        dropZone.classList.remove('drag-over');
    });

    dropZone.addEventListener('drop', (e) => {
        e.preventDefault();
        dropZone.classList.remove('drag-over');

        try {
            const dataRaw = e.dataTransfer.getData('application/json');
            if (!dataRaw) return;

            const cargo = JSON.parse(dataRaw);
            
            // Validação de Lógica de Negócio (Falha Crítica: Overload)
            if (currentWeight + cargo.weight > MAX_WEIGHT) {
                log(`ERRO: Carga ${cargo.id} excede o limite de peso!`, 'error');
                showVisualFeedback('danger');
                return;
            }

            // Processamento do Drop bem-sucedido
            executeLoading(cargo);
            
            // Remove o item do inventário (simulando que foi movido)
            const originalItem = document.querySelector(`[data-id="${cargo.id}"]`);
            if (originalItem) originalItem.remove();

        } catch (err) {
            log('Falha na integridade do envelope de dados.', 'error');
        }
    });

    /**
     * @brief Executa a lógica de carregamento e atualiza a UI.
     */
    function executeLoading(cargo) {
        currentWeight += cargo.weight;
        updateUI();
        addToManifest(cargo);
        log(`Carga ${cargo.id} (${cargo.weight}kg) carregada com sucesso.`);
        showVisualFeedback('success');
    }

    function updateUI() {
        currentWeightEl.textContent = currentWeight;
        const percentage = (currentWeight / MAX_WEIGHT) * 100;
        progressBar.style.width = `${percentage}%`;

        if (percentage >= 100) {
            missionStatusEl.textContent = 'CAPACITY REACHED';
            missionStatusEl.className = 'status-danger';
            progressBar.style.backgroundColor = 'var(--accent-red)';
        } else if (percentage > 80) {
            missionStatusEl.textContent = 'WARNING: HEAVY LOAD';
            missionStatusEl.className = 'status-warn';
            progressBar.style.backgroundColor = 'var(--accent-yellow)';
        }
    }

    function addToManifest(cargo) {
        const li = document.createElement('li');
        li.className = 'manifest-item';
        li.textContent = `> ${new Date().toLocaleTimeString()} | ID:${cargo.id} | ${cargo.type} | ${cargo.weight}KG`;
        manifestList.prepend(li);
    }

    function log(msg, type = 'info') {
        terminalLog.textContent = msg;
        terminalLog.style.color = type === 'error' ? 'var(--accent-red)' : 'var(--accent-yellow)';
    }

    function showVisualFeedback(type) {
        const color = type === 'success' ? 'var(--accent-green)' : 'var(--accent-red)';
        dropZone.style.borderColor = color;
        setTimeout(() => {
            dropZone.style.borderColor = 'var(--border-dim)';
        }, 500);
    }
});

/*
===============================================================================
RESUMO TEÓRICO: DOM DRAG AND DROP API (NÍVEL 31 - ELITE)
===============================================================================

1. O MODELO DE EVENTOS:
   A API de Drag and Drop não é baseada em mouse events comuns (mousemove), mas em 
   um ciclo de vida de eventos especializados. O objeto 'dataTransfer' é a ponte 
   de comunicação entre o item arrastado (source) e o alvo (target).

2. DATATRANSFER & SEGURANÇA:
   O método 'setData()' permite encapsular dados em formatos MIME. No SkyCargo, 
   usamos 'application/json' para transportar metadados complexos (ID, Peso) de 
   forma estruturada. O browser protege esses dados; eles só ficam disponíveis 
   durante o evento 'drop'.

3. PREVENTDEFAULT() - A CHAVE DO DROP:
   Por padrão, a maioria das áreas de um documento HTML não permite o drop de dados. 
   Para habilitar uma Drop Zone, os eventos 'dragover' e 'dragenter' DEVEM chamar 
   'event.preventDefault()'. Sem isso, o evento 'drop' nunca será disparado.

4. FEEDBACK VISUAL HÁPTICO/VISUAL:
   Engenharia de Elite exige feedback imediato. O uso de pseudo-classes ou classes 
   dinâmicas (.drag-over) é vital para reduzir o custo cognitivo do operador, 
   sinalizando onde a ação terá efeito.

5. VALIDAÇÃO NO DROP:
   O drop não é apenas movimento de UI, é uma transação de dados. A validação 
   deve ocorrer antes da persistência ou mudança de estado (ex: conferir peso 
   máximo do drone).
===============================================================================
*/

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */
