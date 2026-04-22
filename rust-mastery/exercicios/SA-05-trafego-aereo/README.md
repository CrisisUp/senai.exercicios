# 🛫 SA-05: Sistema de Controle de Tráfego Aéreo (Desafio Integrador)

## 🎯 Estudo de Caso

A malha aérea da "SkyCargo" tornou-se complexa. Agora, múltiplos drones operam no mesmo espaço aéreo e precisam de uma **Torre de Controle Central**. A torre deve rastrear a posição de cada drone, permitir que administradores calibrem rotas em tempo real e garantir que nenhuma thread de drone corrompa o estado global do tráfego.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos avançados do Nível 31 (Atividades 13 a 15):

1. **Arc (Atomic Reference Counting):** Para permitir que a Torre de Controle e as Threads de cada drone possuam acesso ao estado compartilhado do espaço aéreo.
2. **Mutex (Mutual Exclusion):** Para proteger a lista de drones contra acessos simultâneos de escrita.
3. **Threads:** Para simular o comportamento independente de cada aeronave operando em paralelo.
4. **Interatividade:** O usuário poderá adicionar drones ao sistema e enviar comandos de calibração para toda a frota enquanto ela "voa".

## 📋 Requisitos Funcionais

1. Criar uma struct `DroneAereo` com ID, altitude e status.
2. Criar uma struct `TorreControle` que gerencia um `Arc<Mutex<Vec<DroneAereo>>>`.
3. Implementar um sistema de Threads onde cada drone atualiza sua própria altitude a cada segundo.
4. Criar um menu interativo para o usuário:
    - Adicionar novo drone ao espaço aéreo.
    - Listar todos os drones e suas altitudes atuais.
    - Aplicar um "fator de segurança" (calibração) que altera a altitude de todos os drones simultaneamente.
5. Garantir o encerramento seguro do sistema.

---

## ⚠️ Análise de Falha Crítica (Engenharia de Confiabilidade)

Em sistemas de tráfego aéreo, a concorrência mal gerenciada pode ser fatal. Analisamos os riscos:

1.  **Riscos de Race Conditions:** Sem o uso de `Mutex`, se duas threads (ex: a de simulação e a de calibração do usuário) tentassem alterar a altitude de um drone ao mesmo tempo, poderíamos ter uma "escrita perdida" ou, pior, uma corrupção de memória onde o drone assume uma altitude impossível (NaN ou Infinity), fazendo o sistema de controle colapsar.
2.  **Transactional Inconsistency:** Ao aplicar uma "Calibração de Emergência" em toda a frota, a operação deve ser atômica. Se o `Mutex` for liberado no meio do loop de calibração, metade da frota pode receber o novo comando enquanto a outra metade permanece em rota de colisão. O Rust garante que o lock do `Mutex` protege todo o escopo do vetor.
3.  **Buffer Overflows em Sockets:** Embora este desafio foque em threads locais, a expansão para rede exigiria o envio de structs `DroneAereo` via Sockets. O uso de serializadores seguros (como `serde`) no Rust impede que pacotes malformados estourem o buffer de recepção da torre, uma falha clássica que permitia a derrubada de sistemas de radar legados.
