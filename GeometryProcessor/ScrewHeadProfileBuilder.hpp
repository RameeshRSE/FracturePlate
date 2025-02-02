
#include <vtkVector.h>
#include <vector>

#ifndef SCREW_HEAD_PROFILE_BUILDER_HPP
#define SCREW_HEAD_PROFILE_BUILDER_HPP
namespace Algo {
std::vector<vtkVector3d> CreateHexagonalHead(double base_diameter, double top_diameter, double height);
std::vector<vtkVector3d> CreateTorxHead(double base_diameter, double top_diameter, double height);

}

#endif