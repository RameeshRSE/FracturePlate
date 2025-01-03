
#include <vtkSmoothPolyDataFilter.h>

#include "IVolumeBuilder.h"

#ifndef MARCHINGCUBEVOLUMEBUILDER_H
#define MARCHINGCUBEVOLUMEBUILDER_H

namespace VolumeBuilder
{
    class MarchingCubeVolumeBuilder :public IVolumeBuilder
    {
        public:
            void BuildVolumeFromSource(vtkImageData* source) override;
            vtkSmartPointer<vtkPolyData> GetPolyData() const override;
            vtkAlgorithmOutput * GetOutputPort() const override;

        private:
            vtkSmartPointer<vtkSmoothPolyDataFilter> m_smoother;
    };
}

#endif