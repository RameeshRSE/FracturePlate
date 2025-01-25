

#include "HoleGeometryBuilder.hpp"

#include "GeometryCore.hpp"

#include "../GeometricAlgo/PoissonDiskSampling.hpp"
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
    auto point_radius = params.m_ScrewParamters.m_HeadDiameter*1.5;
    auto hw = plane_width/2.0;
    auto hl = plane_length/2.0;
    auto ht = plane_thickness/2.0;
    auto sl = params.m_ScrewParamters.m_ShaftLength;
    Algo::PoissonDiskSampling dist_algo(plane_width - params.m_ScrewParamters.m_HeadDiameter, plane_length - params.m_ScrewParamters.m_HeadDiameter, point_radius );
    auto points = dist_algo.Generate();
    std::vector<vtkSmartPointer<vtkPolyData>> aligned_screws;
    auto append = vtkSmartPointer<vtkAppendPolyData>::New();
     auto append_screws = vtkSmartPointer<vtkAppendPolyData>::New();
    auto plate_copy = vtkSmartPointer<vtkPolyData>::New();
    plate_copy->DeepCopy(m_PlateGeometry);

    for(const auto& point : points ){
        vtkVector3d p3d;
        p3d.Set(point.x, point.y,-sl/2.0 + params.m_ScrewParamters.m_HeadHeight);
        auto screw_copy = vtkSmartPointer<vtkPolyData>::New();
        screw_copy->DeepCopy(m_ScrewGeometry);
        screw_copy = Geometry::Translate(screw_copy, vtkVector3d(-1.9 ,-hl + 1.9,0));
        screw_copy = Geometry::Translate(screw_copy, p3d);
        append_screws->AddInputData(screw_copy);
    }

    append_screws->Update();

    plate_copy = GeometryCore::ApplyBooleanSubtraction(plate_copy, append_screws->GetOutput());

    append->AddInputData(plate_copy);

    append->Update();


    return append->GetOutput();
}
}