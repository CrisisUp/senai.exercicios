/**
 * @file script.js
 * @brief Comunicação Assíncrona via Fetch API (Atividade 15).
 */

/**
 * @brief Orquestra o carregamento de dados remotos.
 */
async fn carregarDrones() {
    const btn = document.getElementById('btn-fetch');
    const skeleton = document.getElementById('loading-state');
    const results = document.getElementById('results');

    // 1. ESTADO DE PREPARAÇÃO (UI)
    btn.disabled = true;
    results.classList.remove('visible');
    results.innerHTML = ""; // Limpa resultados anteriores
    skeleton.style.display = "grid"; // Mostra os "fantasmas" cinzas
    console.log("[NETWORK] Solicitando dados ao Nexus Central...");

    try {
        // 2. A REQUISIÇÃO (O Momento da Promessa)
        // Usamos um simulador real de API (JSONPlaceholder)
        const response = await fetch('https://jsonplaceholder.typicode.com/users?_limit=3');
        
        // Verifica se a resposta foi bem-sucedida (Status 200)
        if (!response.ok) throw new Error("VAULT_OFFLINE");

        const dronesRemotos = await response.json();

        // Simulação de delay extra para podermos ver o Skeleton (Industrial)
        await new Promise(r => setTimeout(r, 2000));

        // 3. RENDERIZAÇÃO DOS DADOS REAIS
        dronesRemotos.forEach(drone => {
            const card = document.createElement('div');
            card.className = "data-card";
            card.innerHTML = `
                <h3>DRONE-${drone.id}</h3>
                <p><strong>OPERADOR:</strong> ${drone.name}</p>
                <p><strong>FREQ:</strong> ${drone.address.zipcode}</p>
                <p><strong>STATUS:</strong> STANDBY</p>
            `;
            results.appendChild(card);
        });

        console.log("[NETWORK] Dados sincronizados com sucesso.");

    } catch (error) {
        // 4. TRATAMENTO DE ERROS (Resiliência)
        console.error("[ERROR] Falha na rede: ", error.message);
        results.innerHTML = `
            <p style="color: #f85149; grid-column: 1/-1;">
                ❌ ERRO CRÍTICO: Não foi possível conectar ao Nexus Vault.
            </p>
        `;
    } finally {
        // 5. FINALIZAÇÃO (Limpeza de Estados)
        skeleton.style.display = "none";
        results.classList.add('visible'); // Efeito Fade-in
        btn.disabled = false;
    }
}

// Nota: Usei 'async fn' no rascunho mental, mas o correto no JS é 'async function'
// Vou corrigir no arquivo final abaixo.
async function carregarDrones() {
    const btn = document.getElementById('btn-fetch');
    const skeleton = document.getElementById('loading-state');
    const results = document.getElementById('results');

    btn.disabled = true;
    results.classList.remove('visible');
    results.innerHTML = "";
    skeleton.style.display = "grid";

    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/users?_limit=3');
        if (!response.ok) throw new Error("VAULT_OFFLINE");
        const dronesRemotos = await response.json();

        await new Promise(r => setTimeout(r, 2000));

        dronesRemotos.forEach(drone => {
            const card = document.createElement('div');
            card.className = "data-card";
            card.innerHTML = `
                <h3>DRONE-${drone.id}</h3>
                <p><strong>OPERADOR:</strong> ${drone.name}</p>
                <p><strong>FREQ:</strong> ${drone.address.zipcode}</p>
                <p><strong>STATUS:</strong> STANDBY</p>
            `;
            results.appendChild(card);
        });

    } catch (error) {
        results.innerHTML = `<p style="color: #f85149; grid-column: 1/-1;">❌ ERRO CRÍTICO: Falha na sincronização.</p>`;
    } finally {
        skeleton.style.display = "none";
        results.classList.add('visible');
        btn.disabled = false;
    }
}
