cmake_minimum_required(VERSION 3.17)
project(KASHYYYK_HOTEL C)

set(CMAKE_C_STANDARD 99)

add_executable(KASHYYYK_HOTEL main.c check_in.c check_out.c check_in.h check_out.c globals.c globals.h)

#set(CMAKE_EXE_LINKER_FLAGS  "/FORCE")
