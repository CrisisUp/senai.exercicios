/**
 * @file vault.tf
 * @brief Implementação de Cofre de Segurança com Criptografia de Hardware.
 */

# 1. Criação da Chave Mestra KMS (Hardware Security Module)
resource "aws_kms_key" "nexus_key" {
  description             = "Chave Mestra de Criptografia do Nexus de Telemetria"
  deletion_window_in_days = 7
  enable_key_rotation     = true # Boa prática industrial

  tags = {
    Name = "Nexus-Master-Key"
  }
}

# 2. Alias amigável para a chave
resource "aws_kms_alias" "nexus_key_alias" {
  name          = "alias/nexus-telemetria-key"
  target_key_id = aws_kms_key.nexus_key.key_id
}

# 3. Criação do Cofre no Secrets Manager
resource "aws_secretsmanager_secret" "db_credentials" {
  name       = "Nexus/SQLVault/Credentials"
  kms_key_id = aws_kms_key.nexus_key.arn # Vincula o cofre à nossa chave KMS

  description = "Credenciais críticas para o SQL Vault da LogiSpeed"

  tags = {
    SecurityLevel = "ELITE"
  }
}

# 4. Versão inicial do segredo (O valor real nunca deve estar no código, apenas o molde)
resource "aws_secretsmanager_secret_version" "initial_version" {
  secret_id     = aws_secretsmanager_secret.db_credentials.id
  secret_string = jsonencode({
    username = "admin_nexus"
    password = "CHANGE_ME_IN_AWS_CONSOLE" # O engenheiro altera manualmente ou via CLI
    port     = 5432
  })
}
