/**
 * @file queries.sql
 * @brief Integrador de Dados Corporativos com ETL e Analítica Pivotada.
 * @details Pipeline de dados para importação de CSV, resolução de conflitos de seriais
 *          e geração de relatórios financeiros de alta precisão.
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - Security Views: Uso de Views para expor dashboards financeiros sem permitir acesso direto às tabelas de carga.
 * - Analytics Cost: Pivoteamento via SUM(CASE) é eficiente em SQLite, mas exige índices em (categoria, mes) 
 *   para evitar varreduras completas em grandes frotas.
 * - Stress Resilience: A estratégia INSERT OR REPLACE garante a convergência dos dados mesmo em cargas 
 *   repetitivas ou arquivos com sobreposição de informações.
 */

-- ==============================================================================
-- 1. ARQUITETURA DO SISTEMA (DDL)
-- ==============================================================================
CREATE TABLE IF NOT EXISTS faturamento_frota (
    serial TEXT NOT NULL,
    mes TEXT NOT NULL,
    categoria TEXT NOT NULL,
    lucro_cents INTEGER NOT NULL, -- Guardião Financeiro: Lucro em centavos
    PRIMARY KEY (serial, mes)     -- Chave Composta para detecção de conflitos
);

-- ==============================================================================
-- 2. PIPELINE ETL (Simulado)
-- ==============================================================================
-- Nota: Na prática, os dados seriam carregados via comandos .import em tabela temp
-- Aqui simulamos a carga final com resolução de conflitos.

INSERT OR REPLACE INTO faturamento_frota (serial, mes, categoria, lucro_cents)
VALUES 
    ('X-100', 'Jan', 'Resgate', 500000), -- R$ 5.000,00
    ('X-101', 'Jan', 'Carga', 750050),   -- R$ 7.500,50
    ('X-100', 'Fev', 'Resgate', 480000),
    ('X-102', 'Fev', 'Carga', 900000);

-- ==============================================================================
-- 3. CONSULTA ANALÍTICA (PIVOTEAMENTO)
-- ==============================================================================
-- Dashboard final formatado para a diretoria.
CREATE VIEW IF NOT EXISTS v_dashboard_mensal AS
SELECT 
    categoria,
    ROUND(SUM(CASE WHEN mes = 'Jan' THEN lucro_cents ELSE 0 END) / 100.0, 2) AS "Janeiro (R$)",
    ROUND(SUM(CASE WHEN mes = 'Fev' THEN lucro_cents ELSE 0 END) / 100.0, 2) AS "Fevereiro (R$)",
    ROUND(SUM(lucro_cents) / 100.0, 2) AS "Total Acumulado (R$)"
FROM faturamento_frota
GROUP BY categoria;

-- Execução do Dashboard
SELECT * FROM v_dashboard_mensal;

-- ==============================================================================
-- RESUMO TEÓRICO
-- ==============================================================================
/*
1. ETL (Extract, Transform, Load): Processo de movimentação de dados de fontes 
   externas para um banco estruturado, essencial para BI.
2. UPSERT (INSERT OR REPLACE): Padrão que simplifica a lógica de aplicação, 
   permitindo que novos dados atualizem registros existentes automaticamente.
3. DATA PIVOTING: Fundamental para transformar séries temporais em tabelas 
   comparativas, facilitando a análise de tendências sazonais.
4. INTEGRIDADE MONETÁRIA: Armazenar valores como inteiros elimina a imprecisão 
   do ponto flutuante em totalizações e fechamentos financeiros.
*/

-- ==============================================================================
-- ASSUNTOS CORRELATOS
-- ==============================================================================
/*
- Data Cleaning e Deduplicação de registros.
- Normalização vs Desnormalização para Performance.
- Ferramentas de Orquestração de Dados (Airflow, DBT).
- Otimização de Cláusulas CASE em grandes volumes.
*/
