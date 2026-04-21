# 🗄️ Atividade 04: Evolução do Esquema (ALTER TABLE e Manutenção)

## 🎯 Estudo de Caso

O sistema da "SkyStore" precisa evoluir. O departamento de marketing solicitou que agora cada produto tenha uma **Avaliação (1 a 5 estrelas)** e uma coluna de **Desconto (%)** para promoções sazonais. Como já temos dados cadastrados, não podemos simplesmente apagar a tabela e criar de novo. Precisamos modificar a estrutura da tabela existente sem perder as informações.

## 🛠️ Necessidade Técnica

Na vida real, bancos de dados estão em constante mudança:

* **ALTER TABLE:** Comando usado para adicionar, remover ou modificar colunas em uma tabela viva.
* **UPDATE:** Comando para alterar os valores de registros que já existem.
* **Default Values:** Definir um valor padrão para novas colunas para que os registros antigos não fiquem vazios (null).

## 📋 Requisitos

1. Utilizar a tabela `produtos` da Atividade 01/02.
2. Adicionar a coluna `avaliacao` (tipo INTEGER).
3. Adicionar a coluna `desconto` (tipo REAL) com valor padrão de 0.0.
4. Atualizar o preço ou desconto de itens específicos.
5. Realizar uma consulta que calcule o "Preço Final" (Preço - Desconto).
