#pragma once 
#include <stdint.h>

namespace llgl {

class Color
{
public:
    explicit Color(float r=0, float g=0, float b=0, float alpha=1.0);

    static Color white();
    static Color black();
    static Color red();
    static Color green();
    static Color blue();

    float r;
    float g;
    float b;
    float alpha;
};

} // namespace llgl

bool operator==(llgl::Color rhs, llgl::Color lhs);
