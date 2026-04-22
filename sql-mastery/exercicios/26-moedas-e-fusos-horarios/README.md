# 🗄️ Atividade 26: Operações Internacionais (Moedas e Fusos)

## 🎯 Estudo de Caso

A "SkyCargo" agora realiza entregas entre **Brasil (BRL)** e **Inglaterra (GBP)**.

- Uma entrega registrada às 12:00 em Londres acontece às 09:00 em São Paulo.
- O custo da bateria é cobrado em Libras (GBP), mas o relatório consolidado deve ser em Reais (BRL).
Precisamos de um sistema que normalize o tempo para UTC e converta os valores financeiros usando uma tabela de câmbio.

## 🛠️ Necessidade Técnica

- **UTC Normalization:** Usar `strftime('%Y-%m-%d %H:%M:%S', 'now')` para garantir tempo universal.
- **Time Offsets:** Usar modificadores como `'-3 hours'` ou `'+1 hours'` no SELECT.
- **Câmbio Dinâmico:** Realizar um `JOIN` que busca a taxa de conversão mais recente.

## 📋 Requisitos

1. Criar a tabela `taxas_cambio` (moeda, taxa_para_brl, data_referencia).
2. Criar a tabela `entregas_globais` (id, drone_id, custo_local, moeda, data_utc).
3. Inserir dados de entregas em GBP e USD.
4. Criar uma query que:
    - Mostre a hora em **UTC**, **Londres** e **São Paulo**.
    - Converta todos os custos para **BRL**.
