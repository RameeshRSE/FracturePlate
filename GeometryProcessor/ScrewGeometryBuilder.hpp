
#include "IGeometryBuilder.hpp"


#ifndef SCREW_GEOMETRY_BUILDER_HPP
#define SCREW_GEOMETRY_BUILDER_HPP

namespace Geometry {

class ScrewGeometryBuilder : public IGeometryBuilder
{
    public:
        vtkSmartPointer<vtkPolyData> CreateGeometry( const Input::FracturePlateParameters&) override;
    private:
};
}

#endif