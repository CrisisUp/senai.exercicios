# 🛡️ Atividade 12

- **IaC Avançado** - Sobrevivência de Dados e Resiliência
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" está migrando toda a sua infraestrutura para código. O CEO fez uma
pergunta crítica: "Se rodarmos um comando de deleção por erro no nosso
CloudFormation, perdemos todo o histórico de voo e faturamento?". Como
Arquiteto, sua resposta deve ser: "Não, pois implementamos Blindagem de
Retenção".

## 🛠️ Necessidade Técnica

Serviços que guardam estado (Bancos de Dados) exigem tratamentos especiais no
CloudFormation através da propriedade **DeletionPolicy**:

- **Retain:** O recurso permanece intacto na conta após a deleção da stack.
- **Snapshot:** Exclusivo para RDS/EBS/Redshift. Cria um backup final antes de
  destruir a instância física.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL CONTINUIDADE DE NEGÓCIO)

- `RISCO DE ACCIDENTAL WIPE:` Comandos de CI/CD mal configurados podem disparar
  `delete-stack`. Sem DeletionPolicy, os dados morrem com o código.
- `RISCO DE ORPHANED COSTS:` O uso de 'Retain' protege o dado, mas mantém o custo
  ativo na fatura. O Engenheiro de Elite deve auditar recursos órfãos.
- `RISCO DE SNAPSHOT OVERFLOW:` No RDS, snapshots ocupam espaço. Milhares de
  snapshots de bancos deletados podem gerar custos fantasmas se não houver
  limpeza periódica.

## 📋 Requisitos de Elite

1. Template YAML descrevendo uma Tabela DynamoDB e uma Instância RDS.
2. Aplicação de `DeletionPolicy: Retain` para o DynamoDB.
3. Aplicação de `DeletionPolicy: Snapshot` para o RDS.
4. Uso de `Parameters` para isolar credenciais sensíveis (Guardião Financeiro).
