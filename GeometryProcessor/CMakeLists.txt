cmake_minimum_required(VERSION 3.10)
# set the project name
project(GeometryProcessor  C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(LIBIGL REQUIRED QUIET)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersCore
  FiltersModeling
  FiltersSources
  InteractionImage
  InteractionStyle
)

add_library(GeometryProcessor SHARED GeometryCore.cpp
                                     ScrewGeometryBuilder.cpp
                                     FracturePlateGeometryBuilder.cpp
                                     HoleGeometryBuilder.cpp)

target_link_libraries(GeometryProcessor PUBLIC ${VTK_LIBRARIES} GeometricAlgo)
add_executable(FracturePlateViewer FracturePlateViewer.cpp)
target_link_libraries(FracturePlateViewer PUBLIC   InputProcessor GeometryProcessor  GeometricAlgo)
add_executable(BooleanTest testBoolean.cpp)
target_link_libraries(BooleanTest  PUBLIC ${VTK_LIBRARIES})


