cmake_minimum_required(VERSION 3.10)
project("Task2")
set(CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(Task2 ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.3.8.zip
)
FetchContent_MakeAvailable(glfw)
find_package(OpenGL REQUIRED)

FetchContent_Declare(
  imgui
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.zip
)
FetchContent_MakeAvailable(imgui)

file(GLOB IMGUI_SOURCES 
  ${imgui_SOURCE_DIR}/*.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_sources(Task2 PRIVATE ${IMGUI_SOURCES})
target_include_directories(Task2 PRIVATE 
  "src" "headers"
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends 
  ${glfw_SOURCE_DIR}/include
)

target_link_libraries(Task2 nlohmann_json::nlohmann_json glfw OpenGL::GL)

add_definitions(-DGL_SILENCE_DEPRECATION)

enable_testing()

add_executable(Task2Tests tests/tests.cpp src/Graph.cpp)
target_include_directories(Task2Tests PRIVATE "src" "headers" ${nlohmann_json_SOURCE_DIR}/include)
target_link_libraries(Task2Tests gtest_main nlohmann_json::nlohmann_json)
add_test(NAME Task2Tests COMMAND Task2Tests)