cmake_minimum_required(VERSION 3.10)
project(GoBoard)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(a main.cpp Board.cpp Node.cpp)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 and SDL2_ttf libraries
target_link_libraries(a ${SDL2_LIBRARIES})
