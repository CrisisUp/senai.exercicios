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

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Este guia mestre.
- `queries.sql`: O motor do ecossistema.
- `voos_externos.csv`: Dados de entrada para o processo ETL.
- `INTERACAO_SQLITE.md`: Manual do Operador de Elite.
