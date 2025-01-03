cmake_minimum_required(VERSION 3.10)
# set the project name
project(3DVolumeBuilder  C CXX)
SET(VTK_DIR "/Users/rameeshradhakrishnan/Documents/VTK-9.4.1/Build" CACHE PATH "VTK directory override" FORCE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Threads REQUIRED)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  IOImage
  InteractionImage
  InteractionStyle
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "3DVolumeBuilder: Unable to find the VTK build folder.")
endif()

add_library(3DVolumeBuilder SHARED MarchingCubeVolumeBuilder.cpp)
target_link_libraries(3DVolumeBuilder PUBLIC ${VTK_LIBRARIES})