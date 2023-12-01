cmake_minimum_required(VERSION 3.26)
project(ESE6E3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ESE6E3 main.c
        inv.h
        pg.h
        inv.c
        pg.c)
