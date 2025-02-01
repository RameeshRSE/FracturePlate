#include <vtkVector.h>
#include <vector>

namespace Algo {
std::vector<vtkVector3d> CreateVShapeThreadProfile(double major_dia, double minor_dia, double pitch);
void CreateButtressThreadProfile();

}