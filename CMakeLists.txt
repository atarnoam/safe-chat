cmake_minimum_required(VERSION 3.9)
project(aes C)

set(CMAKE_C_STANDARD 99)

include_directories(include debug)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I -Wall -Wextra")

add_executable(aes src/main.c src/gf_operations.c include/gf_operations.h src/key_schedule.c include/key_schedule.h
        src/cypher.c include/cypher.h debug/print_debug.c debug/print_debug.h src/inverse.c include/inverse.h src/cbc.c include/cbc.h)