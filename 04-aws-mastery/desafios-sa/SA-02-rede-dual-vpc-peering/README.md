# 🌐 Desafio SA-02

- Rede Dual-VPC Peering e Hospedagem Híbrida
- `STATUS:` Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

A "SkyCargo" está expandindo sua infraestrutura para uma arquitetura multi-região
lógica. Precisamos isolar o sistema de faturamento (`alpha-vpc`) do sistema de
marketing (`alpha2-vpc`), mas permitir que eles se comuniquem de forma segura e
privada via **VPC Peering**. Além disso, o sistema de faturamento deve se
conectar a um banco de dados centralizado **RDS MySQL**.

## 🛠️ Necessidade Técnica (Topologia de Rede)

Este projeto é um teste de maestria em **Networking AWS**:

- **Dual VPC:** Duas redes virtuais isoladas com CIDRs não-sobrepostos.
- **Subnetting:** Separação entre camadas Públicas (Web) e Privadas (DB/NAT).
- **VPC Peering:** Túnel privado entre as redes para tráfego direto.
- **RDS Integration:** Banco de dados MySQL gerenciado com acesso restrito.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA DE REDE)

- `RISCO DE CIDR OVERLAP:` Se ambas as VPCs usassem `10.0.0.0/16`, o Peering seria
  impossível. O roteamento falharia pois o banco não saberia para qual rede
  enviar o pacote. (Solução: Alpha=10.0, Alpha2=10.1).
- `RISCO DE ASYMMETRIC ROUTING:` Configurar o Peering mas esquecer de atualizar as
  **Route Tables** em ambos os lados. O pacote vai, mas a resposta nunca volta.
- `RISCO DE SECURITY GROUP LOCK:` Bloquear o protocolo ICMP entre as VPCs impedirá
  o PING de validação, mesmo que a rede esteja fisicamente conectada.

## 📋 Requisitos de Elite

1. Template CloudFormation único para toda a infraestrutura (Determinismo).
2. Provisionamento de EC2 com scripts `User Data` para deploy automático do site.
3. Configuração de RDS MySQL 8.0 com integridade bancária.
4. Validação de conectividade cruzada (VPC Peering Challenge).
