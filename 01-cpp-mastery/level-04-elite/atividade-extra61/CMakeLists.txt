cmake_minimum_required(VERSION 3.10)
project(Atividade61_LockFree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ativ61_lockfree atividade-extra61-lockfree.cpp)

find_package(Threads REQUIRED)
target_link_libraries(ativ61_lockfree PRIVATE Threads::Threads)
