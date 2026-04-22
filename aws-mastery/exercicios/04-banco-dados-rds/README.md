# 🗄️ Atividade 04

- **RDS** - Bancos de Dados Relacionais Gerenciados
- `STATUS:` Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

O sistema de logística "SkyCargo" cresceu. O banco de dados
SQLite que usávamos localmente não suporta mais múltiplos acessos simultâneos e
precisa de backups automáticos. Migraremos nossa base de dados para o **Amazon
RDS (Relational Database Service)**, garantindo que as transações de entrega
sejam persistentes e seguras.

## 🛠️ Necessidade Técnica

Instalar um banco de dados em uma EC2 (PC comum) exige que você cuide das
atualizações e do backup. O **RDS** é um serviço gerenciado que cuida disso:

- **Engine:** Escolha do motor (PostgreSQL, MySQL, MariaDB, SQL Server).  
- **Multi-AZ:** Replicação automática em outro Data Center para evitar quedas.  
- **Automated Backups:** Snapshot diário do banco de dados.  
- **Segurança de Rede:** O banco deve residir em uma sub-rede privada, inacessível
pela internet.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA DE DADOS)

- RISCO DE DATABASE EXPOSURE: Colocar o RDS em uma sub-rede pública com a porta
aberta (`0.0.0.0/0`) é o caminho mais rápido para um sequestro de dados (Ransomware).  
- RISCO DE CONNECTION EXHAUSTION: Instâncias pequenas (`t3.micro`) têm limites
baixos de conexões simultâneas. Se o código C++/Rust não fechar as conexões, o banco
travará por esgotamento de recursos.  
- RISCO DE STORAGE FULL: Se o log de transações crescer demais e o armazenamento
encher, o banco entra em modo 'Read-Only', paralisando as operações da SkyCargo.

## 📋 Requisitos de Elite

1. Criação de um Security Group específico para o
banco de dados (DB-SG).  
2. Provisionamento de uma instância RDS (PostgreSQL ou MySQL) via CLI.  
3. Configuração de regras de entrada permitindo acesso apenas a partir do
Security Group da EC2 (Atividade 03).  
4. Demonstração do comando de auditoria de snapshots.
