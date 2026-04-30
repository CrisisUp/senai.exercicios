cmake_minimum_required(VERSION 3.10)
project(Atividade63_ObjectPool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ativ63_pool atividade-extra63-pool.cpp)

find_package(Threads REQUIRED)
target_link_libraries(ativ63_pool PRIVATE Threads::Threads)
