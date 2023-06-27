#include "llgl/Size.hpp"

namespace llgl {

Size::Size(int width, int height)
:width{width}, height{height}
{}

Size::Size(int size)
:width{size}, height{size}
{}

Size::Size()
:width{0}, height{0}
{}


} // namespace llgl

bool operator==(llgl::Size rhs, llgl::Size lhs)
{
	return rhs.width == lhs.width && rhs.height == lhs.height;
}

