# 🗄️ Atividade 06: Transações e Integridade (ACID)

## 🎯 Estudo de Caso

A "SkyCargo" realiza transferências de pacotes entre seu Armazém Central e os Drones em voo. Imagine que um drone reporta ter recebido uma peça:

1. Devemos retirar 1 unidade do estoque do Armazém.
2. Devemos adicionar 1 unidade à carga do Drone.

Se o passo 1 funcionar, mas o sistema travar antes do passo 2, a peça "desaparecerá" do universo. Para evitar isso, usamos **Transações**. Ou tudo acontece perfeitamente, ou nada acontece.

## 🛠️ Necessidade Técnica

As **Transações** garantem as propriedades **ACID**:

* **Atomicidade:** A operação é tratada como um bloco único e indivisível.
* **Consistência:** O banco sai de um estado válido e chega a outro estado válido.
* **Isolamento:** Uma transação não interfere na outra enquanto está rodando.
* **Durabilidade:** Uma vez confirmada, a mudança é permanente.

Comandos Chave:

* **BEGIN TRANSACTION:** Inicia o modo de "rascunho" protegido.
* **COMMIT:** Confirma todas as mudanças e as torna permanentes.
* **ROLLBACK:** Descarta todas as mudanças do rascunho se algo der errado.

## ⚠️ Análise de Falha Crítica: Riscos de Deadlocks

Em sistemas de alta concorrência, as transações podem levar a **Deadlocks** (Impasse). Isso ocorre quando a Transação A bloqueia o Registro 1 e tenta acessar o Registro 2, enquanto a Transação B bloqueia o Registro 2 e tenta acessar o Registro 1. Ambos ficam esperando indefinidamente.
*   **Impacto:** Travamento do banco de dados e timeout em aplicações.
*   **Prevenção:** Sempre acessar recursos em uma ordem consistente e manter transações o mais curtas possível.

## 📋 Requisitos

1. Criar a tabela `estoque_geral` (id, item, quantidade).
2. Criar a tabela `carga_drone` (id, item, quantidade).
3. Simular uma transferência de 5 unidades de um item.
4. Demonstrar o uso do **ROLLBACK** para cancelar uma operação com erro.
5. Demonstrar o uso do **COMMIT** para consolidar uma operação de sucesso.
