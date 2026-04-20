cmake_minimum_required(VERSION 3.10)
project("Task3")
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "utils/*.cpp")
add_executable(Task3 ${SOURCES})
target_include_directories(Task3 PRIVATE "src" "headers" "utils")

# Download and build GTest automatically
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable CTest
enable_testing()

# Test executable - note: no main.cpp, only utils and the test file
add_executable(Task3Tests tests/tests.cpp utils/Utilities.cpp)
target_include_directories(Task3Tests PRIVATE "src" "headers" "utils")
target_link_libraries(Task3Tests gtest_main)
add_test(NAME Task3Tests COMMAND Task3Tests)