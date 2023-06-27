#pragma once 
#include <cstddef>

namespace llgl {

struct Size
{
    Size(int width, int height);
    explicit Size(int size);
    Size();

    int width;
    int height;
};

} // namespace llgl

bool operator==(llgl::Size rhs, llgl::Size lhs);

