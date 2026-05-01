/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Lógica de Filtros e Busca Inteligente (Atividade 07).
 */

const frotaCompleta = [
    { id: "ALPHA-707", bateria: 92, status: "OPERACIONAL" },
    { id: "BETA-404", bateria: 5, status: "ALERTA" },
    { id: "GAMMA-909", bateria: 45, status: "MANUTENÇÃO" },
    { id: "SIGMA-001", bateria: 78, status: "EM ROTA" },
    { id: "OMEGA-999", bateria: 12, status: "ALERTA" }
];

/**
 * @brief Renderiza a tabela baseada em um array fornecido.
 */
function renderizarTabela(dados) {
    const tableBody = document.getElementById('fleet-table');
    tableBody.innerHTML = "";

    dados.forEach(drone => {
        const tr = document.createElement('tr');
        
        // Normaliza a classe para o CSS (remove acentos/espaços se necessário)
        const statusClass = "status-" + drone.status.replace(" ", "-").replace("Ç", "C");

        tr.innerHTML = `
            <td>${drone.id}</td>
            <td>${drone.bateria}%</td>
            <td class="${statusClass}">${drone.status}</td>
        `;
        tableBody.appendChild(tr);
    });
}

/**
 * @brief Aplica o filtro de status capturado do select.
 */
function aplicarFiltro() {
    const filtro = document.getElementById('status-filter').value;
    
    console.log(`[FILTER] Solicitando visão: ${filtro}`);

    // INTELIGÊNCIA DE DADOS: O Método .filter()
    let frotaFiltrada;
    if (filtro === "TODOS") {
        frotaFiltrada = frotaCompleta;
    } else {
        frotaFiltrada = frotaCompleta.filter(drone => drone.status === filtro);
    }

    renderizarTabela(frotaFiltrada);
    console.log(`[SYSTEM] Exibindo ${frotaFiltrada.length} de ${frotaCompleta.length} unidades.`);
}

// Inicialização: Exibe todos ao carregar
renderizarTabela(frotaCompleta);

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
