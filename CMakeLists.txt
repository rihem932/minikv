cmake_minimum_required(VERSION 3.16)
project(minikv CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The database itself, as a library (used by the program and by the tests)
add_library(minikv_core src/kvstore.cpp src/parser.cpp)
target_include_directories(minikv_core PUBLIC src)
target_compile_options(minikv_core PRIVATE -Wall -Wextra)

# The interactive program
add_executable(minikv src/main.cpp)
target_link_libraries(minikv PRIVATE minikv_core)
target_compile_options(minikv PRIVATE -Wall -Wextra)

# Unit tests (Catch2 is downloaded automatically the first time)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(minikv_tests tests/test_kvstore.cpp tests/test_parser.cpp tests/test_persistence.cpp)
target_link_libraries(minikv_tests PRIVATE minikv_core Catch2::Catch2WithMain)
target_compile_options(minikv_tests PRIVATE -Wall -Wextra)
add_test(NAME minikv_tests COMMAND minikv_tests)
