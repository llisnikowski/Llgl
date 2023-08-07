#include <iostream>
#include "llgl/Llgl.hpp"
#include "llgl/Object.hpp"
#include "llgl/Position2d.hpp"
#include "llgl/Color.hpp"
#include "llgl/Shaders.hpp"
#include "llgl/Pipeline.hpp"
#include <vector>
#include <tuple>

int main(int argc, char *argv[])
{
    llgl::Llgl llgl{"Hello World", {800, 600}};
    llgl.init();
    llgl.setBackgroundColor(llgl::Color{0.2, 0.4, 0.8});

    auto object = std::make_shared<llgl::Object<llgl::Position2d, llgl::Color>>(
        std::vector<std::tuple<llgl::Position2d, llgl::Color>>{
            {{-0.5, -0.5}, llgl::Color::red()},
            {{0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{0, 0.7}, {0.0f, 0.0f, 1.0f}}
        }
    );

    auto pipeline = std::make_shared<llgl::Pipeline>();
    auto shaders = std::make_shared<llgl::Shaders>();
    if(!shaders->loadVertex("./../vs.vert")) return 1;
    if(!shaders->loadFragment("./../fs.frag")) return 2;
    pipeline->setShaders(shaders);
    object->setPipeline(pipeline);

    object->bind();

    llgl.addObject(object);

    llgl.run();
    return 0;
}

