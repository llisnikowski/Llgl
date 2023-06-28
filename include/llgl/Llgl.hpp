#pragma once
#include "llgl/Window.hpp"

namespace llgl
{

class Llgl : public Window
{
public:
    Llgl(std::string name, Size size);
    ~Llgl();

    bool init();
    void run();

private:
    bool glfwInit();
    bool loadGlad();

};

} // namespace llgl
