cmake_minimum_required(VERSION 2.8)

message("CMake now is working!")

# Project name
project(Coursework)

add_executable(dt_cmp headers/message.c headers/message.h headers/compress.c headers/compress.h headers/basic_structures.c headers/basic_structures.h main.c)
