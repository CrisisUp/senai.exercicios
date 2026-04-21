# 🗄️ Atividade 09: Automação com Gatilhos (TRIGGERS)

## 🎯 Estudo de Caso

Até agora, na "SkyStore", sempre que registrávamos uma venda, precisávamos de um comando manual (ou uma transação) para baixar o estoque. O problema é que, se o desenvolvedor esquecer de enviar o comando de baixa, o estoque fica errado. Queremos que o próprio **Banco de Dados** assuma essa responsabilidade: sempre que um item for inserido em um pedido, o estoque deve diminuir automaticamente.

## 🛠️ Necessidade Técnica

Os **Gatilhos (Triggers)** são blocos de código SQL que "disparam" automaticamente em resposta a eventos (INSERT, UPDATE ou DELETE):

* **Automação:** Garante que tarefas repetitivas e críticas sempre aconteçam.
* **Integridade:** Impede que o estoque e as vendas fiquem descasados por erro humano.
* **AFTER INSERT:** O gatilho roda logo após um novo registro entrar na tabela de itens.

## 📋 Requisitos

1. Criar a tabela `produtos_estoque` (id, nome, quantidade).
2. Criar a tabela `vendas_registro` (id, produto_id, qtd_vendida).
3. Criar um **TRIGGER** chamado `trg_baixar_estoque`.
4. O gatilho deve subtrair a `qtd_vendida` da tabela `produtos_estoque` sempre que uma linha for inserida em `vendas_registro`.
5. Realizar testes de inserção e provar que o estoque mudou sozinho.
