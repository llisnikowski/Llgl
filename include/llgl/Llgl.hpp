#pragma once
#include "llgl/Window.hpp"
#include <memory>
#include <vector>
#include <functional>

namespace llgl
{
class ObjectBase;
class UniformBase;


struct TickInfo
{
	float currentTimePoint;
	float deltaTime;
};


class Llgl : public Window
{
public:
    using TickUpdateFunc = std::function<void(const TickInfo& tickInfo)>;

    Llgl(std::string name, Size size);
    Llgl();
    ~Llgl();

    bool init();
    void run();

    void addObject(std::shared_ptr<ObjectBase> object);

    void addTickUpdateFunc(TickUpdateFunc func);

private:

    bool glfwInit();
    bool loadGlad();
    
    void updateTickFuncs(float runTime, float deltaTime);

    std::vector<std::weak_ptr<ObjectBase>> objects;
    std::vector<TickUpdateFunc> tickUpdateFunctions;

};

} // namespace llgl
