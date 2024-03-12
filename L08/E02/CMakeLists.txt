cmake_minimum_required(VERSION 3.26)
project(E02 C)

set(CMAKE_C_STANDARD 99)

add_executable(E02 main.c
        graph.c
        graph.h
        st.c
        st.h
)
