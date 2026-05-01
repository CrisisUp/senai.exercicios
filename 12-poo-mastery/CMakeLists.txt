cmake_minimum_required(VERSION 3.10)
project(POOMasteryElite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclusão dos níveis de exercícios
add_subdirectory(exercicios/level-01-iniciado)
add_subdirectory(exercicios/level-02-arquiteto)
add_subdirectory(exercicios/level-03-mestre-poo)
add_subdirectory(exercicios/level-04-elite)

# Inclusão dos labs
add_subdirectory(labs/drone-factory)
