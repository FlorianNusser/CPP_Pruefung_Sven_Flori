cmake_minimum_required(VERSION 3.11)
project(FaceDetectionStarter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

# Platform specific settings
if(WIN32)
    message("Compiling on WIN 32")
    add_definitions(-D_WIN32)
elseif(APPLE)
    message("Compiling on APPLE")
    add_definitions(-D__APPLE__)
elseif(UNIX)
    message("Compiling on LINUX")
    add_definitions(-D__linux__)
endif()

# Include OpenCV directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Main executable
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
    src/drawBall.cpp
    src/catchTheSquares.cpp
    src/square.cpp
    src/gameModeInterface.cpp
    src/dodgeTheBallsMode.cpp
    src/catchTheSquaresMode.cpp
)
target_link_libraries(FaceDetectionStarter ${OpenCV_LIBS})

# Test executable (only build when testing)
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()

    # Test executable (neuer Name: GameTests)
    add_executable(GameTests
        test/gameTest.cpp
        src/game.cpp
        src/player.cpp
        src/shape.cpp
        src/gui.cpp
        src/dodgeTheBalls.cpp
        src/ball.cpp
        src/menu.cpp
        src/gamemode.cpp
        src/color.cpp
        src/catchTheSquares.cpp
        src/square.cpp
        src/gameModeInterface.cpp
        src/dodgeTheBallsMode.cpp
        src/catchTheSquaresMode.cpp
        src/drawShape.cpp
        src/drawBall.cpp
    )
    target_include_directories(GameTests PRIVATE ${CMAKE_SOURCE_DIR}/inc)
    target_link_libraries(GameTests
        GTest::GTest
        GTest::Main
        ${OpenCV_LIBS}
    )

    # Add tests
    include(GoogleTest)
    gtest_discover_tests(GameTests)
endif()

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")


