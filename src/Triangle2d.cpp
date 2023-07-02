#include "llgl/Triangle2d.hpp"


namespace llgl {

Triangle2d::Triangle2d(Point2d point1, Point2d point2, Point2d point3)
:points{point1, point2, point3}
{}

Point2d *Triangle2d::getArray()
{
	return this->points;
}

std::size_t Triangle2d::arraySize()
{
	return sizeof(Point2d) * 3;
}

AttributesList Triangle2d::getAttributeList()
{
	return {{Type::FLOAT, 2/*(x,y)*/, 0, sizeof(float)*2/*(x,y)*/}};
}

} // namespace llgl
