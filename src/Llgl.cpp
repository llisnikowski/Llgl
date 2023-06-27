#include "llgl/Llgl.hpp"
#include <GLFW/glfw3.h>

namespace llgl
{

Llgl::Llgl(std::string name, Size size)
:Window{std::move(name), size}
{
}

Llgl::~Llgl()
{
}

} // namespace llgl
