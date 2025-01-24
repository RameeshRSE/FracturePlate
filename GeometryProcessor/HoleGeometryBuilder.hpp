#include "IGeometryBuilder.hpp"

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

namespace Geometry {

class HoleGeometryBuilder: public IGeometryBuilder{
    public:
      HoleGeometryBuilder(vtkSmartPointer<vtkPolyData> plate, vtkSmartPointer<vtkPolyData> screw);
      vtkSmartPointer<vtkPolyData> CreateGeometry(const Input::FracturePlateParameters&) override;

    private:
        vtkSmartPointer<vtkPolyData> m_PlateGeometry;
        vtkSmartPointer<vtkPolyData> m_ScrewGeometry;
};

}