# 💎 SA-04: Data Warehouse de Inteligência Logística (Desafio Final)

## 🎯 Estudo de Caso
A "SkyCargo" tornou-se uma multinacional. Agora gerenciamos milhares de drones em diferentes continentes, cada um com uma estrutura de peças complexa. A diretoria precisa de um **Data Warehouse** (Armazém de Dados) que entregue relatórios de elite:
1. Quais são os drones mais produtivos por região?
2. Qual a estrutura completa de custos de manutenção de um drone (incluindo todas as suas sub-peças)?
3. Como garantir que, se um drone for aposentado, toda a sua árvore de dados seja limpa ou arquivada com segurança?

## 🛠️ Necessidade Técnica
Este desafio integra TODO o conhecimento da trilha SQL Mastery, com foco no Nível 40:
1.  **Window Functions:** Para gerar rankings de performance regional sem perder o detalhe das viagens.
2.  **Recursive CTEs:** Para navegar na árvore de componentes de hardware (BOM).
3.  **Integridade e Cascatas:** Para garantir que o banco seja autolimpante e à prova de erros de inserção.
4.  **Views Avançadas:** Para consolidar a complexidade técnica em um dashboard executivo.

## 📋 Requisitos Funcionais
1. Criar a estrutura relacional completa: `frota`, `viagens`, `componentes`.
2. Implementar **ON DELETE CASCADE** nos relacionamentos críticos.
3. Criar uma **View** `v_dashboard_produtividade` que use Window Functions para mostrar o ranking de cada drone em sua região.
4. Criar um script de consulta que utilize **WITH RECURSIVE** para listar todas as peças de um drone específico.
5. Demonstrar uma transição de estado/limpeza usando as restrições de integridade.

## ⚠️ Análise de Falha Crítica (Falhas de Logística)

Em um Data Warehouse global, falhas de integridade e lógica podem cegar a diretoria e causar prejuízos multimilionários:

1.  **Distorção de Ranking Regional:** O uso inadequado de Window Functions (`RANK()` vs `DENSE_RANK()`) ou a falta de tratamento de nulos em agregações de distância podem distorcer a produtividade real, levando a investimentos errôneos em regiões menos eficientes.
2.  **Recursão Infinita e Travamento de Servidor:** Falhas na definição de ciclos em tabelas de componentes (`Recursive CTEs`) podem causar loops infinitos que consomem toda a CPU/RAM do banco de dados, paralisando a operação global.
3.  **Expurgo Acidental de Ativos (Cascata Descontrolada):** O uso imprudente de `ON DELETE CASCADE` pode resultar na deleção de anos de histórico de viagens e componentes ao remover um drone da frota, se não houver um processo de arquivamento (Shadow Tables) antes da exclusão.
4.  **Inconsistência Monetária Global:** A conversão de moedas e o armazenamento de custos em `REAL` em um DW de larga escala amplificam erros de arredondamento, tornando impossível uma auditoria financeira precisa entre diferentes continentes.

## 🏗️ Estrutura de Arquivos Obrigatória
- `README.md`: Este guia.
- `queries.sql`: A arquitetura completa do Data Warehouse.
- `INTERACAO_SQLITE.md`: O manual do Lead Data Architect.
