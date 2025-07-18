# CPP_Pruefung_Sven_Flori

## Project Description

This project is a C++ application that implements two game modes: **DodgeTheBalls** and **CatchTheSquares**. The goal of the project is to create an efficient and extensible architecture that allows for easy addition of new game modes while keeping the existing logic clean and organized.

The application uses **OpenCV** for face detection and graphical rendering of game elements. Players can choose between the two modes, and their results are saved and displayed in a leaderboard.


## Extras

Initially, the `game.cpp` file contained over 200 lines of code, with the logic for both game modes implemented in parallel using extensive `if-else` statements. To improve maintainability and scalability, we decided to abstract the architecture. By introducing a **GameModeInterface** and leveraging **runtime polymorphism**, we were able to separate the logic of the game modes into individual files, making the codebase cleaner and more efficient. This also simplifies the process of adding new game modes.


## Features

### Game Modes
1. **DodgeTheBalls**:
   - Players must dodge balls that randomly appear on the screen.
   - The color of the balls is random (Red, Green, Blue).
   - The score is calculated based on the number of frames survived.

2. **CatchTheSquares**:
   - Players must catch squares that appear on the screen.
   - Squares have a fixed color (Green).
   - The score is calculated based on the number of squares caught.

### Leaderboard
- Results are saved in separate files for each game mode:
  - `leaderboardDodgeTheBalls.txt`
  - `leaderboardCatchTheSquares.txt`
- Players can view and compare their results.

### Face Detection
- OpenCV is used to detect faces and determine the player's position.


## Key Features of the Architecture

### Runtime Polymorphism
The `game.cpp` file uses **runtime polymorphism** to automatically access the correct game mode functions. This is achieved by using a **GameModeInterface**, which acts as an abstraction layer for all game modes. Depending on the selected game mode, the appropriate implementation is invoked at runtime, ensuring clean and modular code.

### GameModeInterface
The **GameModeInterface** is an abstract class that defines the core functions required for all game modes:
- `initialize()`
- `spawnShape()`
- `update()`
- `handleCollisions()`
- `draw()`
- `getScore()`

These functions are exclusively implemented in the respective game mode classes (`DodgeTheBallsMode` and `CatchTheSquaresMode`), allowing each mode to have its own specific logic while adhering to a common interface.


### Key Files

#### `game.cpp`
The central file that manages the game modes and implements the main game logic. It uses the **GameModeInterface** to call the specific logic of the game modes.

#### `gameModeInterface.hpp`
An interface that defines the basic functions for all game modes:
- `initialize()`
- `spawnShape()`
- `update()`
- `handleCollisions()`
- `draw()`
- `getScore()`

#### `dodgeTheBallsMode.cpp` and `catchTheSquaresMode.cpp`
Implementations of the two game modes. Both inherit from **GameModeInterface** and implement the specific logic for their mode.

#### `gui.cpp`
Responsible for graphical rendering, including score display, game-over screen, and leaderboard.

#### `constants.hpp`
Contains global constants for the game, such as window size, colors, and spawn intervals for objects.

## 🛠 Installation

### Prerequisites

- **CMake**: For face detection and graphical rendering
- **MinGW Make**: Select the right Generator MinGW for Windows
- **OpenCV** (see `BuildOpenCV.md`): For the build system
- **GoogleTest** (headers + libraries in project)

---

### Build Steps

1. Clone the repo and install OpenCV
   Follow the instructions in `BuildOpenCV.md`.

2. Place GoogleTest under your project root

3. Create and enter a build directory
```bash
mkdir build
cd build
```

4. Configure with CMake
```bash
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
```
If CMake can't locate GoogleTest, supply explicit paths (set the right paths in "PATH_TO"):
```bash
cmake -G "MinGW Makefiles" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DGTEST_INCLUDE_DIR="PATH_TO/googletest/include" \
  -DGTEST_LIBRARY="PATH_TO/googleTest/build/lib/libgtest.a" \
  -DGTEST_MAIN_LIBRARY="PATH_TO/googleTest/build/lib/libgtest_main.a" ..
```
5. Build the project
```bash
cmake --build .
```

6. Run the executables
```bash
./FaceDetectionStartet.exe   # start the face-detection game
./GameTest.exe               # run unit tests
```