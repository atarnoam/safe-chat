cmake_minimum_required(VERSION 3.9)
project(aes C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I -Wall -Wextra -std=c99")

add_executable(aes src/main.c src/bytes.c include/bytes.h src/gf_operations.c include/gf_operations.h)