/**
 * @file script.js
 * @brief Eventos de Teclado e Controle de Modais (Atividade 09).
 */

const modal = document.getElementById('emergency-modal');

/**
 * @brief Abre o alerta de emergência usando a API nativa.
 */
function abrirAlerta() {
    console.log("[SYSTEM] Disparando alerta de segurança...");
    // .showModal() abre o dialog no topo e bloqueia o fundo (backdrop)
    modal.showModal();
}

function fecharAlerta() {
    modal.close();
    console.log("[SYSTEM] Alerta limpo pelo operador.");
}

// 3. EVENT LISTENERS DE TECLADO (Global)
// 'keydown' detecta o momento em que a tecla é pressionada
document.addEventListener('keydown', (event) => {
    // O objeto 'event' contém todos os detalhes da ação
    const tecla = event.key.toUpperCase();
    
    console.log(`[KEY] Tecla detectada: ${tecla}`);

    // Lógica de Atalhos
    if (tecla === 'A') {
        abrirAlerta();
    }

    if (tecla === 'ESCAPE' || tecla === 'ESC') {
        // O navegador já fecha o dialog com ESC por padrão, 
        // mas aqui podemos disparar lógicas extras.
        console.log("[SECURITY] Procedimento de saída via teclado.");
    }
    
    // Atalho Secreto: Log do Estado
    if (tecla === 'L') {
        console.table({
            sistema: "Nexus OS",
            status: "Online",
            modal_aberto: modal.open
        });
    }
});

console.log("[SYSTEM] Engine de Teclado e Camadas Ativa.");
console.log("[HINT] Pressione 'A' para testar o alerta ou 'L' para logs.");
