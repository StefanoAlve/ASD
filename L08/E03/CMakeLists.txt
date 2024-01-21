cmake_minimum_required(VERSION 3.26)
project(E03 C)

set(CMAKE_C_STANDARD 99)

add_executable(E03 main.c
        dataOra.c
        dataOra.h
        titolo.c
        titolo.h
        collezioneTitoli.c
        collezioneTitoli.h
        collezioneQuotazioni.c
        collezioneQuotazioni.h)
