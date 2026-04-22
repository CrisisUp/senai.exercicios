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
