cmake_minimum_required(VERSION 3.10)
# set the project name
project(ObjExporter  C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(VTK REQUIRED)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "ObjExporter: Unable to find the VTK build folder.")
endif()

add_library(ObjExporter SHARED ObjExporter.cpp)
target_link_libraries(ObjExporter PUBLIC ${VTK_LIBRARIES})