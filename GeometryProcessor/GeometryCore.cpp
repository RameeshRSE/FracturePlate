
#include <vtkCylinderSource.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkBooleanOperationPolyDataFilter.h>
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


#include "GeometryCore.hpp"

namespace Geometry {
vtkSmartPointer<vtkPolyData> CreateBox(double width, double length, double height)
{
    // Points for flat fracture plate
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    // Assume origin is (0, 0, 0) for simplicity.
    double z = 0.0;
    points->InsertNextPoint(0.0, 0.0, z);               // Bottom-left corner
    points->InsertNextPoint(width, 0.0, z);            // Bottom-right corner
    points->InsertNextPoint(width, length, z);         // Top-right corner
    points->InsertNextPoint(0.0, length, z);           // Top-left corner

    // Create a single polygon for the flat plate
    vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(4); // 4 corners
    for (int i = 0; i < 4; i++) {
        polygon->GetPointIds()->SetId(i, i);
    }

    // Cell array to hold the polygon
    vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
    polygons->InsertNextCell(polygon);

    // Create the polydata to represent the fracture plate
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetPolys(polygons);

    // 1. Create Fracture Plate Plane with given width and length 
    // 2. Extrude plane to given thickness
    auto extrudeFilter = vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    extrudeFilter->SetInputData(polyData);
    extrudeFilter->SetExtrusionTypeToVectorExtrusion();
    extrudeFilter->SetVector(0.0, 0.0, 1.0); // Extrude along Z-axis
    extrudeFilter->SetScaleFactor(height);      // Extrusion length
    extrudeFilter->Update();

    return  extrudeFilter->GetOutput();
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

vtkSmartPointer<vtkPolyData> 
ApplyBooleanSubtraction(vtkSmartPointer<vtkPolyData> input1,
                        vtkSmartPointer<vtkPolyData> input2)
{
    vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
    clean1->SetInputData(input1);
    clean1->Update();

    vtkSmartPointer<vtkCleanPolyData> clean2 = vtkSmartPointer<vtkCleanPolyData>::New();
    clean2->SetInputData(input2);
    clean2->Update();

    vtkNew<vtkTriangleFilter> tri1;
    tri1->SetInputData(clean1->GetOutput());
    tri1->Update();

    vtkNew<vtkTriangleFilter> tri2;
    tri2->SetInputData(clean2->GetOutput());
    tri2->Update();

    vtkNew<vtkBooleanOperationPolyDataFilter> booleanOperation;
    booleanOperation->SetOperationToDifference();
    booleanOperation->SetInputData(0, tri1->GetOutput());
    booleanOperation->SetInputData(1, tri2->GetOutput());
    booleanOperation->Update();
    return booleanOperation->GetOutput();
}
}