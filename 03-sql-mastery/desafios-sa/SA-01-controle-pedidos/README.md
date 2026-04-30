# 🏢 SA-01: Sistema de Controle de Pedidos (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" expandiu seu modelo de negócios e agora não apenas vende peças, mas também realiza serviços de entrega para **Clientes Corporativos**. Precisamos de um banco de dados que controle quem são os clientes, quais pedidos foram feitos e quais itens compõem cada pedido. O sucesso da operação depende de relatórios precisos sobre o faturamento por cliente e a logística de entrega.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos das Atividades 01, 02 e 03:

1. **SELECT e Filtros (Atividade 01):** Localizar pedidos específicos e clientes.
2. **Agregações e Agrupamentos (Atividade 02):** Somar o valor total de cada pedido e contar quantos pedidos cada cliente fez.
3. **Relacionamentos e JOINs (Atividade 03):** Unir as informações de clientes, pedidos e itens para gerar relatórios completos.

## 📋 Requisitos Funcionais

1. Criar a tabela `clientes` (id, nome, cidade).
2. Criar a tabela `pedidos` (id, cliente_id, data, status).
3. Criar a tabela `itens_pedido` (id, pedido_id, produto, valor_unitario, quantidade).
4. Popular o banco com pelo menos:
    - 3 Clientes.
    - 5 Pedidos.
    - 10 Itens distribuídos entre os pedidos.
5. Realizar consultas complexas que respondam a perguntas de negócio.

## ⚠️ Análise de Falha Crítica (Riscos de Integridade em Pedidos)

A operação de controle de pedidos enfrenta riscos críticos que podem comprometer a confiança do cliente e a saúde financeira da SkyCargo:

1. **Inconsistência de Faturamento:** O uso de tipos de dados de ponto flutuante (`REAL`/`FLOAT`) para valores monetários pode causar erros de arredondamento em grandes volumes, resultando em discrepâncias de centavos que se acumulam.
2. **Orfandade de Dados:** A falta de restrições de `FOREIGN KEY` (ou desativação das mesmas) pode permitir que itens de pedido existam sem um pedido pai, ou pedidos sem um cliente válido.
3. **Duplicidade de Pedidos:** Falhas na validação de entrada podem permitir que o mesmo pedido seja processado múltiplas vezes se não houver chaves únicas compostas ou travas de transação.
4. **Estado Inválido:** Mudanças de status de pedido sem uma máquina de estados (ex: de 'Cancelado' para 'Entregue') podem gerar falhas logísticas graves.

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Contexto e requisitos (Este arquivo).
- `queries.sql`: Script de criação e população.
- `INTERACAO_SQLITE.md`: Guia para execução no terminal.
