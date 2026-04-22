# 💻 Atividade 03

- **EC2** - Computação e Firewalls Virtuais
- `STATUS:` Padrão de Engenharia de Elite Aplicado.

## 🎯 Estudo de Caso

A "SkyCargo" precisa processar os vídeos capturados pelas
câmeras dos drones para detectar obstáculos via IA. Como esse processamento
exige CPU pesada por tempo limitado, não faz sentido comprar um servidor físico.
Usaremos o **Amazon EC2** para criar um servidor Linux potente, realizar o
cálculo e desligá-lo em seguida.

## 🛠️ Necessidade Técnica

O **EC2 (Elastic Compute Cloud)** fornece capacidade computacional redimensionável.
Diferente de um PC comum, ele é regido por:

- **AMI (Amazon Machine Image):** O "template" do S.O. (Amazon Linux, Ubuntu,
etc).  
- **Instance Types:** A combinação de CPU e RAM (ex: `t3.micro`).  
- **Security Groups (SG):** O firewall virtual que controla o tráfego de entrada e
saída.  
- **Key Pairs:** Chaves criptográficas para acesso SSH seguro.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL INFRAESTRUTURA) - RISCO DE SSH ABERTO

(0.0.0.0/0): Deixar a porta 22 aberta para todo o planeta permite ataques de
força bruta. Um Engenheiro de Elite restringe o acesso apenas ao seu IP atual.

- `RISCO DE "GHOST INSTANCE":` Esquecer uma instância potente ligada sem uso
gerará custos de centenas de dólares no fim do mês.  
- `RISCO DE PERDA DE DADOS EFÊMEROS:` O disco local de algumas instâncias é
deletado ao desligar. Dados vitais devem ser persistidos no **Amazon EBS** ou
**S3**.

## 📋 Requisitos de Elite

1. Criação de um Security Group via CLI com regras restritivas.  
2. Provisionamento de uma instância EC2 `t3.micro` (ou similar) programaticamente.  
3. Demonstração de tags para organização de custos (FinOps).
4. Script de encerramento automático para garantir a medalha **Budget Guardian**.
