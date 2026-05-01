/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file script.js
 * @brief Definição de Web Components e Shadow DOM (Atividade 20).
 */

class NexusDroneCard extends HTMLElement {
    constructor() {
        super();
        // 1. SHADOW DOM: Cria o isolamento total
        this.attachShadow({ mode: 'open' });
    }

    // 2. LIFECYCLE: Executa quando o componente entra na tela
    connectedCallback() {
        this.render();
    }

    // 3. REACTIVITY: Reage a mudanças nos atributos do HTML
    static get observedAttributes() {
        return ['name', 'status'];
    }

    attributeChangedCallback() {
        this.render();
    }

    render() {
        const name = this.getAttribute('name') || "UNKNOWN";
        const status = this.getAttribute('status') || "OFFLINE";
        const color = status === 'ALERTA' ? '#f85149' : '#00f2ff';

        // 4. ESTRUTURA E ESTILO ENCAPSULADOS (Ninguém de fora mexe aqui)
        this.shadowRoot.innerHTML = `
            <style>
                :host { display: block; }
                .card {
                    background: #161b22;
                    border: 1px solid #30363d;
                    padding: 20px;
                    border-radius: 8px;
                    width: 220px;
                    font-family: 'Segoe UI', sans-serif;
                    box-shadow: 0 4px 12px rgba(0,0,0,0.5);
                    transition: border-color 0.3s;
                }
                .card:hover { border-color: ${color}; }
                h3 { 
                    color: ${color}; 
                    margin: 0; 
                    font-size: 1rem; 
                    letter-spacing: 1px;
                }
                .status { 
                    font-size: 0.7rem; 
                    color: #7d8590; 
                    margin-top: 5px; 
                    text-transform: uppercase;
                }
                .slot-area { 
                    margin-top: 15px; 
                    font-size: 0.8rem; 
                    color: #00f2ff;
                    font-style: italic;
                    border-top: 1px solid #333;
                    padding-top: 10px;
                }
            </style>
            
            <div class="card">
                <h3>${name}</h3>
                <div class="status">SITUAÇÃO: ${status}</div>
                
                <!-- SLOT: Onde o HTML externo é injetado -->
                <div class="slot-area">
                    <slot name="extra">MODO: PADRÃO</slot>
                </div>
            </div>
        `;
    }
}

// 5. REGISTRO DA TAG: nexus-drone-card agora existe para o navegador!
customElements.define('nexus-drone-card', NexusDroneCard);

console.log("%c[ARCHITECTURE] Web Components Framework Inicializado.", "color: #00f2ff; font-weight: bold;");

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
