#pragma once
#include "llgl/Window.hpp"
#include <memory>
#include <vector>

namespace llgl
{
class ObjectBase;
class UniformBase;

class Llgl : public Window
{
public:
    Llgl(std::string name, Size size);
    Llgl();
    ~Llgl();

    bool init();
    void run();

    void addObject(std::shared_ptr<ObjectBase> object);
    void addToTickUpdater(std::shared_ptr<UniformBase> uniform);

private:
    bool glfwInit();
    bool loadGlad();

    std::vector<std::weak_ptr<ObjectBase>> objects;
    std::vector<std::weak_ptr<UniformBase>> updateTickUniforms;

};

} // namespace llgl
