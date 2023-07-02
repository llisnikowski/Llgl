#pragma once 
#include "llgl/Point2d.hpp"
#include "llgl/Attribute.hpp"

namespace llgl {

class Triangle2d
{
public:
    Triangle2d(Point2d point1, Point2d point2, Point2d point3);
    virtual ~Triangle2d() = default;

    Point2d *getArray();
    std::size_t arraySize();

    AttributesList getAttributeList();

protected:
    Point2d points[3];
};


} // namespace llgl
