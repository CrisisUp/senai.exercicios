-- ==============================================================================
-- ATIVIDADE 30: CHECKPOINTS EM TRANSAÇÕES (SAVEPOINTS)
-- OBJETIVO: Gerenciar falhas parciais em processos de manutenção longos.
-- ==============================================================================
-- 1. Setup da Tabela de Manutenção
CREATE TABLE IF NOT EXISTS manutencao_progresso (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    etapa TEXT NOT NULL,
    status TEXT NOT NULL
);
DELETE FROM manutencao_progresso;
-- 2. INÍCIO DO PROCESSO COMPLEXO
BEGIN TRANSACTION;
-- ETAPA 1: Limpeza Física
INSERT INTO manutencao_progresso (drone_id, etapa, status)
VALUES ('DRONE-777', '1. Limpeza Física', 'CONCLUÍDO');
-- Criamos o primeiro CHECKPOINT
SAVEPOINT sp_limpeza;
-- ETAPA 2: Calibragem de Sensores
INSERT INTO manutencao_progresso (drone_id, etapa, status)
VALUES (
        'DRONE-777',
        '2. Calibragem de Sensores',
        'CONCLUÍDO'
    );
-- Criamos o segundo CHECKPOINT
SAVEPOINT sp_calibragem;
-- ETAPA 3: Atualização de Firmware (VAI FALHAR!)
INSERT INTO manutencao_progresso (drone_id, etapa, status)
VALUES (
        'DRONE-777',
        '3. Firmware v4.0',
        'FALHA CRÍTICA - ARQUIVO CORROMPIDO'
    );
-- 3. O PULO DO GATO: VOLTAR NO TEMPO PARCIALMENTE
-- Percebemos que o Firmware deu erro. Não queremos perder a Limpeza nem a Calibragem.
-- Voltamos para o ponto exato após a calibragem.
ROLLBACK TO sp_calibragem;
-- 4. TENTATIVA DE RECUPERAÇÃO
-- Vamos tentar instalar uma versão estável em vez da v4.0
INSERT INTO manutencao_progresso (drone_id, etapa, status)
VALUES (
        'DRONE-777',
        '3. Firmware v3.9 (Stable)',
        'CONCLUÍDO'
    );
-- 5. FINALIZAÇÃO DO TRABALHO
COMMIT;
-- 6. CONSULTA DE PROVA
-- Note que o registro da v4.0 (que falhou) SUMIU, mas as etapas 1 e 2 foram PRESERVADAS.
SELECT *
FROM manutencao_progresso;
/* 
 ===============================================================
 RESUMO TEÓRICO: SAVEPOINTS
 ===============================================================
 
 1. ALÉM DO COMMIT/ROLLBACK: 
 - SAVEPOINTs permitem que você erre no final de um script sem 
 ter que rodar os 50 comandos iniciais de novo.
 
 2. RELEASE vs COMMIT: 
 - 'RELEASE nome' apenas remove o checkpoint da memória (ele 
 não salva no HD, quem faz isso é o COMMIT final).
 
 3. USOS REAIS: 
 - Processamento de faturas em lote. Se a fatura 99 der erro, 
 você dá ROLLBACK para a 98 e continua para a 100, sem 
 perder as primeiras 98 que deram certo.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com a complexidade do mundo real, onde 
 nem tudo é "binário" (certo ou errado), mas sim uma sequência 
 de estados que podem ser recuperados.
 ===============================================================
 */