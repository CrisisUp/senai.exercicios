# 🗄️ Atividade Bônus 13: Flexibilidade Moderna (JSON e UPSERT)

## 🎯 Estudo de Caso

A "SkyCargo" começou a utilizar sensores experimentais que enviam dados variados (um dia enviam pressão, outro dia umidade, outro dia apenas GPS). Criar colunas para cada sensor novo seria um pesadelo de manutenção. Além disso, os drones enviam atualizações de status constantemente. Se o drone já existir no banco, queremos apenas atualizar sua "última telemetria", caso contrário, queremos registrá-lo.

## 🛠️ Necessidade Técnica

Esta atividade apresenta os recursos de "Vanguarda" do SQL:

* **JSON Functions:** O SQLite permite tratar texto como objetos estruturados.
  * `json_extract()`: Extrai um valor específico de dentro de um texto JSON.
  * `json_valid()`: Garante que o texto inserido é um JSON válido.
* **UPSERT (ON CONFLICT):** Um híbrido entre INSERT e UPDATE.
  * Tenta inserir um registro.
  * Se houver um conflito de Chave Única (ex: Serial do Drone), ele desvia para um comando de atualização automático.

## 📋 Requisitos

1. Criar a tabela `telemetria_avancada` com `id`, `drone_serial` (UNIQUE) e `dados_json` (TEXT).
2. Criar uma restrição `CHECK` para garantir que o campo `dados_json` seja um JSON válido.
3. Usar o comando **UPSERT** para registrar drones.
- Realizar uma consulta que extraia o valor de um sensor específico ("temperatura") de dentro do JSON como se fosse uma coluna comum.

## ⚠️ Análise de Falha Crítica

A flexibilidade do JSON e a conveniência do UPSERT trazem riscos operacionais severos:

1.  **Corrupção de Dados (JSON Invalid):** Sem a constraint `CHECK(json_valid(dados_json))`, o banco aceita qualquer string malformada. Isso causará falhas catastróficas em aplicações que tentarem parsear o JSON na camada de software.
2.  **Overhead de Performance:** Extrair dados de um JSON (`json_extract`) exige que o banco faça o "parse" do texto em cada linha. Em tabelas com milhões de registros, isso é ordens de grandeza mais lento que colunas nativas.
3.  **Perda de Histórico no UPSERT:** O UPSERT, por definição, sobrescreve dados existentes. Se não houver uma tabela de log/histórico, informações críticas anteriores (como telemetria antiga) serão apagadas para sempre.
4.  **Schema Drift:** Como o JSON aceita qualquer chave, o banco pode acabar com uma mistura de chaves como `temp`, `temperatura`, `t`, dificultando enormemente a criação de relatórios consistentes.

