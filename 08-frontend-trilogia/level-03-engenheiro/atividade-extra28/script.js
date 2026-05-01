/**
 * @date 2026
 */
/**
 * @file script.js
 * @brief Orquestração de Alertas Nativos e Vibração (Atividade 28).
 * @author Engenheiro de Elite
 */

/**
 * @brief Solicita permissão ao operador para notificações do Sistema Operacional.
 */
function solicitarPermissao() {
    console.log("[SYSTEM] Solicitando autorização de segurança...");
    
    // 1. Verificação de Suporte
    if (!("Notification" in window)) {
        alert("ERRO: Este navegador não suporta notificações de desktop.");
        return;
    }

    // 2. Requisição de Permissão
    Notification.requestPermission().then(permission => {
        const span = document.getElementById('perm-status');
        span.innerText = permission.toUpperCase();

        if (permission === "granted") {
            span.style.color = "#2ea043";
            console.log("%c[SUCCESS] Permissão concedida pelo operador.", "color: #2ea043; font-weight: bold;");
            document.getElementById('btn-request').style.display = "none";
        } else {
            span.style.color = "#f85149";
            console.warn("[WARNING] Permissão negada. Alertas limitados à aba ativa.");
        }
    });
}

/**
 * @brief Dispara alertas sensoriais conforme a gravidade.
 */
function dispararAlerta(nivel) {
    const log = document.getElementById('alert-log');
    
    switch(nivel) {
        case 'INFO':
            log.innerText = "EVENTO DE ROTINA: Checkout realizado.";
            console.log("[INFO] Sinal de rotina recebido.");
            break;

        case 'WARNING':
            log.innerText = "AVISO: Turbulência detectada no Setor 4.";
            // VIBRAÇÃO API: 200ms de pulso tátil
            if (navigator.vibrate) navigator.vibrate(200);
            console.log("[WARN] Alerta tátil enviado.");
            break;

        case 'CRITICAL':
            log.innerText = "EMERGÊNCIA: Rota de Colisão IMINENTE!";
            
            // 1. Feedback Visual (Shake)
            const card = document.getElementById('critical-card');
            card.classList.add('shake');
            setTimeout(() => card.classList.remove('shake'), 1000);

            // 2. Feedback Tátil (Padrão SOS: 100ms vibra, 100ms pausa, 300ms vibra...)
            if (navigator.vibrate) navigator.vibrate([100, 100, 100, 100, 300]);

            // 3. Notificação OS (Desktop)
            if (Notification.permission === "granted") {
                new Notification("🚨 NEXUS CRITICAL ALERT", {
                    body: "Alerta de Colisão no Drone ALPHA-707. Ação imediata exigida!",
                    icon: "https://placehold.co/100x100/f85149/ffffff?text=X", // Ícone de alerta
                    tag: "collision-alert" // Evita notificações duplicadas
                });
            } else {
                alert("🚨 ALERTA CRÍTICO: ROTA DE COLISÃO!");
            }
            console.error("[CRITICAL] Resposta de emergência ativada.");
            break;
    }
}

// Verifica status no carregamento
if (Notification.permission === "granted") {
    document.getElementById('perm-status').innerText = "GRANTED";
    document.getElementById('perm-status').style.color = "#2ea043";
    document.getElementById('btn-request').style.display = "none";
}

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
