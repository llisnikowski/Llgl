#pragma once
#include <stdint.h>

namespace llgl
{

class Object
{
public:
    Object();
    virtual ~Object();

    uint32_t getVao();

private:
    uint32_t vao;
};

} // namespace llgl
