/**
 * @file outputs.tf
 * @brief Exportação de dados da infraestrutura para o ecossistema Nexus.
 */

output "vpc_id" {
  description = "ID da VPC Global do Nexus"
  value       = aws_vpc.nexus_vpc.id
}

output "public_subnet_id" {
  description = "ID da Subnet Pública (Drones/Gateway)"
  value       = aws_subnet.public_subnet.id
}

output "private_subnet_id" {
  description = "ID da Subnet Privada (Vault)"
  value       = aws_subnet.private_subnet.id
}

output "vpc_cidr_block" {
  description = "Range de IPs da VPC"
  value       = aws_vpc.nexus_vpc.cidr_block
}
