cmake_minimum_required(VERSION 3.10)
project("Task1")
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

set(SOURCES
    src/main.cpp
    client/Client.cpp
    client/CoinMachine.cpp
    server/Server.cpp
)

add_executable(Task1 ${SOURCES})
target_include_directories(Task1 PRIVATE "headers" "src" "client" "server")

enable_testing()
add_executable(Task1Tests 
    tests/tests.cpp
    client/CoinMachine.cpp
    server/Server.cpp
)
target_include_directories(Task1Tests PRIVATE "headers" "src" "client" "server")
target_link_libraries(Task1Tests gtest_main)
add_test(NAME Task1Tests COMMAND Task1Tests)
