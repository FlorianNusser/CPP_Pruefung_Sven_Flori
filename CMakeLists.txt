cmake_minimum_required(VERSION 3.11)
project(FaceDetectionStarter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV directories
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(FaceDetectionStarter
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/shape.cpp
    src/gui.cpp
    src/dodgeTheBalls.cpp
    src/ball.cpp
    src/drawShape.cpp
    src/menu.cpp
    src/gamemode.cpp
    src/color.cpp
)
target_link_libraries(FaceDetectionStarter ${OpenCV_LIBS})

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")


