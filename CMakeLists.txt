cmake_minimum_required(VERSION 3.22)
project(SnakeClone)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(snake_clone ${SOURCES})

target_link_libraries(snake_clone
        raylib
        GL
        m
        pthread
        dl
        rt
        X11
)

target_compile_options(snake_clone PRIVATE
        -Wall
        -Wno-missing-braces
        -s
        -O1
        -D_DEFAULT_SOURCE
        -DPLATFORM_DESKTOP
)