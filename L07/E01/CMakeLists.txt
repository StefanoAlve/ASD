cmake_minimum_required(VERSION 3.26)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c
        equipArray.c
        inv.c
        invArray.c
        pg.c
        pgList.c
        main.c)
