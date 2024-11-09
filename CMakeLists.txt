cmake_minimum_required(VERSION 3.20)

project(the-hunt LANGUAGES C)

add_executable(the-hunt)

target_sources(${PROJECT_NAME}
    PRIVATE
    source/main.C
    source/engine/application.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>)
