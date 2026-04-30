# 🏢 SA-09: Hub Assíncrono de Operações Globais (Desafio Integrador)

## 🎯 Estudo de Caso
A central de comando da "SkyCargo" precisa de uma atualização tecnológica. Atualmente, o monitoramento de faturamento internacional e a atualização de estoque são lentos e travam o sistema principal. O novo **Hub de Operações** deve integrar as melhores práticas de backend e dados aprendidas no ciclo.

## 🛠️ Necessidade Técnica
Este desafio integra os conhecimentos do ciclo de Integração (Atividades 25 a 27):
1.  **Connection Pooling:** Para gerenciar o acesso de múltiplos drones simultâneos ao banco.
2.  **Migrações Automáticas:** Garantir que as tabelas de faturamento global existam ao iniciar.
3.  **Assincronismo (Tokio):** Realizar o processamento de câmbio sem bloquear a interface de usuário.

## 📋 Requisitos Funcionais
1. Ao iniciar, o programa deve verificar/criar a tabela `faturamento_global`.
2. Criar um **Pool de Conexões** (r2d2).
3. Implementar uma tarefa assíncrona que simula o recebimento de uma fatura em Dólar (USD).
4. Usar `spawn_blocking` para converter o valor para BRL (usando a inteligência do SQL) e salvar no banco.
5. Manter um loop de navegação do drone rodando simultaneamente sem atrasos.

## 🏗️ Estrutura de Arquivos Obrigatória
- `README.md`: Este guia.
- `main.rs`: O motor assíncrono integrado.
