
#include <vtkAppendPolyData.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTriangleFilter.h>
#include <vtkVector.h>


#include "ScrewHeadProfileBuilder.hpp"
#include "GeometryCore.hpp"
#include "../GeometryCore/BooleanOperations.hpp"
#include "../GeometricAlgo/CoreMath.hpp"

namespace Algo {

vtkSmartPointer<vtkPolyData> 
 CreateHexagonalHead(double base_diameter, 
                     double top_diameter, 
                     double height,
                     double socket_diameter,
                     double socket_height)
                     {
   auto head = Geometry::CreateCone(top_diameter, base_diameter, height);
   auto tp = CoreMath::GenerateHexagon(socket_diameter/2.0);
   auto points = vtkSmartPointer<vtkPoints>::New();
   auto poly = vtkSmartPointer<vtkCellArray>::New();
   auto scale = base_diameter/top_diameter;
   poly->InsertNextCell(tp.size()); // number of points

    for(int i = 0; i < tp.size(); ++i)
    {
        points->InsertPoint(i, tp[i].GetX(), tp[i].GetY(), tp[i].GetZ());
        poly->InsertCellPoint(i);
    }

   auto hex_profile= vtkSmartPointer<vtkPolyData>::New();
   hex_profile->SetPoints(points);
   hex_profile->SetPolys(poly);

   auto triangle_filter = vtkSmartPointer<vtkTriangleFilter>::New();
   triangle_filter->SetInputData(hex_profile);
   triangle_filter->Update();

   auto extrusion =  vtkSmartPointer<vtkLinearExtrusionFilter>::New();
   extrusion->SetExtrusionTypeToNormalExtrusion();
   extrusion->SetVector(0, 0, socket_height);
   extrusion->SetInputData(triangle_filter->GetOutput());
   extrusion->Update();

   head = Geometry::Trinagulate(head);
   auto hex_pyramid = Geometry::Trinagulate(extrusion->GetOutput());
   hex_pyramid = Geometry::Translate(hex_pyramid, vtkVector3d(0, 0, height - socket_height));
   

   head = GeometryCore::ApplyBooleanSubtraction(head, hex_pyramid);

   return head;
}

vtkSmartPointer<vtkPolyData>
 CreateTorxHead(double base_diameter, 
               double top_diameter, 
               double height,
               double socket_diameter, 
               double socket_height)
{
   auto head = Geometry::CreateCone(top_diameter, base_diameter, height);
   auto tp = CoreMath::GenerateTorxProfile(socket_diameter/2.0);
   auto points = vtkSmartPointer<vtkPoints>::New();
   auto poly = vtkSmartPointer<vtkCellArray>::New();
   auto scale = base_diameter/top_diameter;
   poly->InsertNextCell(tp.size()); // number of points

    for(int i = 0; i < tp.size(); ++i)
    {
        points->InsertPoint(i, tp[i].GetX(), tp[i].GetY(), tp[i].GetZ());
        poly->InsertCellPoint(i);
    }

   auto torx_profile= vtkSmartPointer<vtkPolyData>::New();
   torx_profile->SetPoints(points);
   torx_profile->SetPolys(poly);

   auto triangle_filter = vtkSmartPointer<vtkTriangleFilter>::New();
   triangle_filter->SetInputData(torx_profile);
   triangle_filter->Update();

   auto extrusion =  vtkSmartPointer<vtkLinearExtrusionFilter>::New();
   extrusion->SetExtrusionTypeToNormalExtrusion();
   extrusion->SetVector(0, 0, socket_height);
   extrusion->SetInputData(triangle_filter->GetOutput());
   extrusion->Update();

   head = Geometry::Trinagulate(head);
   auto torx_pyramid = Geometry::Trinagulate(extrusion->GetOutput());
   torx_pyramid = Geometry::Translate(torx_pyramid, vtkVector3d(0, 0, height - socket_height));
   
   head = GeometryCore::ApplyBooleanSubtraction(head, torx_pyramid);


   return head;
}

}