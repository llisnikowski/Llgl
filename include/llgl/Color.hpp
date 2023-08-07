#pragma once 
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

namespace llgl {

class Color
{
public:
    constexpr Color(float r=0, float g=0, float b=0);

    constexpr static Color white();
    constexpr static Color black();
    constexpr static Color red();
    constexpr static Color green();
    constexpr static Color blue();

    static constexpr std::size_t argsNumber();
    static constexpr GLenum argsType();
    static std::string getName();

    float r;
    float g;
    float b;
};


//-----------------------

constexpr Color::Color(float r, float g, float b)
:r{r}, g{g}, b{b}
{}

constexpr Color Color::white(){return Color(1.0f, 1.0f, 1.0f);}
constexpr Color Color::black(){return Color(0.0f, 0.0f, 0.0f);}
constexpr Color Color::red(){return Color(1.0f, 0.0f, 0.0f);}
constexpr Color Color::green(){return Color(0.0f, 1.0f, 0.0f);}
constexpr Color Color::blue(){return Color(0.0f, 0.0f, 1.0f);}


constexpr std::size_t Color::argsNumber()
{
    return sizeof(Color) / sizeof(float);
}

constexpr GLenum Color::argsType()
{
    return GL_FLOAT;
}


} // namespace llgl

constexpr bool operator==(llgl::Color rhs, llgl::Color lhs)
{
	return rhs.r == lhs.r && rhs.g == lhs.g
		&& rhs.b == lhs.b;
}
