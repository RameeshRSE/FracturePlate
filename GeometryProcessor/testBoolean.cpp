#include <vtkSmartPointer.h>
#include <vtkCylinderSource.h>
#include <vtkCubeSource.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

int main()
{
    // Create a cylinder
    auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(50); // More facets for a smoother cylinder
    cylinder->SetHeight(5.0);
    cylinder->SetRadius(1.5);
    cylinder->Update(); // Ensure it is updated

    // Create a cube
    auto cube = vtkSmartPointer<vtkCubeSource>::New();
    cube->SetXLength(2.0);
    cube->SetYLength(2.0);
    cube->SetZLength(2.0);

    // Transform the cube (optional: move to overlap with cylinder as needed)
    auto transform = vtkSmartPointer<vtkTransform>::New();
    transform->Translate(2.5, 0.0, 0.2); // Adjust position of cube relative to cylinder

    auto transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transformFilter->SetInputConnection(cube->GetOutputPort());
    transformFilter->SetTransform(transform);
    transformFilter->Update();

    // Perform Boolean subtraction: cylinder - cube
    auto booleanOperation = vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
    booleanOperation->SetOperationToDifference(); // Subtract the cube from the cylinder
    booleanOperation->SetInputConnection(0, cylinder->GetOutputPort());
    booleanOperation->SetInputConnection(1, cube->GetOutputPort());
    booleanOperation->Update();

    // Mapper and Actor for result
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(booleanOperation->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Renderer, RenderWindow, and RenderWindowInteractor
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4); // Dark blue background

    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);

    auto renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Start the interaction
    renderWindow->Render();
    renderWindowInteractor->Start();

    return 0;
}
