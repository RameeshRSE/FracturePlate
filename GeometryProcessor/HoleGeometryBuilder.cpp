

#include "HoleGeometryBuilder.hpp"

#include "GeometryCore.hpp"

#include "../GeometricAlgo/PoissonDiskSampling.hpp"
#include <vector>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>
#include <vtkVector.h>

namespace Geometry {

HoleGeometryBuilder::HoleGeometryBuilder(vtkSmartPointer<vtkPolyData> plate, vtkSmartPointer<vtkPolyData> screw):
m_PlateGeometry(plate),
m_ScrewGeometry(screw){

}

vtkSmartPointer<vtkPolyData> HoleGeometryBuilder::CreateGeometry(const Input::FracturePlateParameters& params){
    auto plane_width = params.m_Width;
    auto plane_length = params.m_Length;
    auto plane_thickness = params.m_Thickness;
    auto point_radius = params.m_ScrewParamters.m_HeadDiameter;
    auto hw = plane_width/2.0;
    auto hl = plane_length/2.0;
    auto ht = plane_thickness/2.0;
    Algo::PoissonDiskSampling dist_algo(plane_width - params.m_ScrewParamters.m_HeadDiameter, plane_length - params.m_ScrewParamters.m_HeadDiameter, point_radius );
    auto points = dist_algo.Generate();
    std::vector<vtkSmartPointer<vtkPolyData>> aligned_screws;
    auto append = vtkSmartPointer<vtkAppendPolyData>::New();
    auto plate_copy = vtkSmartPointer<vtkPolyData>::New();
    plate_copy->DeepCopy(m_PlateGeometry);

    /*for(const auto& point : points ){
        vtkVector3d p3d;
        p3d.Set(point.x, point.y,0.0);
        auto screw_copy = vtkSmartPointer<vtkPolyData>::New();
        screw_copy->DeepCopy(m_ScrewGeometry);
        screw_copy = Geometry::Translate(screw_copy, vtkVector3d(-1.9 ,-hl + 1.9, -ht));
        screw_copy = Geometry::Translate(screw_copy, p3d);
    }*/

    plate_copy = Geometry::ApplyBooleanSubtraction(plate_copy, m_ScrewGeometry);

    m_ScrewGeometry = Geometry::Translate(m_ScrewGeometry, vtkVector3d(2, 2, 0));
    append->AddInputData(m_ScrewGeometry);
    append->AddInputData(plate_copy);

    append->Update();


    return append->GetOutput();
}
}