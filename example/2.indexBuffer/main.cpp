#include <iostream>
#include "llgl/Llgl.hpp"
#include "llgl/Object.hpp"
#include "llgl/Position2d.hpp"
#include "llgl/Color.hpp"
#include "llgl/Shaders.hpp"
#include "llgl/Pipeline.hpp"
#include "llgl/IndexBuffer.hpp"
#include <vector>
#include <tuple>

int main(int argc, char *argv[])
{
    llgl::Llgl llgl{"Hello World", {800, 600}};
    llgl.init();
    llgl.setBackgroundColor(llgl::Color{0.2, 0.4, 0.8});

    auto object = std::make_shared<llgl::Object<llgl::Position2d, llgl::Color>>(
        std::vector<std::tuple<llgl::Position2d, llgl::Color>>{
            {{-0.7, -0.7}, {1.0, 0.0, 0.0}},
            {{0.7, -0.7}, {0.0, 1.0, 0.0}},
            {{0.7, 0.7}, {0.0f, 0.0f, 1.0f}},
            {{-0.7, 0.7}, {1.0f, 1.0f, 0.0f}}
        }
    );

    auto pipeline = std::make_shared<llgl::Pipeline>();
    auto shaders = std::make_shared<llgl::Shaders>();
    if(!shaders->loadVertex("./../vs.vert")) return 1;
    if(!shaders->loadFragment("./../fs.frag")) return 2;
    pipeline->setShaders(shaders);
    object->setPipeline(pipeline);


    //  3--2
    //  | /|
    //  |/ |
    //  0--1
    auto indexBuffer = std::make_unique<llgl::IndexBuffer<uint8_t>>(
        std::vector<uint8_t>{
            0, 1, 2,
            0, 2, 3
        }
    );

    object->setIndexBuffer(std::move(indexBuffer));

    llgl.addObject(object);

    llgl.run();
    return 0;
}

