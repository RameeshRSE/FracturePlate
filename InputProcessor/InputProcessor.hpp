
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
        double m_ShaftLength;
        double m_shaftDiameter;
        double m_ThreadPitch;
    };

    struct FracturePlateParameters
    {
        double m_Length;
        double m_Width;
        double m_Thickness;
        PlateType m_Type;
        ScrewParameters m_ScrewParamters;
        std::vector<double> m_3DContourPoints;
        HoleType            m_HoleType;
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