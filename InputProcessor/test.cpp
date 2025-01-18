
#include "InputProcessor.hpp"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


int main()
{
   Input::InputProcessor& p = Input::InputProcessor::getShared();
   
   auto f = R"(
    {
        "fracture_plate": {
            "width":  8,
            "length": 7,
            "thickness": 0.5,
            "plate_type": 0,
            "screw_params" : {
            "shaft_diameter":0.1,
            "shaft_length": 0.8,
            "thread_pitch": 0.3
            },
            "contours":[]
        }
    }
    )";

    auto params = p.ProcessParams(f);

    return 0;
}