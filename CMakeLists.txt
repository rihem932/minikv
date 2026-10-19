cmake_minimum_required(VERSION 3.16)
project(minikv CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minikv src/main.cpp src/kvstore.cpp)
target_compile_options(minikv PRIVATE -Wall -Wextra)
