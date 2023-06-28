 #include "llgl/Color.hpp"

namespace llgl {

Color::Color(float r, float g, float b, float alpha)
:r{r}, g{g}, b{b}, alpha{alpha}
{}

Color Color::white(){return Color(1.0f, 1.0f, 1.0f);}
Color Color::black(){return Color(0.0f, 0.0f, 0.0f);}
Color Color::red(){return Color(1.0f, 0.0f, 0.0f);}
Color Color::green(){return Color(0.0f, 1.0f, 0.0f);}
Color Color::blue(){return Color(0.0f, 0.0f, 1.0f);}

} // namespace llgl

bool operator==(llgl::Color rhs, llgl::Color lhs)
{
	return rhs.r == lhs.r && rhs.g == lhs.g
		&& rhs.b == lhs.b && rhs.alpha == lhs.alpha;
}

