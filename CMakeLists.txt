set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
cmake_minimum_required(VERSION 3.28)
project(rmalloc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force Clang
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

add_library(rmalloc STATIC src/rmalloc.cpp)

target_include_directories(rmalloc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_options(rmalloc PRIVATE
    -Wall -Wextra -Werror -Wshadow -pedantic
)

add_executable(rmalloc_test test/main.cpp)
target_link_libraries(rmalloc_test PRIVATE rmalloc)
