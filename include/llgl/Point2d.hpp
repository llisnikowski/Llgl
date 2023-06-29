#pragma once 
#include <initializer_list>
#include <utility>

namespace llgl {

class Point2d
{
public:
    constexpr Point2d(float x=0, float y=0);

    float x;
    float y;
};

//--------------

constexpr Point2d::Point2d(float x, float y)
:x{x}, y{y}
{}

} // namespace llgl

constexpr bool operator==(llgl::Point2d lhs, llgl::Point2d rhs);



constexpr bool operator==(llgl::Point2d lhs, llgl::Point2d rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

