# 📊 SA-09: Central de Monitoramento Global e Segurança (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" opera em 3 continentes e sofre com tentativas de sabotagem de dados. Precisamos de um sistema que:

1. Converta o faturamento de várias moedas para BRL (Ativ. 26).
2. Detecte acessos suspeitos em alta velocidade (Ativ. 25).
3. Monitore a latência das transações e alerte o SRE se houver lentidão (Ativ. 27).

## 🛠️ Necessidade Técnica

Este desafio integra:

* **Window Functions (LAG):** Para detecção de Brute Force.
* **JOINs de Câmbio:** Para normalização financeira global.
* **Triggers de Observabilidade:** Para gerar alertas automáticos de latência.

## 📋 Requisitos Funcionais

1. Criar o banco `seguranca_global.db`.
2. Implementar a tabela de `acessos` e o Trigger Sentinela de performance.
3. Criar a View de `faturamento_unificado` que busca taxas em uma tabela de câmbio.
4. Simular um ataque de brute force (várias inserções em 1 segundo) e verificar se o sistema gerou o alerta.

## ⚠️ Análise de Falha Crítica (Global Security Monitoring)

Sistemas de monitoramento global são alvos primordiais e possuem vulnerabilidades críticas:

1.  **Riscos de Performance de Window Functions:** A detecção de padrões de ataque em tempo real usando `LAG()` sobre milhões de registros de log sem índices parciais ou particionamento temporal pode degradar a latência do sistema, transformando a ferramenta de segurança em um vetor de negação de serviço (DoS).
2.  **Corrupção Massiva de Alertas:** Gatilhos complexos que realizam múltiplas inserções em tabelas de auditoria (`alertas`) podem causar corrupção se o limite de recursão de triggers for atingido ou se houver falhas de escrita durante picos de ataques massivos, resultando em "pontos cegos" na monitoração.
3.  **Data Leaks via Analytics:** Views financeiras que unem dados de operações e taxas de câmbio podem expor margens de lucro e dados de faturamento sensíveis a usuários que deveriam ter apenas acesso aos logs de segurança se não houver uma separação rígida de privilégios ou esquemas (schemas).
4.  **Inconsistência de Backup sob Stress:** Tentar realizar backups a quente (hot backups) durante um incidente de segurança com alta carga de I/O pode resultar em arquivos de banco de dados inconsistentes, impedindo a análise forense pós-incidente devido à falta de integridade estrutural.
