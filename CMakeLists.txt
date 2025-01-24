cmake_minimum_required(VERSION 3.10)
# set the project name
project(MediImageProcessor  C CXX)
set(CMAKE_CXX_STANDARD 14)
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

add_subdirectory(3DVolumeBuilder)
add_subdirectory(MedicalImageReader)
add_subdirectory(OBJExporter)
add_subdirectory(MediImageProcessor)
add_subdirectory(MediImageViewer)
add_subdirectory(InputProcessor)
add_subdirectory(GeometryProcessor)
add_subdirectory(GeometricAlgo)