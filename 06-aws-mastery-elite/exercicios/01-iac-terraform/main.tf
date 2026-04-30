/**
 * @file main.tf
 * @brief Orquestração da Infraestrutura Nexus via Terraform.
 * @author Engenheiro de Elite
 */

terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

provider "aws" {
  region = var.aws_region
}

# 1. Criação da VPC (Rede Privada do Nexus)
resource "aws_vpc" "nexus_vpc" {
  cidr_block           = "10.0.0.0/16"
  enable_dns_hostnames = true
  enable_dns_support   = true

  tags = {
    Name        = "Nexus-VPC-Global"
    Environment = var.environment
    Project     = "LogiSpeed-SkyCargo"
  }
}

# 2. Subnet Pública (Onde os Drones/API se conectam)
resource "aws_subnet" "public_subnet" {
  vpc_id                  = aws_vpc.nexus_vpc.id
  cidr_block              = "10.0.1.0/24"
  map_public_ip_on_launch = true
  availability_zone       = "${var.aws_region}a"

  tags = {
    Name = "Nexus-Public-Layer"
  }
}

# 3. Subnet Privada (Onde o SQL Vault reside - Blindada da Internet)
resource "aws_subnet" "private_subnet" {
  vpc_id            = aws_vpc.nexus_vpc.id
  cidr_block        = "10.0.2.0/24"
  availability_zone = "${var.aws_region}a"

  tags = {
    Name = "Nexus-Private-Vault"
  }
}

# 4. Gateway de Internet (Permite saída para a rede pública)
resource "aws_internet_gateway" "nexus_igw" {
  vpc_id = aws_vpc.nexus_vpc.id

  tags = {
    Name = "Nexus-Gateway"
  }
}
