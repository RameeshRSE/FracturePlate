#include "../MediImageProcessor/MediImageProcessor.h"
#include <iostream>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <DICOM Folder> <Output.obj>" << std::endl;
        return EXIT_FAILURE;
    }

    MediImageApp::MediImageProcessor processor;

    processor.ProcessMRI(argv[1]);
    auto& volumeBuilder = processor.GetVolumeBuilder();

     vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(volumeBuilder.GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.1, 0.1, 0.1); // Optional: Change color of the model

    // Step 5: Visualization
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.1, 0.1); // Background color
    
    renderWindow->Render();
    renderWindowInteractor->Start();



}