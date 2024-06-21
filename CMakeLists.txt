cmake_minimum_required(VERSION 3.10)
project(GoBoard)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(GoBoard
    src/main.cpp
    src/logic/board.cpp
    src/logic/node.cpp
    src/file/file_manager.cpp 
)

# Include directories
target_include_directories(GoBoard PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/logic
    ${PROJECT_SOURCE_DIR}/src/file
)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(GoBoard ${SDL2_LIBRARIES})
