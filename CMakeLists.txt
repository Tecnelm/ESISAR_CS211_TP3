cmake_minimum_required(VERSION 3.15)
project(ESISAR_CS211_TP3 C)

set(CMAKE_C_STANDARD 90)

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(ESISAR_CS211_TP3 main.c)