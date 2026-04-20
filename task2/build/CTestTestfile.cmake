# CMake generated Testfile for 
# Source directory: /Users/konradkurzak/DIRS/novomatic/task2
# Build directory: /Users/konradkurzak/DIRS/novomatic/task2/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Task2Tests "/Users/konradkurzak/DIRS/novomatic/task2/build/Task2Tests")
set_tests_properties(Task2Tests PROPERTIES  _BACKTRACE_TRIPLES "/Users/konradkurzak/DIRS/novomatic/task2/CMakeLists.txt;58;add_test;/Users/konradkurzak/DIRS/novomatic/task2/CMakeLists.txt;0;")
subdirs("_deps/nlohmann_json-build")
subdirs("_deps/googletest-build")
subdirs("_deps/glfw-build")
