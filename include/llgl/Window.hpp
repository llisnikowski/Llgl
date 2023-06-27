#pragma once
#include <string>
#include "llgl/Size.hpp"


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

private:
    std::string name;
    Size size;

};

} // namespace llgl
