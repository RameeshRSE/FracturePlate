

#include "HoleGeometryBuilder.hpp"

#include "GeometryCore.hpp"

#include "../GeometricAlgo/ScrewPlacingAlgo.hpp"
#include <vector>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>
#include <vtkVector.h>
#include "../GeometryCore/BooleanOperations.hpp"


namespace Geometry {

HoleGeometryBuilder::HoleGeometryBuilder(vtkSmartPointer<vtkPolyData> plate, vtkSmartPointer<vtkPolyData> screw):
m_PlateGeometry(plate),
m_ScrewGeometry(screw){

}

vtkSmartPointer<vtkPolyData> HoleGeometryBuilder::CreateGeometry(const Input::FracturePlateParameters& params){
    auto plane_width = params.m_Width;
    auto plane_length = params.m_Length;
    auto plane_thickness = params.m_Thickness;
    auto point_radius = params.m_ScrewParamters.m_HeadTopDiameter;
    auto head_height = params.m_ScrewParamters.m_HeadHeight;
    auto hw = plane_width/2.0;
    auto hl = plane_length/2.0;
    auto ht = plane_thickness/2.0;
    auto sl = params.m_ScrewParamters.m_ShaftLength/2.0;
    
    auto points = Algo::DistributeScrews(10, plane_width,plane_length - hw, point_radius);
    std::vector<vtkSmartPointer<vtkPolyData>> aligned_screws;
    auto append = vtkSmartPointer<vtkAppendPolyData>::New();
    auto append_screws = vtkSmartPointer<vtkAppendPolyData>::New();
    auto plate_copy = vtkSmartPointer<vtkPolyData>::New();
    plate_copy->DeepCopy(m_PlateGeometry);

    for(const auto& point : points ){
        vtkVector3d p3d;
        auto z = ht - sl - head_height;
        p3d.Set(point.x - hw, point.y - hl, z);
        auto screw_copy = vtkSmartPointer<vtkPolyData>::New();
        screw_copy->DeepCopy(m_ScrewGeometry);
        screw_copy = Geometry::Translate(screw_copy, p3d);

        append_screws->AddInputData(screw_copy);
    }

    append_screws->Update();

    //plate_copy = GeometryCore::ApplyBooleanSubtraction(plate_copy, append_screws->GetOutput());

    append->AddInputData(plate_copy);

    append->Update();


    return append->GetOutput();
}
}