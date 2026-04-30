# 🦀🗄️ Atividade Integradora 30: Auditoria Forense (Shadow Tables)

## 🎯 Estudo de Caso

A "SkyCargo" exige auditoria completa sobre as configurações críticas dos drones. Se um operador alterar o limite de velocidade ou a versão do firmware, o sistema deve registrar automaticamente:

1. Quem alterou (simulado).
2. Qual era o valor antigo.
3. Qual é o novo valor.
4. Data e Hora exatas.

O desafio é fazer isso sem que o código Rust precise se preocupar com o log. O **SQL (Trigger)** cuidará da gravação automática na **Shadow Table**.

## 🛠️ Necessidade Técnica

Integrar automação de banco com interface de backend:

* **Shadow Table:** Uma tabela espelho que guarda o histórico de mudanças.
* **Preventive/Audit Trigger:** Um gatilho SQL que detecta o `UPDATE` e gera o registro de auditoria.
* **Rust CRUD:** Interface para realizar as alterações e visualizar a "Caixa Preta" de auditoria.

## 📋 Requisitos

1. Criar a tabela `drone_configs` (id, serial, firmware).
2. Criar a tabela `caixa_preta_logs` (id, drone_id, valor_velho, valor_novo, data).
3. Implementar o **TRIGGER** `trg_auditoria_drone` no SQL via Rust.
4. Desenvolver o menu interativo:
    - Ver Configuração Atual.
    - Alterar Firmware (Gerando log automático).
    - Ver Auditoria (A "Caixa Preta").
    - Excluir Drone (Verificando se a auditoria persiste).
