

cmake_minimum_required(VERSION 3.10)
project(Mercenary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the executable
add_executable(code test.cpp Role.hpp)

# Set compiler options for better warnings and optimization
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

