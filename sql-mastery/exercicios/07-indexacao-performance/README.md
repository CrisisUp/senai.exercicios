# 🗄️ Atividade 07: Engenharia de Performance (Indexação e Planos de Busca)

## 🎯 Estudo de Caso

A "SkyCargo" agora gera milhares de registros de telemetria por hora. O banco de dados de logs (`historico_voo`) cresceu tanto que uma consulta simples para encontrar os logs de um drone específico está levando vários segundos. O sistema está ficando lento e precisamos otimizar a velocidade de busca sem alterar o código da aplicação.

## 🛠️ Necessidade Técnica

Quando fazemos um `SELECT ... WHERE drone_id = 'X'`, o banco precisa ler linha por linha (Full Table Scan) se não houver um guia.

* **INDEX (Índice):** Funciona como o índice remissivo de um livro. Ele cria uma estrutura separada que aponta exatamente onde os dados estão, transformando buscas lentas em buscas instantâneas.
* **EXPLAIN QUERY PLAN:** Um comando de auditoria que revela "como" o banco de dados pretende executar a sua consulta. É a ferramenta número 1 para o Engenheiro de Performance.

## ⚠️ Análise de Falha Crítica: Fragmentation em Índices

A criação excessiva de índices ou a inserção aleatória de dados pode levar à **Fragmentação**. Isso acontece quando as páginas da B-Tree do índice não estão mais contíguas no disco, forçando o cabeçote de leitura a saltar entre setores físicos.
*   **Impacto:** Degradação gradual da performance de busca, anulando o benefício do índice.
*   **Prevenção:** Monitoramento regular via `ANALYZE` e reconstrução de índices fragmentados com `REINDEX`.

## 📋 Requisitos

1. Criar a tabela `historico_voo` (id, drone_id, evento, data_hora).
2. Simular uma massa de dados (várias linhas para o mesmo drone).
3. Analisar o plano de busca ANTES da indexação.
4. Criar um índice para a coluna `drone_id`.
5. Analisar o plano de busca DEPOIS da indexação e comparar os resultados.
