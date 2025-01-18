cmake_minimum_required(VERSION 3.10)

# set the project name
project(InputProcessor  C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(InputProcessor SHARED InputProcessor.cpp)
target_link_libraries(InputProcessor  PRIVATE nlohmann_json::nlohmann_json)
add_executable(InputTester test.cpp)
target_link_libraries(InputTester PUBLIC  InputProcessor nlohmann_json::nlohmann_json)
