# 🛡️ Atividade 25: O Escudo Cibernético (Detecção de Ataques via SQL)

## 🎯 Estudo de Caso

A "SkyCargo" sofreu uma tentativa de acesso não autorizado. Precisamos criar um radar que detecte dois tipos de ataques:

1. **Brute Force:** Tentativas de login repetidas em intervalos de menos de 1 segundo.
2. **Exfiltração/Anomalia:** Uma transação cujo valor é 10x maior que a média histórica daquele drone.

## 🛠️ Necessidade Técnica

Utilizaremos o SQL como motor analítico de segurança:

* **`LAG() OVER()`:** Para olhar o registro anterior e calcular o tempo decorrido.
* **`AVG() OVER()`:** Para calcular a linha de base (baseline) do comportamento normal.
* **`unixepoch()`:** Para converter datas em segundos e permitir cálculos matemáticos precisos.

## 📋 Requisitos

1. Criar a tabela `acessos_sistema` (id, usuario, timestamp, status).
2. Criar a tabela `transacoes_financeiras` (id, drone_id, valor).
3. Criar uma query que identifique usuários com mais de 3 falhas de login seguidas em menos de 5 segundos.
4. Criar uma query que identifique transações suspeitas (acima da média do drone).
