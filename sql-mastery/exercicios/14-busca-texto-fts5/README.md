# 🗄️ Atividade 14: Motor de Busca Inteligente (FTS5)

## 🎯 Estudo de Caso

A "SkyCargo" gera milhões de linhas de logs de texto livre descritos pelos pilotos
(ex: "O motor esquerdo vibrou após 10 min de voo"). O gerente precisa buscar
palavras-chave como "vibração", "fumaça" ou "queda" instantaneamente. Usar `LIKE '%vibracao%'` é inviável, pois o banco levaria minutos para ler tudo.

## 🛠️ Necessidade Técnica

O **FTS5 (Full-Text Search version 5)** é um módulo do SQLite que cria tabelas
virtuais otimizadas para busca de palavras:

* **Tokenização:** O banco quebra o texto em palavras e cria um índice reverso.
* **Operador MATCH:** Em vez de comparar caracteres, ele busca o "token" (palavra) diretamente.
* **Performance:** A busca em uma tabela FTS é milhares de vezes mais rápida que o `LIKE`.
* **Snippets:** O banco consegue devolver o trecho do texto onde a palavra foi encontrada, destacando-a.

## 📋 Requisitos

1. Criar uma tabela virtual usando o módulo `fts5`.
2. Popular com logs de voo descritivos.
3. Realizar buscas usando o operador `MATCH`.
4. Demonstrar a busca por prefixos (ex: `vibr*` para achar vibrou, vibração, vibrando).
