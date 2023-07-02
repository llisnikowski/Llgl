#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/Attribute.hpp"

namespace llgl
{

template <typename T>
class Object
{
public:
    Object(T buffor);
    virtual ~Object();

    uint32_t getVao();
    uint32_t getVbo();

private:
    uint32_t vao{};
    uint32_t vbo{};

    T buffor;
};


//----------------------

template <typename T>
Object<T>::Object(T buffor)
:buffor{buffor}
{
	glCreateVertexArrays(1, &this->vao);

	glCreateBuffers(1, &this->vbo);
    glNamedBufferStorage(vbo, buffor.arraySize(), buffor.getArray(), 0);

    AttributesList attributes = buffor.getAttributeList();
    for(uint32_t i = 0; i < attributes.size(); i++){
        auto &att = attributes[i];
        glEnableVertexArrayAttrib(this->vao, i);
        glVertexArrayAttribFormat(this->vao, i, att.number
        , static_cast<GLenum>(att.type), GL_FALSE, 0);
        glVertexArrayVertexBuffer(vao, i, vbo, att.offset, att.stride);
        glVertexArrayAttribBinding(vao, i, i);
    }
}

template <typename T>
Object<T>::~Object()
{
    glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}

template <typename T>
uint32_t Object<T>::getVao()
{
	return this->vao;
}

template <typename T>
uint32_t Object<T>::getVbo()
{
	return this->vbo;
}

} // namespace llgl
