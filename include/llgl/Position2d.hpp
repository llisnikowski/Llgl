#pragma once 
#include <initializer_list>
#include <utility>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl {

class Position2d
{
public:
    constexpr Position2d(float x=0, float y=0);

    static constexpr std::size_t argsNumber();
    static constexpr GLenum argsType();
    static constexpr std::size_t argsFullSize();

    float x;
    float y;
};

//--------------

constexpr Position2d::Position2d(float x, float y)
:x{x}, y{y}
{}

} // namespace llgl

constexpr bool operator==(llgl::Position2d lhs, llgl::Position2d rhs);



constexpr bool operator==(llgl::Position2d lhs, llgl::Position2d rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

