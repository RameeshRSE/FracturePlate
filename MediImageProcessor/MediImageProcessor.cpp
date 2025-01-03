#include "MediImageProcessor.h"
#include "../MedicalImageReader/MRIReader.hpp"
#include "../OBJExporter/ObjExporter.h"

namespace MediImageApp
{
    void MediImageProcessor::ProcessMRI(const std::string& mri_file)
    {
        MedicalImage::MRIReader mri_reader;
        
        mri_reader.ReadFile(mri_file);
        m_volumeBuilder.BuildVolumeFromSource(mri_reader.GetOutput());
    }

     void MediImageProcessor::ExportToObj(const std::string&output_file)
     {
        MediImageExporter::ObjExporter obj_exporter;
        obj_exporter.ExportToFile(output_file, m_volumeBuilder.GetOutputPort());
     }

    VolumeBuilder::MarchingCubeVolumeBuilder& MediImageProcessor::GetVolumeBuilder()
    {
        return m_volumeBuilder;
    }
}
