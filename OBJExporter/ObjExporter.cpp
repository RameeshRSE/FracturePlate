
#include <vtkOBJWriter.h>
#include <vtkSmartPointer.h>

#include "ObjExporter.h"


namespace MediImageExporter
{
    void ObjExporter::ExportToFile(const std::string& file,  vtkAlgorithmOutput *meshSource)
    {
        auto objWriter = vtkSmartPointer<vtkOBJWriter>::New();
        objWriter->SetFileName(file.c_str());
        objWriter->SetInputConnection(meshSource);
        objWriter->Write();
    }
}