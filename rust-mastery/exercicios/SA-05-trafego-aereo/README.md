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
