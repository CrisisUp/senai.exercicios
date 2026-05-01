/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Processamento de Arrays e Manipulação Dinâmica de Tabelas (Atividade 06).
 */

// 1. Array de Objetos (A base de dados da frota)
const frotaDrones = [
    { id: "ALPHA-707", modelo: "Interceptor", bateria: 85, status: "OPERACIONAL" },
    { id: "BETA-404", modelo: "Cargo Lifter", bateria: 12, status: "ALERTA" },
    { id: "GAMMA-909", modelo: "Stealth Scout", bateria: 99, status: "OPERACIONAL" },
    { id: "SIGMA-001", modelo: "Vulture v2", bateria: 45, status: "MANUTENÇÃO" }
];

/**
 * @brief Popula a tabela com os dados do Array.
 */
function popularTabela() {
    const tbody = document.getElementById('fleet-body');
    
    // Limpa a tabela antes de popular (evita duplicação)
    tbody.innerHTML = "";

    // LOOP INDUSTRIAL (.forEach)
    frotaDrones.forEach(drone => {
        // Criamos uma nova linha
        const tr = document.createElement('tr');

        // Definimos a cor do status baseado na lógica (Condicional Ativ 05)
        let corStatus = "#3fb950"; // Verde default
        if (drone.status === "ALERTA") corStatus = "#f85149";
        if (drone.status === "MANUTENÇÃO") corStatus = "#d29922";

        // Preenchemos o conteúdo da linha
        tr.innerHTML = `
            <td style="font-weight: bold; color: #58a6ff;">${drone.id}</td>
            <td>${drone.modelo}</td>
            <td>${drone.bateria}%</td>
            <td style="color: ${corStatus}">${drone.status}</td>
        `;

        // Anexamos a linha ao corpo da tabela
        tbody.appendChild(tr);
    });

    console.log(`[SYSTEM] Monitor sincronizado com ${frotaDrones.length} unidades.`);
}

function limparTabela() {
    document.getElementById('fleet-body').innerHTML = "";
    console.log("[SYSTEM] Monitor de frota limpo.");
}

// Inicialização opcional: popular ao carregar
popularTabela();

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
