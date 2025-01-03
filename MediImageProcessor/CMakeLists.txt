cmake_minimum_required(VERSION 3.10)
# set the project name
project(MediImageProcessor  C CXX)
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
  message(FATAL_ERROR "ObjExporter: Unable to find the VTK build folder.")
endif()

add_library(MediImageProcessor SHARED  MediImageProcessor.cpp)
target_link_libraries(MediImageProcessor PUBLIC ${VTK_LIBRARIES} 3DVolumeBuilder MRIReader ObjExporter)