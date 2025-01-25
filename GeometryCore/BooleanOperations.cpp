#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkTriangle.h>
#include <igl/copyleft/cgal/mesh_boolean.h>
#include <Eigen/Core>
#include <vtkTriangleFilter.h>
#include <vtkCleanPolyData.h>


#include "BooleanOperations.hpp"
#include "igl/MeshBooleanType.h"
namespace  {

// Function to convert vtkPolyData to Eigen matrices
void vtkPolyDataToEigen(vtkPolyData* polyData, Eigen::MatrixXd& V, Eigen::MatrixXi& F) {
    auto points = polyData->GetPoints();
    V.resize(points->GetNumberOfPoints(), 3);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double p[3];
        points->GetPoint(i, p);
        V.row(i) << p[0], p[1], p[2];
    }

    auto polys = polyData->GetPolys();
    F.resize(polys->GetNumberOfCells(), 3);
    polys->InitTraversal();
    vtkIdType npts;
    const vtkIdType *pts;
    int i = 0;
    while (polys->GetNextCell(npts, pts)) {
        if (npts == 3) {
            F.row(i++) << pts[0], pts[1], pts[2];
        }
    }
    F.conservativeResize(i, Eigen::NoChange);
}

// Function to convert Eigen matrices back to vtkPolyData
vtkSmartPointer<vtkPolyData> EigenToVtkPolyData(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F) {
    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    auto points = vtkSmartPointer<vtkPoints>::New();
    auto triangles = vtkSmartPointer<vtkCellArray>::New();

    for (int i = 0; i < V.rows(); ++i) {
        points->InsertNextPoint(V(i, 0), V(i, 1), V(i, 2));
    }

    for (int i = 0; i < F.rows(); ++i) {
        auto triangle = vtkSmartPointer<vtkTriangle>::New();
        triangle->GetPointIds()->SetId(0, F(i, 0));
        triangle->GetPointIds()->SetId(1, F(i, 1));
        triangle->GetPointIds()->SetId(2, F(i, 2));
        triangles->InsertNextCell(triangle);
    }

    polyData->SetPoints(points);
    polyData->SetPolys(triangles);
    return polyData;
}

vtkSmartPointer<vtkPolyData> ApplyBoolean(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2, igl::MeshBooleanType op)
{
    // Convert vtkPolyData to Eigen
    Eigen::MatrixXd VA, VB, VC;
    Eigen::MatrixXi FA, FB, FC;
    vtkPolyDataToEigen(input1, VA, FA);
    vtkPolyDataToEigen(input2, VB, FB);   
    // Perform Boolean Operation: Union
    igl::copyleft::cgal::mesh_boolean(VA, FA, VB, FB, op, VC, FC);

    // Convert back to vtkPolyData
    return EigenToVtkPolyData(VC, FC);
}
}
namespace GeometryCore {



vtkSmartPointer<vtkPolyData> ApplyBooleanSubtraction(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2)
{
    
   return ApplyBoolean(input1, input2, igl::MESH_BOOLEAN_TYPE_MINUS);
}

vtkSmartPointer<vtkPolyData> ApplyBooleanUnion(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2)
{
   return ApplyBoolean(input1, input2, igl::MESH_BOOLEAN_TYPE_UNION);

}

vtkSmartPointer<vtkPolyData> ApplyBooleanIntersection(vtkSmartPointer<vtkPolyData> input1, vtkSmartPointer<vtkPolyData> input2)
{
  return ApplyBoolean(input1, input2, igl::MESH_BOOLEAN_TYPE_INTERSECT);
}
}
