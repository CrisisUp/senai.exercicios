# Configuração de Build - Atividade Extra 22 (Mestre POO)
cmake_minimum_required(VERSION 3.10)
project(AtividadeExtra22)

set(CMAKE_CXX_STANDARD 17)

add_executable(atividade-extra22-aviacao 
    main.cpp 
    Aeronave.cpp
    Aeronave.h
)
