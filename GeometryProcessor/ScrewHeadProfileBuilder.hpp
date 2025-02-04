
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vector>

#ifndef SCREW_HEAD_PROFILE_BUILDER_HPP
#define SCREW_HEAD_PROFILE_BUILDER_HPP
namespace Algo {
vtkSmartPointer<vtkPolyData>  CreateHexagonalHead(double base_diameter, 
                                                  double top_diameter, 
                                                  double height,
                                                  double socket_diameter,
                                                  double socket_height);
vtkSmartPointer<vtkPolyData> CreateTorxHead(double base_diameter, 
               double top_diameter, 
               double height,
               double socket_diameter, 
               double socket_height);

}

#endif