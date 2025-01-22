#include "IGeometryBuilder.hpp"


#ifndef FRACTURE_PLATE_GEOMETRY_BUILDER_HPP
#define FRACTURE_PLATE_GEOMETRY_BUILDER_HPP
namespace Geometry {
         
class FracturePlateGeometryBuilder : public IGeometryBuilder
{
   public:
        vtkSmartPointer<vtkPolyData> CreateGeometry(const Input::FracturePlateParameters&) override;
   private:
};
}

#endif