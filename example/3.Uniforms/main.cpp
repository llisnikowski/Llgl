#include <iostream>
#include "llgl/Llgl.hpp"
#include "llgl/Object.hpp"
#include "llgl/Position2d.hpp"
#include "llgl/Color.hpp"
#include "llgl/Shaders.hpp"
#include "llgl/Pipeline.hpp"
#include "llgl/IndexBuffer.hpp"
#include "llgl/Uniform.hpp"
#include "llgl/UniformMatrix.hpp"
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

    auto object2 = std::make_shared<llgl::Object<llgl::Position2d, llgl::Color>>(
        std::vector<std::tuple<llgl::Position2d, llgl::Color>>{
            {{-0.3, -0.3}, {0.0, 1.0, 1.0}},
            {{0.3, -0.3}, {1.0, 0.0, 1.0}},
            {{0, 0.3}, {1.0f, 1.0f, 0.0f}}
        }
    );

    auto pipeline2 = std::make_shared<llgl::Pipeline>();
    auto shaders2 = std::make_shared<llgl::Shaders>();
    if(!shaders2->loadVertex("./../mat.vert")) return 1;
    if(!shaders2->loadFragment("./../fs.frag")) return 2;
    pipeline2->setShaders(shaders2);
    object2->setPipeline(pipeline2);

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
    {
            // --- | Matrix | ---
        constexpr float speed = 30;
        auto uniformMatrix = std::make_shared<llgl::UniformMatrix<4, 4>>();
        shaders2->addUniform(uniformMatrix);
        llgl.addTickUpdateFunc([uniformMatrix, speed](const llgl::TickInfo &timeInfo){
            llgl::Mat<4, 4> matrix{1.0f};
            matrix = llgl::rotate(matrix, llgl::radians(-timeInfo.currentTimePoint*speed), llgl::Vec<3>(0.f, 0.f, 1.f));
            matrix = llgl::translate(matrix, -llgl::Vec<3>(-0.5f, -0.5f, 0.f));
            uniformMatrix->set(matrix);
        });
    }

    llgl.addObject(object);
    llgl.addObject(object2);

    llgl.run();
    return 0;
}

