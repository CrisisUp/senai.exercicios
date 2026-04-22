# 🗄️ Atividade 28: Manutenção e Limpeza (VACUUM e Fragmentação)

## 🎯 Estudo de Caso

Após meses de logs de auditoria, segurança e telemetria, o banco de dados da "SkyCargo" está gigante. O problema é que deletamos muitos dados antigos, mas o tamanho do arquivo no HD continua o mesmo! O arquivo está "esburacado" (fragmentado). Precisamos reorganizar as páginas do banco para recuperar espaço e ganhar velocidade de leitura.

## 🛠️ Necessidade Técnica

* **VACUUM:** O comando que reconstrói o banco de dados do zero, eliminando espaços vazios deixados por registros deletados.
* **Auto-Vacuum:** Uma configuração que automatiza esse processo (embora tenha custo de CPU).
* **ANALYZE:** Atualiza as estatísticas internas para que o planejador de queries escolha o melhor índice.

## 📋 Requisitos

1. Criar uma tabela pesada `logs_temporarios`.
2. Inserir 1000 linhas de dados.
3. Verificar o número de páginas do banco.
4. Deletar todos os dados.
5. Executar o **VACUUM** e notar a diferença na estrutura do arquivo.

## ⚠️ Análise de Falha Crítica

*   **Riscos de Performance Locks:** O comando `VACUUM` requer um bloqueio exclusivo (exclusive lock) em todo o banco de dados. Durante sua execução, nenhuma outra transação de leitura ou escrita pode ser realizada, o que pode causar downtime em sistemas 24/7.
*   **Vacuum Latency:** A latência do `VACUUM` é proporcional ao tamanho total do banco de dados, não apenas ao volume de dados deletados. Em bancos multi-terabyte, esse processo pode levar horas ou dias.
*   **Heap Bloat:** O acúmulo de espaço não recuperado ("dead tuples" em outros bancos ou páginas vazias no SQLite) degrada o cache de memória, pois o banco acaba carregando páginas vazias para o buffer pool, reduzindo a eficiência de I/O.
*   **Transaction Log Overflow:** O `VACUUM` cria um arquivo temporário que pode dobrar o uso de espaço em disco durante o processo. Se o disco estiver próximo do limite, o comando falhará e poderá corromper o log de transações ou impedir a recuperação do sistema.
