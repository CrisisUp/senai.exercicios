cmake_minimum_required(VERSION 3.10)
project(Atividade62_LockFree_SPSC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ativ62_spsc atividade-extra62-spsc.cpp)

find_package(Threads REQUIRED)
target_link_libraries(ativ62_spsc PRIVATE Threads::Threads)
