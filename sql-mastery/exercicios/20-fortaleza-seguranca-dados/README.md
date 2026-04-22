# 🗄️ Atividade 20: A Fortaleza de Dados (Segurança e Integridade)

## 🎯 Estudo de Caso

O sistema da "SkyCargo" foi alvo de uma tentativa de invasão onde um usuário
tentou zerar as dívidas de todos os clientes injetando comandos maliciosos.
Além disso, logs críticos de voo foram apagados por erro humano. Precisamos
transformar nosso banco em uma **Fortaleza**:

1. Impedir valores monetários inválidos.
2. Garantir que e-mails tenham um formato básico.
3. Criar uma tabela de logs que seja **IMUTÁVEL** (ninguém pode apagar ou alterar).

## 🛠️ Necessidade Técnica

* **CHECK Constraints com Patterns:** Usar o operador `LIKE` ou `GLOB` dentro do CHECK para validar e-mails.
* **Preventive Triggers:** Criar gatilhos que cancelam operações de `DELETE` ou `UPDATE` indesejadas.
* **RAISE(ABORT, 'mensagem'):** Uma função interna do SQLite que interrompe uma operação e exibe um erro personalizado.

## 📋 Requisitos

1. Criar a tabela `usuarios_central` com e-mail validado e saldo sempre positivo.
2. Criar a tabela `caixa_preta` para logs de segurança.
3. Criar um **TRIGGER** que bloqueie qualquer tentativa de `DELETE` na tabela `caixa_preta`.
4. Criar um **TRIGGER** que bloqueie qualquer tentativa de `UPDATE` na tabela `caixa_preta`.
5. Demonstrar a proteção tentando burlar as regras.
