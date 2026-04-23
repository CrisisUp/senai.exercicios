# 📊 SA-02: Sistema de Faturamento e Auditoria (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyStore" está se profissionalizando. O setor financeiro agora exige que cada venda registre o valor dos impostos separadamente. Além disso, para evitar furos no estoque, toda venda deve ser uma operação blindada: se o estoque não puder ser baixado, o pedido não pode ser registrado. Por fim, a contabilidade quer uma visão simplificada de quanto imposto foi gerado por mês.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos do Nível 21 (Atividades 04 a 06):

1. **Evolução do Esquema (ALTER TABLE):** Adicionar colunas de impostos e data de faturamento nas tabelas existentes.
2. **Transações (BEGIN/COMMIT):** Garantir que a inserção do pedido, dos itens e a atualização do estoque ocorram de forma atômica.
3. **Vistas (VIEWS):** Criar um dashboard virtual de auditoria que mostre faturamento bruto, impostos e lucro líquido.

## 📋 Requisitos Funcionais

1. Modificar a tabela `itens_pedido` para incluir a coluna `imposto_valor` (REAL).
2. Criar uma Transação de Venda Completa:
    - Inserir um novo pedido.
    - Inserir itens vinculados com cálculo de imposto (ex: 10% do valor unitário).
    - Baixar a quantidade correspondente da tabela `estoque_geral` (da Atividade 06).
3. Criar uma View chamada `v_auditoria_financeira` que consolide esses dados.
4. Demonstrar um cenário de ROLLBACK caso ocorra uma falha simulada (ex: tentar vender mais do que há no estoque).

## ⚠️ Análise de Falha Crítica (Erros de Faturamento)

O sistema de faturamento é o coração financeiro da empresa, e falhas nesta camada podem levar a prejuízos diretos e problemas legais:

1. **Cálculo de Imposto Impreciso:** O uso de `REAL` para impostos pode gerar dízimas periódicas que, ao serem somadas em milhares de transações, resultam em diferenças significativas no recolhimento fiscal.
2. **Vendas sem Estoque (Race Conditions):** Sem o uso de transações atômicas (`BEGIN/COMMIT`) e travas adequadas, dois pedidos simultâneos podem "vender" o mesmo item físico, resultando em estoque negativo ou pedidos não atendidos.
3. **Faturamento Fantasma:** Se um pedido for inserido mas a transação falhar antes de registrar os itens ou baixar o estoque (sem um `ROLLBACK`), o sistema terá um registro de venda sem produtos associados.
4. **Violação de Integridade na View:** Se a View de auditoria não considerar cancelamentos ou devoluções, o relatório financeiro apresentará um faturamento inflado, levando a decisões gerenciais baseadas em dados falsos.

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Contexto e requisitos (Este arquivo).
- `queries.sql`: Script de preparação e lógica de transação.
- `INTERACAO_SQLITE.md`: Guia de "Copiar e Colar" para o terminal.
