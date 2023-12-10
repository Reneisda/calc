cmake_minimum_required(VERSION 3.26)
project(calc C)

set(CMAKE_C_STANDARD 23)

add_executable(calc main.c
        calculations.c
        calculations.h
        callfuncs.c
        callfuncs.h)
target_link_libraries(calc m)
target_link_libraries(calc gmp)

