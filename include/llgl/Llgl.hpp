#pragma once
#include "llgl/Window.hpp"
#include <memory>
#include <vector>

namespace llgl
{
class ObjectBase;

class Llgl : public Window
{
public:
    Llgl(std::string name, Size size);
    Llgl();
    ~Llgl();

    bool init();
    void run();

    void addObject(std::shared_ptr<ObjectBase> object);

private:
    bool glfwInit();
    bool loadGlad();

    std::vector<std::weak_ptr<ObjectBase>> objects;

};

} // namespace llgl
