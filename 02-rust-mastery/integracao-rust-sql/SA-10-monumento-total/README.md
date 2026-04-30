# 🏆 SA-10: O Monumento Total (Ecossistema Unificado)

## 🎯 Estudo de Caso: SkyCargo OS (v1.0)

Este é o ápice da jornada. Você deve construir o sistema central que controla a operação global da SkyCargo. O sistema deve:

1. **Hardware:** Chamar um driver em **C++** para processar o sinal de ignição do drone.
2. **Lógica:** Usar **Rust** para gerenciar uma frota multithread que executa missões simultâneas.
3. **Dados:** Persistir os resultados em um **Data Warehouse SQL**, gerando relatórios de inteligência regional.

## 🛠️ Necessidade Técnica (Integração Total)

- **FFI:** Rust chamando C++ para o driver de ignição.
- **Async/Tokio:** Missões de voo rodando em paralelo sem bloquear a central.
- **Connection Pool:** Múltiplas threads acessando o banco de forma eficiente.
- **JSON:** Telemetria complexa salva em campos flexíveis.
- **SQL Analytics:** Relatório final com Window Functions (Rankings).

## 📋 Requisitos Funcionais

1. Implementar o driver de ignição em `driver_hardware.cpp`.
2. Criar o motor Rust que orquestra a conexão e o hardware.
3. Simular o voo de 3 drones ao mesmo tempo.
4. Salvar logs com JSON de status (bateria, coordenadas).
5. Exibir um dashboard SQL de performance consolidada ao final.

## 🏗️ Estrutura de Arquivos Obrigatória

- `main.rs`: O cérebro do sistema.
- `driver_hardware.cpp`: O driver de baixo nível.
- `build.rs`: Compilador do driver.
- `queries.sql`: A inteligência do banco de dados.
