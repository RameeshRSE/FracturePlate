
#include "../InputProcessor/InputProcessor.hpp"

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

#ifndef IGEOMETRY_BUILDER_HPP
#define IGEOMETRY_BUILDER_HPP

namespace Geometry {

class IGeometryBuilder
{
    public:

    virtual vtkSmartPointer<vtkPolyData> CreateGeometry(const  Input::FracturePlateParameters&) = 0;

    protected:
};

}


#endif