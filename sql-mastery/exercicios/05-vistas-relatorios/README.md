# 🗄️ Atividade 05: Vistas e Relatórios (CREATE VIEW)

## 🎯 Estudo de Caso

A diretoria da "SkyStore" está cansada de pedir aos analistas para escreverem JOINs complexos e cálculos de desconto toda vez que precisam de um relatório simples. Eles querem uma "Tabela Virtual" que já mostre o produto, o nome do fornecedor e o preço final calculado. Queremos simplificar a vida do usuário final escondendo a complexidade técnica.

## 🛠️ Necessidade Técnica

As **Vistas (Views)** são tabelas virtuais baseadas no resultado de um SELECT:

* **Encapsulamento:** Você salva uma query complexa dentro de um nome simples (ex: `v_relatorio_geral`).
* **Segurança:** Permite que usuários vejam apenas as colunas necessárias, sem expor a estrutura completa do banco.
* **Abstração:** Se a fórmula do preço mudar, você altera apenas a View, e todos os relatórios que a utilizam serão atualizados automaticamente.

## 📋 Requisitos

1. Utilizar a estrutura de `produtos` e `fornecedores` das atividades anteriores.
2. Criar uma View chamada `v_catalogo_completo` que una Produto, Preço e Nome do Fornecedor.
3. Criar uma View chamada `v_promocoes_ativas` que liste apenas produtos com desconto > 0, já com o preço final calculado.
*   Realizar consultas simples diretamente sobre as Views (como se fossem tabelas comuns).

## ⚠️ Análise de Falha Crítica

**Risco:** Degradação de Performance em Views Empilhadas (Nested Views).
**Cenário:** Criar views que consultam outras views que, por sua vez, realizam joins complexos. Em grandes volumes de dados, o otimizador de consultas pode ter dificuldade em aplicar índices de forma eficiente, resultando em lentidão extrema.
**Solução:** Evitar o excesso de camadas de abstração. Monitorar o plano de execução e, se necessário, materializar os dados (Materialized Views - não disponível nativamente no SQLite, mas simulável via tabelas temporárias) para relatórios pesados.

