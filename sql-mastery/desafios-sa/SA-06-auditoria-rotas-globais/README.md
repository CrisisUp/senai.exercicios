# 🛡️ SA-06: Central de Auditoria e Rotas Globais (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" unificou suas bases internacionais. Precisamos de um sistema que:

1. Busque rotas entre cidades (Ativ. 18).
2. Cruze esses dados com o banco de "Drones Aposentados" (Ativ. 16) para garantir que nenhuma rota perigosa use drones velhos.
3. Registre em uma tabela de auditoria (Ativ. 17) toda vez que uma nova rota for inserida ou modificada no mapa global.

## 🛠️ Necessidade Técnica

Este desafio integra:

* **ATTACH DATABASE:** Para conectar o banco de drones aposentados.
* **RECURSIVE CTE:** Para navegar no mapa de cidades.
* **TRIGGERS:** Para auditoria automática de mudanças no mapa.
* **JOIN CROSS-DB:** Para validar a segurança da frota.

## 📋 Requisitos Funcionais

1. Criar o mapa de rotas (tabela `rotas_globais`).
2. Criar a tabela de auditoria `log_rotas`.
3. Anexar o banco `arquivo_morto.db` (da Atividade 16).
4. Implementar um Trigger que grave o log de auditoria ao mudar a quilometragem de uma rota.
5. Realizar uma query que busque o caminho entre Cidade A e Cidade C e mostre se há algum drone inativo associado por erro.

## ⚠️ Análise de Falha Crítica (Riscos de Auditoria Global)

A unificação de bases internacionais e o roteamento de dados exigem atenção a vulnerabilidades sistêmicas:

1.  **Riscos de Performance de Índices Parciais:** O uso de Índices Parciais em rotas críticas (ex: rotas com distância > 1000km) deve ser calibrado com precisão. Se as consultas não utilizarem exatamente o mesmo predicado do índice, o banco ignorará a otimização, resultando em latência catastrófica em sistemas de logística em tempo real.
2.  **Corrupção Multi-banco:** O uso de `ATTACH DATABASE` introduz o risco de corrupção se um dos bancos (como o `arquivo_morto.db`) for desconectado ou sofrer falha de I/O durante uma transação de escrita. Sem o modo `WAL` (Write-Ahead Logging) ativo e sincronizado, a integridade referencial entre os bancos pode ser perdida.
3.  **Latência de Dashboard:** Consultas recursivas (CTE) para navegação de rotas, se não limitadas por profundidade ou não otimizadas por índices nas colunas `origem` e `destino`, podem levar segundos para retornar, congelando dashboards operacionais e impedindo a resposta a incidentes de rota.
4.  **Insegurança de Dados:** Triggers de auditoria são a última linha de defesa. Se houver falha na implementação que permita desativar os triggers (`PRAGMA recursive_triggers = OFF`) ou se as tabelas de log não forem imutáveis, alterações maliciosas em rotas globais podem passar despercebidas pela auditoria.
