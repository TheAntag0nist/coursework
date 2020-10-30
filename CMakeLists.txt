cmake_minimum_required(VERSION 2.8)

message("CMake now is working!")

set (PROJECT dt_cmp)

# Project name
project(${PROJECT})


set (HEADERS 
	../headers/message.h
	../headers/compress.h
	../headers/basic_structures.h
	../headers/archive.h)
	
set (SOURCES 
	../headers/message.c
	../headers/compress.c
	../headers/basic_structures.c
	../headers/archive.c
	../main.c)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})
