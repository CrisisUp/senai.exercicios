# Configuração de Build - Atividade Extra 20 (Elite)
cmake_minimum_required(VERSION 3.10)
project(AtividadeExtra20)

set(CMAKE_CXX_STANDARD 17)

add_executable(atividade-extra20-banco 
    main.cpp 
    ContaBancaria.cpp
    ContaBancaria.h
)
