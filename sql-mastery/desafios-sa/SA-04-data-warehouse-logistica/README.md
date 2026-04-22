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

## 🏗️ Estrutura de Arquivos Obrigatória
- `README.md`: Este guia.
- `queries.sql`: A arquitetura completa do Data Warehouse.
- `INTERACAO_SQLITE.md`: O manual do Lead Data Architect.
