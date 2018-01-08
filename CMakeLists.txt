cmake_minimum_required(VERSION 3.8)
project(wd_library)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c container.c container.h)
add_executable(wd_library ${SOURCE_FILES})