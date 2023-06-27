#include "llgl/Window.hpp"
#include <GLFW/glfw3.h>

namespace llgl
{

Window::Window(std::string name, Size size)
:name{std::move(name)}, size{size}
{
}

std::string Window::getName() const
{
    return this->name;
}

Size Window::getSize() const
{
    return this->size;
}

void Window::setSize(Size size)
{
    this->size = size;
}

void Window::setName(std::string name)
{
    this->name = name;
}

} // namespace llgl
