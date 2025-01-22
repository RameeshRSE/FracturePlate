
#include<memory>
#include <string>
#include <vector>

#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

namespace Input 
{
    enum PlateType
    {
        PRE_CONTURED,
        STRAIGHT,
    };

    enum HoleType
    {
        COMPRESSION_TYPE,
        LOCKING,
        COMBINED,
    };

    struct ScrewParameters
    {
        double m_ShaftLength = 0.0;
        double m_shaftDiameter = 0.0;
        double m_ThreadPitch = 0.0;
        double m_HeadDiameter  = 0.0;
        double m_HeadHeight = 0.0;
        double m_ThreadDepth = 0.0;
    };

    struct FracturePlateParameters
    {
        double m_Length = 0.0;
        double m_Width = 0.0;
        double m_Thickness = 0.0;
        int    m_NoOfScrews = 0.0 ;
        PlateType m_Type = STRAIGHT;
        ScrewParameters m_ScrewParamters;
        std::vector<double> m_3DContourPoints;
        HoleType            m_HoleType = LOCKING;
    };

    class InputProcessor
    {
        public:
        static InputProcessor& getShared();
        FracturePlateParameters ProcessParams(const std::string& json_string);

        private:
        InputProcessor() noexcept;
        InputProcessor(const InputProcessor&) = delete;
        InputProcessor(const InputProcessor&&) = delete;
        static std::unique_ptr<InputProcessor> mp_shared;
    };
}
#endif