# ☁️ Atividade 01

- **Setup, Segurança e CLI** (A Fundação Cloud)
- `STATUS:` Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

A "SkyCargo" está migrando seus servidores locais para a nuvem. O primeiro erro
de um engenheiro júnior é usar a conta "Root" para tudo e deixar chaves de
acesso (`Access Keys`) expostas no código. Precisamos configurar o ambiente
seguindo o **Princípio do Menor Privilégio**.

## 🛠️ Necessidade Técnica

A AWS é um oceano de recursos. O controle começa no **IAM (Identity and Access
Management)**:

- **IAM Users vs Roles:** Por que nunca usar a conta Root.  
- **AWS CLI:** Comandar a nuvem via terminal (Engenharia de Automação).  
- **MFA** (Multi-Factor Authentication):** A primeira linha de defesa.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL SEGURANÇA EM NUVEM)

- `RISCO DE ACCESS KEY LEAK:` Se você comitar suas chaves no GitHub, robôs as
capturarão em segundos e minerarão criptomoedas na sua conta, gerando dívidas de
milhares de dólares. (Solução: `.gitignore` e Roles).  
- `RISCO DE PRIVILEGE ESCALATION:` Uma política de permissão muito "aberta" (`*`)
permite que um atacante assuma o controle total da infraestrutura.  
- `RISCO DE BILLING SPYKE:` Sem alarmes de orçamento, um erro de script pode
instanciar milhares de servidores, destruindo o caixa da empresa.

## 📋 Requisitos de Elite

1. Configuração do Perfil AWS CLI via `aws configure`.  
2. Criação de um usuário IAM com permissões restritas (PowerUser).  
3. Ativação de MFA na conta mestre.
4. Interface de comando para listar recursos básicos.
