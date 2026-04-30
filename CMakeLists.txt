cmake_minimum_required(VERSION 3.10)
project(SenaiExercicios CXX)

# Configurações do Compilador (C++17 e Warnings)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags de Compilação Didáticas (Cores e Erros)
add_compile_options(-Wall -Wextra -g -fcolor-diagnostics -fansi-escape-codes)

# --- SISTEMA DE GESTÃO MODULAR (Modern CMake) ---

# Integração com Vcpkg (Gerenciador de Pacotes)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json")
    message(STATUS "Vcpkg manifest detected. Ensure -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake is set.")
endif()

# 1. Atividades e Projetos (Migrados do GLOB para Alvos Explícitos)
add_subdirectory(01-cpp-mastery)

# 2. Infraestrutura de Testes
find_package(GTest CONFIG QUIET)
if(GTEST_FOUND)
    add_subdirectory(core-infrastructure/tests)
else()
    message(STATUS "GTest não encontrado. Testes unitários C++ ignorados.")
endif()

# 3. Infraestrutura de Documentação (SRE Mindset)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_HAVE_DOT YES) # Habilita diagramas Graphviz
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
    
    doxygen_add_docs(docs
        "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Gerando documentação técnica automatizada (Doxygen)..."
    )
else()
    message(WARNING "Doxygen não encontrado. Documentação automática desativada.")
endif()

# 4. Utilitários Globais
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/core-infrastructure/tools/gerador-pdf.cpp")
    add_executable(gerador-pdf core-infrastructure/tools/gerador-pdf.cpp)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/core-infrastructure/tools/gerador-html.cpp")
    add_executable(gerador-html core-infrastructure/tools/gerador-html.cpp)
endif()

# NOTA: As atividades antigas podem ser migradas gradualmente 
# para este novo formato adicionando 'add_subdirectory' ou mantendo
# um script de compatibilidade se necessário.
