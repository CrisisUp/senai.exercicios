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
4. Realizar uma consulta que extraia o valor de um sensor específico ("temperatura") de dentro do JSON como se fosse uma coluna comum.
