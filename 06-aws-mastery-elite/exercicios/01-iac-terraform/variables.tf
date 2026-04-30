/**
 * @file variables.tf
 * @brief Parametrização da Infraestrutura Industrial.
 */

variable "aws_region" {
  description = "Região da AWS para o deploy do Nexus"
  type        = string
  default     = "us-east-1"
}

variable "environment" {
  description = "Ambiente (dev, staging, prod)"
  type        = string
  default     = "dev"
}

variable "vpc_cidr" {
  description = "Bloco CIDR para a VPC"
  type        = string
  default     = "10.0.0.0/16"
}
