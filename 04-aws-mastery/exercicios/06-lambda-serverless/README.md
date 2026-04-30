# ƛ Atividade 06

- **AWS Lambda** - Computação Serverless Orientada a Eventos
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" quer que, sempre que um drone registrar um status de "Bateria
Baixa" no DynamoDB, uma mensagem de alerta seja enviada para a central de
manutenção. Em vez de ter um servidor EC2 rodando 24h apenas para checar isso,
usaremos o **AWS Lambda**: uma função que "acorda", processa o alerta e "morre"
em milissegundos.

## 🛠️ Necessidade Técnica

O **AWS Lambda** permite rodar código sem provisionar ou gerenciar servidores.
Você paga apenas pelo tempo de execução (em milissegundos).

- **Handler:** A função principal que recebe o evento.
- **Trigger:** O gatilho que dispara a função (S3, DynamoDB, API Gateway).
- **Runtime:** O ambiente de execução (Python, Node.js, Rust, Go).
- **Execution Role:** Permissão IAM para a função acessar outros serviços.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA SERVERLESS)

- `RISCO DE COLD START:` Se a função ficar muito tempo sem uso, a primeira chamada
  será lenta, pois a AWS precisa "instanciar" o container. Em missões de
  segurança aérea de milissegundos, isso pode ser um problema.
- `RISCO DE TIMEOUT:` Se o código entrar em loop ou demorar mais que o tempo
  configurado (padrão 3s), a AWS mata o processo no meio, causando perda de
  dados.
- `RISCO DE CONCURRENCY LIMIT:` Se ocorrerem 100.000 alertas ao mesmo tempo, o
  Lambda pode atingir o limite da conta e começar a rejeitar requisições
  (Throttling).

## 📋 Requisitos de Elite

1. Criação de um pacote de implantação (.zip) contendo o código da função.
2. Provisionamento de uma IAM Role com permissão de execução (LambdaBasic).
3. Criação da função `AlertHandler` via CLI.
4. Teste de invocação manual simulando um evento de "Bateria Crítica".
