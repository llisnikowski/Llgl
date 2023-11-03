#include <iostream>
#include "llgl/Llgl.hpp"
#include "llgl/Object.hpp"
#include "llgl/Position2d.hpp"
#include "llgl/Color.hpp"
#include "llgl/Shaders.hpp"
#include "llgl/Pipeline.hpp"
#include "llgl/IndexBuffer.hpp"
#include "llgl/Uniform.hpp"
#include <vector>
#include <tuple>
#include <chrono>
#include <cmath>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;
using Duration = std::chrono::duration<float, std::ratio<1, 1>>;


int main(int argc, char *argv[])
{
    llgl::Llgl llgl{"Hello World", {800, 600}};
    llgl.init();
    llgl.setBackgroundColor(llgl::Color{0.2, 0.4, 0.8});

    auto object = std::make_shared<llgl::Object<llgl::Position2d, llgl::Color>>(
        std::vector<std::tuple<llgl::Position2d, llgl::Color>>{
            {{-0.3, -0.3}, {1.0, 0.0, 0.0}},
            {{0.3, -0.3}, {0.0, 1.0, 0.0}},
            {{0.3, 0.3}, {0.0f, 0.0f, 1.0f}}
        }
    );

    auto pipeline = std::make_shared<llgl::Pipeline>();
    auto shaders = std::make_shared<llgl::Shaders>();
    if(!shaders->loadVertex("./../vs.vert")) return 1;
    if(!shaders->loadFragment("./../fs.frag")) return 2;
    pipeline->setShaders(shaders);
    object->setPipeline(pipeline);

    {       // --- | Uniforms | ---
        // static
        auto constOffsetUniform = std::make_shared<llgl::Uniform<float, 2>>(
            std::array<float, 2>{-0.2, 0.4}
        );
        shaders->addUniform(constOffsetUniform);

        // dynamic
        auto dynamicOffsetUniform = std::make_shared<llgl::Uniform<float, 1>>(
            std::array<float, 1>{0}
        );
        shaders->addUniform(dynamicOffsetUniform);

        constexpr float radius = 0.3f;
        constexpr float speed = 2;
        llgl.addTickUpdateFunc([dynamicOffsetUniform, radius, speed](const llgl::TickInfo &timeInfo){
            dynamicOffsetUniform->set({std::cos(timeInfo.currentTimePoint * speed) * radius});
        });

    }

    llgl.addObject(object);

    llgl.run();
    return 0;
}

