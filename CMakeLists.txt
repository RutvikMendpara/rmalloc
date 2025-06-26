cmake_minimum_required(VERSION 3.28)
project(rmalloc LANGUAGES CXX)

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable C++20 Modules scan
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Force Clang
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# rmalloc static lib
add_library(rmalloc STATIC src/rmalloc.cpp)

# Expose include/ as public header path
target_include_directories(rmalloc PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Strict warnings
target_compile_options(rmalloc PRIVATE
        -Wall -Wextra -Werror -Wshadow -pedantic
)

# Unit test
add_executable(rmalloc_test test/main.cpp)
target_link_libraries(rmalloc_test PRIVATE rmalloc)
