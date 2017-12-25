cmake_minimum_required(VERSION 3.9)
project(aes C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99")

add_executable(aes main.c bytes.c bytes.h)