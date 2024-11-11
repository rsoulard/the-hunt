cmake_minimum_required(VERSION 3.20)

project(the-hunt LANGUAGES C)

add_executable(the-hunt)

target_sources(${PROJECT_NAME}
    PRIVATE
    source/main.C
    source/algorithms/hash.c
    source/datastructures/dictionary.c
    source/engine/application.c
    source/engine/applicationbuilder.c
    source/engine/framebuffer.c
    source/engine/servicecollection.C
    source/engine/serviceprovider.c
    source/engine/softwarerenderer.c
    source/engine/window.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>)
