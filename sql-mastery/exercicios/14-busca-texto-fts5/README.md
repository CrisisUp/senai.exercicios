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
- Demonstrar a busca por prefixos (ex: `vibr*` para achar vibrou, vibração, vibrando).

## ⚠️ Análise de Falha Crítica

O uso de Full-Text Search (FTS5) transforma o banco em um motor de busca, mas traz custos ocultos:

1.  **Overhead de Escrita (Write Penalty):** Cada `INSERT` em uma tabela FTS5 dispara um processo de tokenização (quebra de palavras) e re-indexação. Isso torna a escrita significativamente mais lenta que em tabelas normais.
2.  **Explosão de Armazenamento:** O índice invertido do FTS5 pode ocupar tanto espaço quanto (ou até mais que) os próprios dados originais, aumentando o tamanho do arquivo `.sqlite`.
3.  **Complexidade de Manutenção:** Tabelas FTS5 são "virtuais". Elas não suportam todas as operações de tabelas normais (como algumas constraints de `FOREIGN KEY` complexas) e podem exigir comandos de `OPTIMIZE` periódicos para manter a performance.
4.  **Risco de Corrupção de Índice:** Se o processo for interrompido bruscamente, o índice textual pode ficar dessincronizado com os dados reais, exigindo um `REBUILD` manual da tabela virtual.

