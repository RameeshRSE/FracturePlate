#ifndef OBJEXPORTER_H
#define OBJEXPORTER_H

#include<string>

class vtkAlgorithmOutput;

namespace MediImageExporter
{
    class ObjExporter
    {
        public:
          void ExportToFile(const std::string& file,  vtkAlgorithmOutput *meshSource);
    };

}

#endif