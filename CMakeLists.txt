cmake_minimum_required(VERSION 2.6)
project(libtstp)

add_executable(libtstp main.cpp)

install(TARGETS libtstp RUNTIME DESTINATION bin)
