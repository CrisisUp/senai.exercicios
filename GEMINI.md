# 📘 Protocolo de Expansão de Conteúdo (PEC) - SENAI C++

Este documento serve como a diretriz mestre para a evolução deste repositório educacional.

## 🎯 Objetivo

Construir conhecimento em C++ de forma modular, prática e incremental. Cada novo conceito deve ser fundamentado nos anteriores e validado por desafios integradores.

## 🛠️ Estrutura do Ciclo de Aprendizado (Regra 3+1)

A cada ciclo de 4 entregas:

1. **Atividades 1, 2 e 3:** Introdução de **um** novo conceito técnico aplicado a um domínio de negócio real.
2. **Desafio Integrador:** Projeto robusto que utiliza **exclusivamente** o que foi aprendido até aquele momento.

## 🎮 Sistema de Maestria (Gamificação)

Para motivar a evolução, o projeto adota um sistema de XP (Experiência) e Conquistas:

### 📈 Níveis de Competência

- **Nível 1-10 (Iniciado):** Domina lógica básica, vetores e funções.
- **Nível 11-20 (Arquiteto):** Domina Estruturas STL, Arquivos e Exceções. **Obrigatório: Arquitetura Modular (.h e .cpp).**
- **Nível 21-30 (Mestre POO):** Domina Herança, Polimorfismo e Abstração.
- **Nível 31+ (Engenheiro de Elite):** Domina Templates, Memória Dinâmica e Padrões de Projeto.

### 🏅 Medalhas de Honra (Achievements)

- 🛡️ **Código Blindado:** Primeira vez que tratou exceções (try-catch) com sucesso.
- 🧬 **Mestre Genético:** Implementou sua primeira hierarquia de herança.
- 🏭 **Engenheiro de Refatoração:** Concluiu um desafio de modernização de legado.
- 💰 **Guardião Financeiro:** Implementou lógica de centavos inteiros (integridade bancária).
- ✨ **Zero Warning:** Completou um ciclo inteiro (3+1) sem nenhum aviso do compilador.

---

## 📋 Padrão de Entrega (Obrigatório)

...
Para cada nova atividade, a entrega deve seguir esta ordem:

### 1. Documento de Contexto (`atividade-extraXX.txt`)

- **Estudo de Caso:** Cenário do mundo real.
- **Necessidade Técnica:** Por que o conhecimento atual não basta e qual a nova ferramenta resolverá o problema.
- **Requisitos:** Lista de funcionalidades obrigatórias.

### 2. Código Fonte (`atividade-extraXX.cpp`)

- **Cabeçalho Doxygen completo:** (`@file`, `@brief`, `@author`, `@date`).
- **Comentários didáticos:** Explicação linha a linha da nova sintaxe.
- **Interface amigável:** Uso de cores ANSI para feedback de erro/sucesso.
- **Resumo Teórico (Obrigatório ao final):** Comentário em bloco detalhando os novos aprendizados técnicos e a lógica de negócio aplicada.
- **Assuntos Correlatos (Obrigatório ao final):** Tópicos para pesquisa futura que complementam o assunto, mesmo que não usados no código atual.

### 3. Validação

- O código deve ser compatível com o `Makefile` existente.
- Executar `make` para garantir zero erros/warnings.

## ⚠️ Restrições Inegociáveis

- **Proibido "Saltar Etapas":** Nunca usar bibliotecas ou recursos avançados se o cronograma ainda não os alcançou.
- **Foco em Negócios:** Toda atividade deve simular uma dor real de uma empresa ou profissional.
- **Arquitetura Modular (Nível 11+):** É expressamente proibido o uso de um único arquivo `.cpp` para atividades deste nível. O código deve ser decomposto em cabeçalhos e implementações para ensinar organização de sistemas.
- **Código Limpo:** Priorizar legibilidade e tratamento de erros compatível com o nível atual.

---
*Documento gerado em 19/04/2026 para guiar o aprendizado de C++.*
