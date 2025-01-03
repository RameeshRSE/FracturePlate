cmake_minimum_required(VERSION 3.10)

# set the project name
project(MRIReader  C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Threads REQUIRED)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  IOImage
  InteractionImage
  InteractionStyle
  IOExport
  IOImport
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "ReadDICOM: Unable to find the VTK build folder.")
endif()

add_library(MRIReader SHARED MRIReader.cpp)
target_link_libraries(MRIReader PUBLIC ${VTK_LIBRARIES})