cmake_minimum_required(VERSION 3.10)
project(SenaiExercicios CXX)

# Configurações do Compilador (C++17 e Warnings)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags de Compilação Didáticas (Cores e Erros)
add_compile_options(-Wall -Wextra -g -fcolor-diagnostics -fansi-escape-codes)

# --- SISTEMA DE GESTÃO MODULAR (Modern CMake) ---

# Em vez de varrer tudo automaticamente com GLOB, usamos add_subdirectory 
# para os módulos principais. Isso permite controle total de dependências.

# 1. Trilha de Evolução de Legado (Nova)
add_subdirectory(repositorio-extra/Evolucao-Legado)

# 2. Compatibilidade com Exercícios Antigos
include(LegacyExercises.cmake)

# 3. Utilitários Globais
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gerador-pdf.cpp")
    add_executable(gerador-pdf gerador-pdf.cpp)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gerador-html.cpp")
    add_executable(gerador-html gerador-html.cpp)
endif()

# NOTA: As atividades antigas podem ser migradas gradualmente 
# para este novo formato adicionando 'add_subdirectory' ou mantendo
# um script de compatibilidade se necessário.
