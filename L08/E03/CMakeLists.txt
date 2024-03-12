cmake_minimum_required(VERSION 3.26)
project(E03 C)

set(CMAKE_C_STANDARD 99)

add_executable(E03 main.c
        datetime.h
        title.h
        titleList.c
        titleList.h
        dailyquotBST.c
        dailyquotBST.h
        title.c
        datetime.c)
