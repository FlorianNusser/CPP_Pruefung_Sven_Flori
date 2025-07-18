# CPP_Pruefung_Sven_Flori

## 🛠 Installation

### Prerequisites

- CMake (≥ 3.10)
- MinGW Make
- OpenCV (see `BuildOpenCV.md`)
- GoogleTest (headers + libraries in project)

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