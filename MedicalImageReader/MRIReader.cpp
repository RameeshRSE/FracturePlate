
#include "MRIReader.hpp"


namespace  MedicalImage
{
    void MRIReader::ReadFile(const std::string& dicomFolder)
    {
        m_Reader->SetDirectoryName(dicomFolder.c_str());
        m_Reader->Update();
    }

    vtkAlgorithmOutput* MRIReader::GetOutputPort()
    {
        return m_Reader->GetOutputPort();
    }

    vtkImageData* MRIReader::GetOutput()
    {
        return m_Reader->GetOutput();
    }
} // namespace MedicalImage
