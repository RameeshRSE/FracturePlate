
#include <iostream>
#include <vtkCylinderSource.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyLine.h>
#include <vtkTubeFilter.h>

#include <cmath>

#include "ScrewGeometryBuilder.hpp"
#include "GeometryCore.hpp"

namespace  {

    // Function to generate a helical curve
vtkSmartPointer<vtkPolyData> CreateHelicalThread(double radius, double pitch, double height) {
    auto points = vtkSmartPointer<vtkPoints>::New();
    int n_turns = int(height/pitch);
    int resolution = n_turns * 100; // Higher resolution gives smoother thread
    double thetaStep = 2.0* vtkMath::Pi() / 100.0; // Adjust for thread detail

    for (int i = 0; i <= resolution; ++i) {
        double theta = i * thetaStep;
        double x = radius * cos(theta);
        double y = radius * sin(theta);
        double z = (double)(i/100.0) * pitch; 
        points->InsertNextPoint(x, y, z);
    }

    auto polyline = vtkSmartPointer<vtkPolyLine>::New();
    polyline->GetPointIds()->SetNumberOfIds(resolution + 1);
    for (int i = 0; i <= resolution; ++i) {
        polyline->GetPointIds()->SetId(i, i);
    }

    auto lines = vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(polyline);

    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetLines(lines);

    vtkNew<vtkTubeFilter> tubeFilter;
    tubeFilter->SetInputData(polyData);
    tubeFilter->SetRadius(.2); // default is .5
    tubeFilter->SetNumberOfSides(50);
    tubeFilter->Update();
    

    return tubeFilter->GetOutput();
}

}
namespace Geometry {

vtkSmartPointer<vtkPolyData> ScrewGeometryBuilder::CreateGeometry(const Input::FracturePlateParameters& params)
{
    const auto& screw_params = params.m_ScrewParamters;
    // Screw shaft
    auto shaft = Geometry::CreateCylinder(screw_params.m_shaftDiameter/2.0, screw_params.m_ShaftLength);
    shaft  = Geometry::PivotPointRotation(shaft, vtkVector3d(0,0,0), vtkVector3d(1, 0, 0), 90);

    std::cout<<" H D"<<screw_params.m_HeadHeight<<"\n";
    // Screw head
    auto head = Geometry::CreateCylinder(screw_params.m_HeadDiameter/2.0, screw_params.m_HeadHeight);
    head = Geometry::Translate(head, vtkVector3d(0, screw_params.m_ShaftLength/2.0, 0.0));
    head  = Geometry::PivotPointRotation(head, vtkVector3d(0,0,0), vtkVector3d(1, 0, 0), 90);


    auto helix = CreateHelicalThread(screw_params.m_shaftDiameter/2.0, screw_params.m_ThreadPitch, screw_params.m_ShaftLength); // Radius, Pitch, Height
    helix = Geometry::Translate(helix, vtkVector3d(0, 0.0, -screw_params.m_ShaftLength/2.0));
    // Combine parts
    auto append = vtkSmartPointer<vtkAppendPolyData>::New();
    append->AddInputData(shaft);
    append->AddInputData(head);
    append->AddInputData(helix);
    append->Update();

    return append->GetOutput();
}

}