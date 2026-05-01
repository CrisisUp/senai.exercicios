# Configuração de Build - Atividade Extra 21 (Mestre POO)
cmake_minimum_required(VERSION 3.10)
project(AtividadeExtra21)

set(CMAKE_CXX_STANDARD 17)

add_executable(atividade-extra21-agro 
    main.cpp 
    MaquinaAgricola.cpp
    MaquinaAgricola.h
)
