# 🎮 SA-04: Central de Comando e Controle Inteligente (Desafio Integrador)

## 🎯 Estudo de Caso
A "SkyCargo" evoluiu. Agora, não monitoramos apenas drones isolados, mas uma infraestrutura complexa que inclui: Estações de Carregamento, Sensores Meteorológicos e os próprios Drones. Precisamos de uma **Central de Comando** capaz de gerenciar todos esses dispositivos heterogêneos, processar alertas de segurança em massa e transmitir relatórios de telemetria de forma universal.

## 🛠️ Necessidade Técnica
Este desafio integra os conhecimentos das Atividades 10 a 12:
1.  **Traits (Interfaces):** Para padronizar o comportamento de hardware de diferentes tipos (Drones e Estações).
2.  **Generics e Trait Bounds:** Para criar um sistema de rádio que transmite qualquer informação que siga o protocolo de segurança.
3.  **Iteradores e Closures:** Para filtrar eventos críticos e transformar dados brutos em relatórios de inteligência.
4.  **Dynamic Dispatch (`Box<dyn ...>`):** Para gerenciar a lista heterogênea de hardware na central.

## 📋 Requisitos Funcionais
1. Definir a trait `Hardware` com os métodos `identificador(&self) -> String` e `analisar_seguranca(&self) -> Result<(), String>`.
2. Implementar `Hardware` para as structs `DroneVoo` e `BaseCarregamento`.
3. Criar uma função genérica `transmitir_emergencia<T: Hardware>(dispositivo: &T)` que utiliza a trait bound.
4. Na `main`, criar uma lista polimórfica de hardware.
5. Utilizar iteradores e closures para:
    - Filtrar apenas os dispositivos que apresentam falha de segurança.
    - Transformar os IDs desses dispositivos em uma lista de strings para o esquadrão de manutenção.
6. Garantir que o sistema seja robusto contra falhas de hardware ausente (Uso de Option).

---

## ⚠️ Análise de Falha Crítica (Engenharia de Confiabilidade)

Como este sistema lida com infraestrutura crítica, devemos prever os seguintes cenários de falha em uma implementação de baixo nível:

1.  **Riscos de Race Conditions:** Em um ambiente multithreaded (ex: telemetria chegando via rádio enquanto a central analisa falhas), sem o uso de `Arc<Mutex<T>>` ou `channels`, dois processos poderiam tentar atualizar o estado da bateria de um drone simultaneamente, levando a estados corrompidos ou leituras obsoletas.
2.  **Transactional Inconsistency:** Se uma falha é detectada na `BaseCarregamento` (curto-circuito), o comando de "Desligamento de Emergência" deve ser atômico. Se o sistema falhar entre a detecção e o comando, a estação pode sofrer danos físicos permanentes. Rust mitiga isso forçando o tratamento de todos os caminhos de erro com `Result`.
3.  **Buffer Overflows em Sockets:** Na transmissão via rádio/rede, o uso de buffers fixos sem verificação de limites (comum em C legado) é a porta de entrada para ataques. O sistema de tipos do Rust e a segurança de memória garantem que, mesmo em transmissões genéricas, nunca acessaremos memória fora dos limites do buffer de transmissão.
