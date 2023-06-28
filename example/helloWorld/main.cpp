#include <iostream>
#include "llgl/Llgl.hpp"

int main(int argc, char *argv[])
{
    llgl::Llgl llgl{"Hello World", {800, 600}};
    llgl.init();

    llgl.run();
    return 0;
}