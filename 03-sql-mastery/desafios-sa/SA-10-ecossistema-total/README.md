# 🏆 SA-10: O Monumento - Ecossistema de Dados Total (Desafio Final)

## 🎯 Estudo de Caso: SkyCargo Global OS

A "SkyCargo" atingiu a maturidade total. O banco de dados não é mais apenas um
suporte, ele é o **Sistema Operacional de Dados** da empresa. Este ecossistema
deve integrar o recebimento de dados externos, gerenciar hierarquias complexas
de hardware, garantir a segurança contra falhas e ataques, e entregar inteligência
preditiva para a diretoria.

Este é o "Desafio Final" que separa os arquitetos dos mestres.

## 🛠️ Necessidade Técnica

O SA-10 exige a aplicação orquestrada de TODO o conhecimento da trilha:

1. **Engenharia ETL (Ativ. 24):** Importar dados brutos de missões de arquivos CSV externos.
2. **Inteligência de Grafos (Ativ. 18):** Resolver rotas de entrega complexas.
3. **Window Functions de Elite (Ativ. 21):** Monitorar a saúde dos drones via médias móveis.
4. **Segurança de Fortaleza (Ativ. 20):** Impedir deleção de dados críticos.
5. **Automação Robótica (Ativ. 09):** Triggers que atualizam status e disparam alertas.
6. **Sistemas Híbridos (Ativ. 13):** Uso de campos JSON para telemetria flexível.
7. **Performance em Escala (Ativ. 07/15):** Indexação total e planos de busca otimizados.

## 📋 Requisitos Funcionais

1. **Módulo de Carga:** Importar via `.import` uma planilha de voos (`voos_externos.csv`).
2. **Módulo de Estrutura:** Implementar a árvore de componentes do drone (BOM) e consultar recursivamente.
3. **Módulo de Inteligência:** Criar uma View que apresente o ranking de drones, sua média móvel de distância e os dados de telemetria JSON extraídos.
4. **Módulo de Segurança:** Implementar Triggers que bloqueiem qualquer alteração em drones em estado "EM_MISSAO".
5. **Módulo de Backup:** Gerar um script de recuperação total (`backup_final.sql`).

## ⚠️ Análise de Falha Crítica (Total Ecosystem Resilience)

Um ecossistema de dados total é um sistema de alta complexidade onde falhas em cascata podem paralisar a corporação:

1. **Riscos de Performance de Window Functions:** Em um banco com milhões de voos e telemetria JSON, o uso de `RANK()` e `AVG() OVER()` sem índices de cobertura que incluam as colunas de partição e ordenação (como `drone_id` e `data_missao`) resultará em tempos de resposta inaceitáveis para sistemas de controle de tráfego aéreo.
2. **Corrupção Massiva em Hierarquias Recursivas:** Consultas recursivas (CTEs) mal formuladas ou a falta de limites de profundidade podem causar estouro de pilha (stack overflow) no motor do banco de dados. Além disso, operações de deleção em cascata (`ON DELETE CASCADE`) em grandes árvores de componentes podem causar bloqueios prolongados e corrupção se o hardware falhar durante a propagação.
3. **Data Leaks via Telemetria JSON:** O armazenamento de dados em JSON é flexível, mas perigoso. Se chaves sensíveis (como coordenadas de bases secretas ou chaves de criptografia) forem inseridas inadvertidamente no JSON, elas podem ser expostas por Views que não filtram campos específicos, permitindo vazamentos massivos de inteligência.
4. **Inconsistência de Backup em Sistemas Híbridos:** A presença de triggers complexos e transações que envolvem arquivos externos (ETL) e JSON interno exige uma estratégia de backup atômica. Backups parciais ou realizados via sistema de arquivos sem o comando `.backup` podem resultar em um estado onde os metadados (JSON) não coincidem com a estrutura física (tabelas), tornando o banco inútil para recuperação.

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Este guia mestre.
- `queries.sql`: O motor do ecossistema.
- `voos_externos.csv`: Dados de entrada para o processo ETL.
- `INTERACAO_SQLITE.md`: Manual do Operador de Elite.
