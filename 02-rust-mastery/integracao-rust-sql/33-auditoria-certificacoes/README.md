# 🦀🗄️ Atividade Integradora 33: Auditoria Forense em Habilitações

## 🎯 Estudo de Caso
O sistema de certificação (Ativ. 32) agora é uma peça crítica de auditoria na "SkyCargo". Precisamos saber exatamente quando um piloto foi habilitado para um drone. Como o processo de habilitação envolve questões legais, o log não pode depender do programador. O próprio banco de dados deve registrar a data e hora de cada novo vínculo.

## 🛠️ Necessidade Técnica
Expandir a arquitetura N:N com automação forense:
*   **Shadow Table de Auditoria:** Uma tabela `historico_certificacoes` que armazena a história de cada vínculo.
*   **Trigger de Inserção:** Um gatilho que captura o `piloto_id` e o `drone_id` e registra o momento exato do vínculo.
*   **Rust Analytics:** Consulta complexa que une as tabelas de auditoria para mostrar a evolução temporal da equipe.

## 📋 Requisitos
1. Utilizar o banco da Atividade 32 (`certificacoes.db`).
2. Criar a tabela `historico_certificacoes` (id, piloto_nome, drone_modelo, data).
3. Implementar um **TRIGGER** que, ao inserir na tabela de ligação `habilitacoes`, busque os nomes nas tabelas de Pilotos e Drones e grave no Histórico.
4. Desenvolver o menu interativo:
    - Vincular Habilitação (e ver o log automático).
    - Consultar Timeline de Certificações.
