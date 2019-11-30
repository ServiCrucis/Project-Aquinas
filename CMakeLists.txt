cmake_minimum_required(VERSION 3.0)
project(Modulus)
set(CMAKE_MODULE_PATH ./build/)
set(PROJECT_SOURCE_DIR ./src/)
set(CONFIGURE_INPUT ./build/configuration/)
# compiler flags
if (CYGWIN OR MINGW OR MSYS OR UNIX)
    # set C standard to C18 revision
    add_compile_options(-std=c18)
    # set warnings
    add_compile_options(-Wall -Wpedantic -Werror=pedantic -Wextra)
    # ubsan (undefined, address, pointer-compare, pointer-subtract, leak)
    #add_compile_options(-fsanitize=undefined -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_compile_options(-g3 -Og)
    else ()
        add_compile_options(-Ofast)
    endif ()
endif ()
# configuration files
configure_file(${CONFIGURE_INPUT}/project.h.in ${PROJECT_SOURCE_DIR}/include/project.h)
add_subdirectory(${PROJECT_SOURCE_DIR})