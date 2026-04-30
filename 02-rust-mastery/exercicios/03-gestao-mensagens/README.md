# 🦀 Atividade 03: Gestão de Mensagens (Ownership / Propriedade)

## 🎯 Estudo de Caso
A transportadora "SkyCargo" está implementando um sistema de log para as mensagens enviadas pelos drones. Para garantir a máxima eficiência e evitar vazamentos de memória (comuns em C++), o Rust utiliza o conceito de **Ownership**. Precisamos de um sistema que processe as mensagens, decida quem é o "dono" daquela informação na memória e garanta que ela seja descartada no momento certo.

## 🛠️ Necessidade Técnica
O **Ownership** é o conceito mais importante do Rust e o que o diferencia de todas as outras linguagens:
*   **Cada valor tem um único dono.**
*   **Quando o dono sai de escopo, o valor é descartado (Drop).**
*   **Transferência (Move):** Ao passar uma string para uma função, você "entrega a posse". A variável original deixa de existir.
*   **Clonagem (Clone):** Se precisar de uma cópia independente na memória.

## 📋 Requisitos
1. Criar uma função `processar_log(msg: String)` que recebe a posse de uma mensagem e a exibe.
2. Demonstrar o erro de compilação ao tentar usar uma variável após o "Move".
3. Implementar uma função que retorna uma nova string para demonstrar a transferência de volta da propriedade.
### 4. Usar `String` (alocada na Heap) em vez de `&str` para evidenciar o gerenciamento de memória.

## 🛡️ Análise de Falha Crítica (Refatoração de Elite)

*   **Riscos de Panic:** Erros de alocação de memória no Heap podem causar panic se o sistema ficar sem recursos. Strings grandes sem limite de tamanho são um risco em sistemas embarcados.
*   **Use-after-move:** O compilador Rust bloqueia estaticamente qualquer tentativa de usar uma variável cuja posse foi transferida. Isso elimina bugs de ponteiros pendentes (dangling pointers).
*   **Borrow Checker Errors:** O uso de referências imutáveis (`&`) permite múltiplos leitores, mas impede a modificação simultânea, prevenindo condições de corrida (race conditions) em logs.
*   **Memory Overheads:** O uso excessivo de `.clone()` duplica dados na Heap, aumentando a pressão sobre o alocador e reduzindo a performance (Fantasma do CPU). O uso de referências é a solução preferencial.

