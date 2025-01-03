
#include<string>
#include <vtkNew.h>
#include <vtkDICOMImageReader.h>
#include <vtkAlgorithmOutput.h>
#include <vtkImageData.h>

#ifndef MRIREADER_H
#define MRIREADER_H

namespace MedicalImage
{
    class MRIReader
    {
        public:
            MRIReader() = default;
            void ReadFile(const std::string& dicomFolder);
            vtkAlgorithmOutput * GetOutputPort();
            vtkImageData* GetOutput();
        private:
            vtkNew<vtkDICOMImageReader> m_Reader;    
    };
}

#endif
