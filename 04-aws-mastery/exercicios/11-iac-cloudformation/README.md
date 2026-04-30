# 📜 Atividade 11

- **AWS CloudFormation** - O Poder da Infraestrutura como Código
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" cansou de rodar scripts Shell que às vezes falham por falta de
internet ou parâmetros errados. Precisamos de um "Contrato de Infraestrutura"
que garanta que o ambiente de produção seja exatamente igual ao rascunho.
Usaremos o **AWS CloudFormation** para descrever nosso bucket S3 e suas
políticas de segurança em um arquivo YAML.

## 🛠️ Necessidade Técnica

O **CloudFormation** permite tratar sua infraestrutura como se fosse código C++:

- **Templates (YAML/JSON):** A descrição textual dos seus recursos.
- **Stacks (Pilhas):** A unidade lógica que agrupa todos os recursos.
- **Parameters:** Permitem que o mesmo template crie ambientes de 'Dev' ou 'Prod'.
- **Change Sets:** Permite ver o que vai mudar antes de aplicar a alteração.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ENGENHARIA DE INFRAESTRUTURA)

- `RISCO DE STACK DRIFT:` Se alguém mudar um recurso manualmente pelo console AWS
  (fora do CloudFormation), o template perde a sincronia com a realidade,
  causando falhas em atualizações futuras.
- `RISCO DE CIRCULAR DEPENDENCY:` Tentar criar um recurso A que depende de B,
  enquanto B depende de A, trava a criação da Stack (Rollback automático).
- `RISCO DE DELETE OVERRIDE:` Se você não configurar o 'DeletionPolicy', apagar a
  Stack no CloudFormation deletará todos os seus dados (S3/RDS) permanentemente.

## 📋 Requisitos de Elite

1. Criação de um template `infra.yaml` descrevendo um Bucket S3.
2. Definição de parâmetros dinâmicos para o nome do projeto.
3. Configuração de `Outputs` para exportar a URL do site.
4. Comando CLI para realizar o deploy da Stack.
