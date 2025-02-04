
#include <iostream>
#include <vtkCylinderSource.h>
#include <vtkLineSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTubeFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyLine.h>
#include <vtkTubeFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkFeatureEdges.h>
#include <vtkRotationalExtrusionFilter.h>
#include <cmath>
#include <vtkVector.h>

#include "ScrewGeometryBuilder.hpp"
#include "GeometryCore.hpp"
#include "ThreadProfileBuilder.hpp"
#include "ScrewHeadProfileBuilder.hpp"

namespace  {

    // Function to generate a helical curve
vtkSmartPointer<vtkPolyData> CreateHelicalThread(double radius, double pitch, double height) {
    auto points = vtkSmartPointer<vtkPoints>::New();
    int n_turns = int(height/pitch);
    int resolution = n_turns * 20; // Higher resolution gives smoother thread
    auto poly = vtkSmartPointer<vtkCellArray>::New();
    auto tp = Algo::CreateVShapeThreadProfile(radius + 0.2, radius, pitch);

    /*points->InsertPoint(0, 1.0, 0.0, 0.0);
    points->InsertPoint(1, 1.0732, 0.0, -0.1768);
    points->InsertPoint(2, 1.25, 0.0, -0.25);
    points->InsertPoint(3, 1.4268, 0.0, -0.1768);
    points->InsertPoint(4, 1.5, 0.0, 0.00);
    points->InsertPoint(5, 1.4268, 0.0, 0.1768);
    points->InsertPoint(6, 1.25, 0.0, 0.25);
    points->InsertPoint(7, 1.0732, 0.0, 0.1768);*/

    points->InsertPoint(0, tp[0].GetX(), tp[0].GetY(), tp[0].GetZ());
    points->InsertPoint(1, tp[1].GetX(), tp[1].GetY(), tp[1].GetZ());
    points->InsertPoint(2, tp[2].GetX(), tp[2].GetY(), tp[2].GetZ());
    points->InsertPoint(3, tp[3].GetX(), tp[3].GetY(), tp[3].GetZ());
    points->InsertPoint(4, tp[4].GetX(), tp[4].GetY(), tp[4].GetZ());
    poly->InsertNextCell(5); // number of points
    poly->InsertCellPoint(0);
    poly->InsertCellPoint(1);
    poly->InsertCellPoint(2);
    poly->InsertCellPoint(3);
    poly->InsertCellPoint(4);

    auto profile= vtkSmartPointer<vtkPolyData>::New();
    profile->SetPoints(points);
    profile->SetPolys(poly);

    auto extrude= vtkSmartPointer<vtkRotationalExtrusionFilter>::New();
    extrude->SetInputData(profile);
    extrude->SetResolution(resolution);
    extrude->SetTranslation(height);
    extrude->SetDeltaRadius(0.0);
    extrude->SetAngle(n_turns*360.0); 
    extrude->Update();

    auto normals= vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputConnection(extrude->GetOutputPort());
    normals->SetFeatureAngle(60);
    normals->Update();

   
    return normals->GetOutput() ;
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
    auto head = Algo::CreateTorxHead(screw_params.m_HeadBaseDiameter, screw_params.m_HeadTopDiameter, screw_params.m_HeadHeight,screw_params.m_socket_diameter, screw_params.m_socket_height);
    head = Geometry::Translate(head, vtkVector3d(0, 0.0, screw_params.m_ShaftLength/2.0));

    auto helix = CreateHelicalThread(screw_params.m_shaftDiameter/2.0, screw_params.m_ThreadPitch, screw_params.m_ShaftLength); // Radius, Pitch, Height
    helix = Geometry::Translate(helix, vtkVector3d(0, 0.0, -(screw_params.m_ShaftLength/2.0)));
   
    // Combine parts
    auto append = vtkSmartPointer<vtkAppendPolyData>::New();
    append->AddInputData(shaft);
    append->AddInputData(head);
    append->AddInputData(helix);
    append->Update();

    return  Geometry::Trinagulate(append->GetOutput());
}

}