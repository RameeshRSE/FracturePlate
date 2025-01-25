
#include <vtkCylinderSource.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolygon.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.H>
#include <vtkTriangleFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkCubeSource.h>
#include "GeometryCore.hpp"

namespace Geometry {
vtkSmartPointer<vtkPolyData> CreateBox(double width, double length, double height)
{
    // Points for flat fracture plate
    auto box = vtkSmartPointer<vtkCubeSource>::New();
    box->SetXLength(width);
    box->SetYLength(length);
    box->SetZLength(height);
    box->Update();
    return  box->GetOutput();
}

vtkSmartPointer<vtkPolyData> CreateCylinder(double radius, double height)
{
    auto c = vtkSmartPointer<vtkCylinderSource>::New();
    c->SetHeight(height);
    c->SetRadius(radius);
    c->SetCenter(0, 0, 0);
    c->SetResolution(50);
    c->Update();

    return c->GetOutput();
}

vtkSmartPointer<vtkPolyData>
 PivotPointRotation(vtkSmartPointer<vtkPolyData> obj, 
                    const vtkVector3d & pivot, 
                    const vtkVector3d& axis, 
                    double angle_in_degree)
{
    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetInputData(obj);
    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    transform->Translate(-pivot.GetX(), -pivot.GetY(), -pivot.GetZ());
    transform->RotateWXYZ (angle_in_degree,axis.GetX(), axis.GetY(), axis.GetZ());
    transform->Translate(pivot.GetX(), pivot.GetY(), pivot.GetZ());
    transform->Update();
    transformFilter->SetTransform(transform);
    transformFilter->Update();

    return transformFilter->GetPolyDataOutput();
}

vtkSmartPointer<vtkPolyData> Translate(vtkSmartPointer<vtkPolyData> obj, const vtkVector3d & to)
{
    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetInputData(obj);
    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    transform->Translate(to.GetX(), to.GetY(), to.GetZ());
    transform->Update();
    transformFilter->SetTransform(transform);
    transformFilter->Update();

    return transformFilter->GetPolyDataOutput();
}

vtkSmartPointer<vtkPolyData> Scale(vtkSmartPointer<vtkPolyData> obj, const vtkVector3d & pivot, const vtkVector3d & scale)
{
    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetInputData(obj);
    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    transform->Translate(-pivot.GetX(), -pivot.GetY(), -pivot.GetZ());
    transform->Scale (scale.GetX(), scale.GetY(), scale.GetZ());
    transform->Translate(pivot.GetX(), pivot.GetY(), pivot.GetZ());
    transform->Update();
    transformFilter->SetTransform(transform);
    transformFilter->Update();

    return transformFilter->GetPolyDataOutput();
}

vtkSmartPointer<vtkPolyData> Trinagulate(vtkSmartPointer<vtkPolyData> input)
{
    vtkSmartPointer<vtkCleanPolyData> clean = vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputData(input);
    clean->Update();


    vtkNew<vtkTriangleFilter> tr;
    tr->SetInputData(clean->GetOutput());
    tr->Update();

    return tr->GetOutput();
}
}