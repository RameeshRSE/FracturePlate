
#ifndef VOLUMEBUILDER_H
#define VOLUMEBUILDER_H

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

class vtkImageData;
class vtkAlgorithmOutput;

namespace VolumeBuilder
{
    class IVolumeBuilder
    {
        public:
          virtual void BuildVolumeFromSource(vtkImageData* source) = 0;
          virtual vtkSmartPointer<vtkPolyData> GetPolyData() const = 0;
          virtual vtkAlgorithmOutput * GetOutputPort() const = 0;
    };
}

#endif