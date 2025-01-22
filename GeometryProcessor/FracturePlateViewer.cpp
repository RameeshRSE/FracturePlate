
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include "../InputProcessor/InputProcessor.hpp"
#include "ScrewGeometryBuilder.hpp"
#include "FracturePlateGeometryBuilder.hpp"



int main()
{
    auto f = R"(
    {
        "fracture_plate": {
            "no_of_screws": 5,
            "width":  10,
            "length": 70,
            "thickness": 2.0,
            "plate_type": 0,
            "screw_params" : {
            "shaft_diameter": 3.0,
            "shaft_length": 50.0,
            "thread_pitch": 1,
            "thread_depth": 1,
            "head_diameter": 5.0,
            "head_height": 1.0
            },
            "contours":[]
        }
    }
    )";
    Input::InputProcessor& p = Input::InputProcessor::getShared();
   
    auto params = p.ProcessParams(f);


    auto screw = Geometry::ScrewGeometryBuilder().CreateGeometry(params);
    auto f_plate = Geometry::FracturePlateGeometryBuilder().CreateGeometry(params);
    
    auto screw_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    screw_mapper->SetInputData(screw);

    auto f_plate_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    f_plate_mapper->SetInputData(f_plate);
    
    auto screw_actor = vtkSmartPointer<vtkActor>::New();
    screw_actor->SetMapper(screw_mapper);
    screw_actor->GetProperty()->SetColor(0.6, 0.6, 0.6); 

    auto f_plate_actor = vtkSmartPointer<vtkActor>::New();
    f_plate_actor->SetMapper(f_plate_mapper);
    f_plate_actor->GetProperty()->SetColor(0.3, 0.3, 0.1); 

    // Step 5: Visualization
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(screw_actor);
    renderer->AddActor(f_plate_actor);
    renderer->SetBackground(0.1, 0.1, 0.1); // Background color
    
    renderWindow->Render();
    renderWindowInteractor->Start();

    return 0;
}