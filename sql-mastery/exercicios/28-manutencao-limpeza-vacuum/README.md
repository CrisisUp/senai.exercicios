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
