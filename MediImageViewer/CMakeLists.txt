cmake_minimum_required(VERSION 3.10)
# set the project name
project(MediImageViewer  C CXX)
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

add_executable(MediImageViewer MediImageViewer.cpp)
target_link_libraries(MediImageViewer PUBLIC ${VTK_LIBRARIES} MediImageProcessor 3DVolumeBuilder MRIReader ObjExporter)