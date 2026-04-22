# 🗄️ Atividade 23: Resolução de Conflitos Profunda (INSERT OR...)

## 🎯 Estudo de Caso

A "SkyCargo" recebe lotes de dados de parceiros internacionais. Muitas vezes,
esses lotes contêm dados que já temos (conflito de chave única) ou que violam
nossas regras de segurança (horas negativas). Precisamos decidir como o banco
deve reagir: Devemos substituir o dado antigo? Ignorar o novo? Ou parar toda a
operação imediatamente para auditoria?

## 🛠️ Necessidade Técnica

Em SQL, o comando `INSERT` pode ser estendido com cláusulas de resolução de conflitos:

* **REPLACE:** Se houver conflito, deleta a linha antiga e insere a nova (Cuidado: o ID pode mudar!).
* **IGNORE:** Se houver erro, apenas pula aquela linha e continua para a próxima.
* **ABORT / FAIL:** Cancela a operação atual, mas mantém o que já foi feito na transação (com nuances técnicas entre eles).
* **ROLLBACK:** O mais drástico: cancela tudo e desfaz a transação inteira.

## 📋 Requisitos

1. Criar a tabela `frota_internacional` com `serial` (UNIQUE) e `horas_voo` (CHECK >= 0).
2. Demonstrar a diferença entre `INSERT OR IGNORE` e `INSERT OR REPLACE`.
3. Simular um erro de `CHECK` e ver como o `INSERT OR ABORT` se comporta.
4. Realizar consultas de conferência para provar qual dado "venceu" o conflito.

---

## 🛡️ ANÁLISE DE FALHA CRÍTICA (Fase 3)

1. **COLISÕES DE UPSERT:** O uso de `INSERT OR REPLACE` é destrutivo. Ele deleta o registro antigo e insere um novo. Se houver chaves estrangeiras com `ON DELETE CASCADE`, o uso inadvertido de `REPLACE` pode causar uma limpeza em massa de dados relacionados (orphaning).
2. **RESET DE CHAVE PRIMÁRIA:** Ao usar `REPLACE` em tabelas com `AUTOINCREMENT`, o ID original é perdido e um novo é gerado. Isso quebra a rastreabilidade histórica em logs externos que dependem do ID físico do banco.
3. **OVERHEAD DE ROLLBACK:** Em transações massivas, o uso de `INSERT OR ABORT` pode ser custoso, pois exige que o banco mantenha um diário de undo (rollback journal) para cada falha de constraint, impactando o throughput de escrita.
