#include <vtkImageData.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyData.h>

#include "MarchingCubeVolumeBuilder.h"

namespace VolumeBuilder
{
    void MarchingCubeVolumeBuilder::BuildVolumeFromSource(vtkImageData* source)
    {
         vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
        marchingCubes->SetInputData(source);
        marchingCubes->ComputeNormalsOn();
        marchingCubes->SetValue(0, 500);  // Threshold value, adjust based on your data
        marchingCubes->Update();
        vtkSmartPointer<vtkPolyData> surface = marchingCubes->GetOutput();

        // Optional: Smooth the surface mesh
        m_smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
        m_smoother->SetInputData(surface);
        m_smoother->SetNumberOfIterations(20);  // Adjust iterations for smoothness
        m_smoother->SetRelaxationFactor(0.1);  // Adjust smoothing strength
        m_smoother->Update();
    }

    vtkSmartPointer<vtkPolyData> MarchingCubeVolumeBuilder::GetPolyData() const
    {
        return m_smoother->GetOutput();;
    }

    vtkAlgorithmOutput * MarchingCubeVolumeBuilder::GetOutputPort() const
    {
        return m_smoother->GetOutputPort();
    }
}