cmake_minimum_required(VERSION 3.10)
project(GoBoard)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(GoBoard
    src/main.cpp
    src/logic/board.cpp
    src/logic/node.cpp
    src/ui/SDLRenderer.cpp  # Add SDLRenderer.cpp here
    src/file/File_manager.cpp  # Add File_manager.cpp here
)

target_include_directories(GoBoard PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/logic
    ${PROJECT_SOURCE_DIR}/src/rendering  # Adjust if SDLRenderer.h is in a different directory
    ${PROJECT_SOURCE_DIR}/src/file_management  # Adjust if File_manager.h is in a different directory
)


# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(GoBoard ${SDL2_LIBRARIES})
