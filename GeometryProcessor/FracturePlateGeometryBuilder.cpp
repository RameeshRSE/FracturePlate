
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

#include "GeometryCore.hpp"
#include "FracturePlateGeometryBuilder.hpp"
#include "../GeometryCore/BooleanOperations.hpp"

namespace 
{
    
    vtkSmartPointer<vtkPolyData> BuildFlatPlate(const Input::FracturePlateParameters& params)
    {
        // Points for flat fracture plate
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Assume origin is (0, 0, 0) for simplicity.
        double z = 0.0;
        double hw = params.m_Width/2.0;
        double ht = params.m_Thickness/2.0;
        double hl = params.m_Length/2.0;
        double fl_length = params.m_Length - params.m_Width;
        double fl_width = params.m_Width;
        double fl_height = params.m_Thickness;

        auto f_plate = Geometry::CreateBox(fl_width, fl_length , fl_height);
        auto l_end = Geometry::CreateCylinder(hw, params.m_Thickness);
        auto r_end = Geometry::CreateCylinder(hw, params.m_Thickness); 
       
        l_end = Geometry::PivotPointRotation(l_end, vtkVector3d(), vtkVector3d(1.0, 0.0, 0.0),-90);
        r_end = Geometry::PivotPointRotation(r_end, vtkVector3d(), vtkVector3d(1.0, 0.0, 0.0),-90);
        l_end = Geometry::Translate(l_end, vtkVector3d(0,  -fl_length/2.0, 0));
        r_end = Geometry::Translate(r_end, vtkVector3d(0,  fl_length/2.0,  0));

        r_end = Geometry::Trinagulate(r_end);
        l_end = Geometry::Trinagulate(l_end);
        f_plate =  Geometry::Trinagulate(f_plate);

        l_end=  GeometryCore::ApplyBooleanSubtraction(l_end, f_plate);
        r_end = GeometryCore::ApplyBooleanSubtraction(r_end, f_plate);

        auto append = vtkSmartPointer<vtkAppendPolyData>::New();
        append->AddInputData(f_plate );
        append->AddInputData(l_end);
        append->AddInputData(r_end);
        append->Update();
        return  append->GetOutput();
    }
}

namespace Geometry {
vtkSmartPointer<vtkPolyData> FracturePlateGeometryBuilder::CreateGeometry(const Input::FracturePlateParameters& params)
{
    return BuildFlatPlate(params);
}
}