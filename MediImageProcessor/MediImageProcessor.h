
#include <string>
#include "../3DVolumeBuilder/MarchingCubeVolumeBuilder.h"

#ifndef MediImageProcessor_H
#define MediImageProcessor_H

namespace MediImageApp
{
    class MediImageProcessor
    {
        public:
           void ProcessMRI(const std::string& mri_file); 
           void ExportToObj(const std::string&output_file);   
           VolumeBuilder::MarchingCubeVolumeBuilder& GetVolumeBuilder();
        private:
            VolumeBuilder::MarchingCubeVolumeBuilder m_volumeBuilder;
    };
}

#endif

