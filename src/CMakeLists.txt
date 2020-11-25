cmake_minimum_required(VERSION 3.17)
project(KASHYYYK_HOTEL C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(KASHYYYK_HOTEL main.c check_in.c check_out.c check_in.h check_out.c globals.c globals.h book_table.c book_table.h)
