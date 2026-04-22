# Script de Compatibilidade para Exercícios Antigos
# Este script mantém a lógica de descoberta automática para as pastas
# que ainda não foram migradas para o padrão Modern CMake.

function(discover_legacy_exercises folder_path)
    file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${folder_path} ${CMAKE_CURRENT_SOURCE_DIR}/${folder_path}/*)
    foreach(subdir ${SUBDIRS})
        set(full_path "${CMAKE_CURRENT_SOURCE_DIR}/${folder_path}/${subdir}")
        if(IS_DIRECTORY "${full_path}" AND NOT EXISTS "${full_path}/CMakeLists.txt")
            file(GLOB CPP_FILES "${full_path}/*.cpp")
            
            # Gerenciamento de Dependências Específicas (Legado)
            if("${subdir}" STREQUAL "atividade-extra51")
                list(APPEND CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/repositorio-extra/atividade-extra50/Monitoramento.cpp")
            endif()

            if("${subdir}" STREQUAL "SA-3-Desafio-3")
                list(APPEND CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/repositorio-extra/atividade-extra52/Medicao.cpp")
            endif()

            if(CPP_FILES)
                add_executable("${subdir}" ${CPP_FILES})
                # Organiza os executáveis em pastas na IDE (VS Code/Visual Studio)
                set_target_properties("${subdir}" PROPERTIES FOLDER "Legacy/${folder_path}")
            endif()
        endif()
    endforeach()
endfunction()

# Executa a descoberta
discover_legacy_exercises("repositorio")
discover_legacy_exercises("repositorio-extra")
