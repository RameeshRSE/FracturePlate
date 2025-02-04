
#include <vtkSmartPointer.h>
#include <vtkVector.h>
#include <vtkPolyData.h>

#ifndef GEOMETRY_CORE_HPP
#define GEOMETRY_CORE_HPP

namespace Geometry {

vtkSmartPointer<vtkPolyData> CreateBox(double width, double length, double height);
vtkSmartPointer<vtkPolyData> CreateCylinder( double radius, double height);
vtkSmartPointer<vtkPolyData> CreateCone( double top_diameter, double botton_diameter, double height);
vtkSmartPointer<vtkPolyData> PivotPointRotation(vtkSmartPointer<vtkPolyData> obj, const vtkVector3d & pivot, const vtkVector3d& axis, double angle_in_degree);
vtkSmartPointer<vtkPolyData> Translate(vtkSmartPointer<vtkPolyData> obj, const vtkVector3d & to);
vtkSmartPointer<vtkPolyData> Scale(vtkSmartPointer<vtkPolyData> obj, const vtkVector3d & pivot, const vtkVector3d & to);
vtkSmartPointer<vtkPolyData> Trinagulate(vtkSmartPointer<vtkPolyData> input);
}

#endif