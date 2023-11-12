#pragma once
#include <cstdint>
#include <string>

namespace llgl
{

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadTexture(std::string filename, bool alpha);
    bool bind(uint32_t nr);

private:
    uint32_t textureId{};
};



} // namespace llgl


