cmake_minimum_required(VERSION 3.26)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c
        ST.c
        ST.h
        GRAPH.c
        GRAPH.h
)
