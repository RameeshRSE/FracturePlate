
#include "InputProcessor.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <iostream>

namespace Input 
{
    using json = nlohmann::json;
    std::unique_ptr<InputProcessor> InputProcessor::mp_shared;
   
    FracturePlateParameters buildFromJson(const json& root)
    {
        FracturePlateParameters params;
        try {
            auto fracture_plate_item = root["fracture_plate"]; 
            auto contours = fracture_plate_item["contours"];
            auto screw_item = fracture_plate_item["screw_params"];
            params.m_Length = fracture_plate_item["length"];;
            params.m_Width = fracture_plate_item["width"];
            params.m_Thickness = fracture_plate_item["thickness"];
            params.m_NoOfScrews = fracture_plate_item["no_of_screws"];
            params.m_Type = (fracture_plate_item["plate_type"] == 0) ? STRAIGHT :  PRE_CONTURED;
            params.m_ScrewParamters.m_shaftDiameter = screw_item["shaft_diameter"];
            params.m_ScrewParamters.m_ShaftLength  = screw_item["shaft_length"];
            params.m_ScrewParamters.m_ThreadPitch = screw_item["thread_pitch"];
            params.m_ScrewParamters.m_ThreadDepth = screw_item["thread_depth"];
            params.m_ScrewParamters.m_HeadDiameter = screw_item["head_diameter"];
            params.m_ScrewParamters.m_HeadHeight = screw_item["head_height"];
        } 
        catch (json::exception& e) 
        {
           std::cout<<"Error:"<<e.what();
        }

        return params;
    }

    InputProcessor::InputProcessor()noexcept = default ;

    InputProcessor& InputProcessor::getShared()
    {
        if(mp_shared)
        {
            mp_shared.reset(new InputProcessor());
        }
        return *mp_shared;
    }

    FracturePlateParameters InputProcessor::ProcessParams(const std::string& json_string)
    {
        FracturePlateParameters params;
        try
        {
            auto root = json::parse(json_string);
            params = buildFromJson(root);
        }
        catch (const json::parse_error& e)
        {
            std::cout << e.what() << std::endl;
        }
        return params;
    }

}

