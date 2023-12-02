cmake_minimum_required(VERSION 3.26)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c
        equipArray.h
        equipArray.c
        inv.h
        inv.c
        pgList.h
        pgList.c
        pg.h
        pg.c
        invArray.h
        invArray.c

)
