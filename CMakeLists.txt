cmake_minimum_required(VERSION 3.25)
project(skip_list C)

set(CMAKE_C_STANDARD 17)

add_executable(skip_list main.c src/skip_list.c src/skip_list.h)
