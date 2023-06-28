#pragma once
#include <string>
#include "llgl/Size.hpp"

struct GLFWwindow;

namespace llgl
{

class Window
{
public:
    Window(std::string name, Size size);
    virtual ~Window() = default;

    std::string getName() const;
    void setName(std::string name);
    Size getSize() const;
    void setSize(Size size);

protected:
    bool init();
    GLFWwindow* getWindow(){return this->window;}

private:
    std::string name;
    Size size;
    GLFWwindow* window;

};

} // namespace llgl
