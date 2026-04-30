# 🪣 Atividade 02

- **S3** - Armazenamento e Hospedagem Estática
- `STATUS:` Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

A "SkyCargo" precisa de um local centralizado para armazenar os manuais de
manutenção dos drones e os logs de voo. Além disso, eles querem um painel web
simples onde os clientes possam verificar o status das entregas. Em vez de
alugar um servidor completo para um site simples, usaremos o **Amazon S3**.

## 🛠️ Necessidade Técnica

O **S3 (Simple Storage Service)** é o pilar de armazenamento da AWS. Ele não é
um disco rígido comum, mas um armazenamento de objetos:

- **Buckets:** Containers para seus arquivos (nomes devem ser únicos no mundo).
- **Static Website Hosting:** Capacidade de servir arquivos HTML/CSS/JS sem
servidor (Serverless).  
- **Bucket Policies:** Regras JSON que definem quem pode ler ou escrever dados.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA DE DADOS)

- `RISCO DE EXPOSIÇÃO PÚBLICA (DATA LEAK):` Deixar um bucket com permissão de
leitura pública para arquivos sensíveis (como CPFs ou chaves de criptografia).
A AWS bloqueia isso por padrão hoje, mas erros de política ainda ocorrem.

- `RISCO DE EXCLUSÃO ACIDENTAL:` Sem a ativação do **Versioning** (Versionamento),
um arquivo deletado ou sobrescrito é perdido para sempre.

- `RISCO DE CUSTO INVISÍVEL:` Milhares de logs pequenos podem gerar um custo alto
de requisições API (PUT/GET). Solução: Ciclo de vida (Lifecycle Policies) para
mover dados para classes de armazenamento mais baratas (Glacier).

## 📋 Requisitos de Elite

1. Criação de um Bucket S3 via CLI com nomeação padronizada.  
2. Configuração do bucket para Hospedagem de Site Estático.  
3. Implementação de uma Bucket Policy que permite apenas leitura pública (Get)
para o site.  
4. Upload de um arquivo `index.html` de telemetria simulada.
