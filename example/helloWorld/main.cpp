#include <iostream>
#include "llgl/Llgl.hpp"
#include "llgl/Object.hpp"
#include "llgl/Position2d.hpp"
#include "llgl/Color.hpp"

int main(int argc, char *argv[])
{
    llgl::Llgl llgl{"Hello World", {800, 600}};
    llgl.init();
    llgl.setBackgroundColor(llgl::Color::blue());

    llgl::Object<llgl::Position2d, llgl::Color>({
        {{-0.5, -0.5}, llgl::Color::red()},
        {{0.5, -0.5}, {0.0, 1.0, 0.0}},
        {{0, 0.7}, {0, 0, 1}}
    });

    llgl.run();
    return 0;
}

