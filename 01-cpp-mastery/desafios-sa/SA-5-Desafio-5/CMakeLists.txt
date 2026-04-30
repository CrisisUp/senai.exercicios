cmake_minimum_required(VERSION 3.10)
project(SA5_MaestroMemoria)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sa5_maestro SA-5-Maestro-Memoria.cpp)

# Links para threads (necessário em sistemas Linux/Unix)
find_package(Threads REQUIRED)
target_link_libraries(sa5_maestro PRIVATE Threads::Threads)
