#include "llgl/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

namespace llgl
{

Texture::Texture()
{

}

Texture::~Texture()
{
    if(this->textureId) glDeleteTextures(1, &this->textureId);
}

bool Texture::loadTexture(std::string filename, bool alpha)
{
    int width, height, channels;
    unsigned char* pix = stbi_load(filename.c_str(), &width, &height, &channels, alpha ? 4 : 3);

    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    float border[4]{ 1.f, 0.f, 0.f, 1.f };
    glTextureParameterfv(textureId, GL_TEXTURE_BORDER_COLOR, border);
    glTextureStorage2D(textureId, std::floor(std::log2(std::max(width, height))), alpha ? GL_RGBA8 : GL_RGB8, width, height);
    glTextureSubImage2D(textureId, 0, 0, 0, width, height, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pix);
    glGenerateTextureMipmap(textureId);

    stbi_image_free(pix);
    return true;
}

bool Texture::bind(uint32_t nr)
{
    glBindTextureUnit(nr, this->textureId);
    return true;
}

} // namespace llgl

