#include "llgl/Window.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

Window::Window(std::string name, Size size)
:name{std::move(name)}, size{size}, window{nullptr}
{
}

bool Window::init()
{
    this->window = glfwCreateWindow(size.width, size.height, name.c_str(), nullptr, nullptr);
    if(this->window == nullptr) return false;

    glfwMakeContextCurrent(this->window);
    
    return true;
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
