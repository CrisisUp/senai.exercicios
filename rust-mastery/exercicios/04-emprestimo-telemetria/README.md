# 🦀 Atividade 04: Telemetria de Voo (Borrowing e Referências)

## 🎯 Estudo de Caso
O sistema da "SkyCargo" precisa agora processar dados de telemetria (altitude, velocidade, bateria) em tempo real. No entanto, diferentes módulos (Painel do Piloto, Sistema de Segurança e Registro de Log) precisam ler esses dados ao mesmo tempo. Na Atividade 03, vimos que passar a posse (Ownership) destrói a variável original. Aqui, precisamos ler os dados sem "matar" o objeto original.

## 🛠️ Necessidade Técnica
O **Borrowing (Empréstimo)** permite acessar dados sem tomar a posse:
*   **Referências Imutáveis (`&T`):** Permitem ler o dado. Você pode ter infinitas referências de leitura ao mesmo tempo.
*   **Referências Mutáveis (`&mut T`):** Permitem alterar o dado. Você só pode ter UMA referência de escrita por vez (para evitar conflitos/race conditions).
*   **Regra de Ouro:** Ou você tem muitas leituras, ou uma única escrita. Nunca as duas ao mesmo tempo.

## 📋 Requisitos
1. Criar uma struct `Telemetria` com altitude, velocidade e bateria.
2. Implementar uma função `exibir_painel(t: &Telemetria)` que apenas lê os dados.
3. Implementar uma função `calibrar_altitude(t: &mut Telemetria, nova_alt: f64)` que altera o dado original.
4. Demonstrar no `main` como os dados persistem após serem "emprestados" para as funções.
