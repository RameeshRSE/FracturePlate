#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#ifndef BOOLEAN_OPERATIONS_HPP
#define BOOLEAN_OPERATIONS_HPP

namespace GeometryCore {
vtkSmartPointer<vtkPolyData> ApplyBooleanSubtraction(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2);
vtkSmartPointer<vtkPolyData> ApplyBooleanUnion(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2);
vtkSmartPointer<vtkPolyData> ApplyBooleanIntersection(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2);
}
#endif
