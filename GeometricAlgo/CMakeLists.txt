cmake_minimum_required(VERSION 3.10)

# set the project name
project(GeometricAlgo  C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(GeometricAlgo SHARED PoissonDiskSampling.cpp)
