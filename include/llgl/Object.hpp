#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

template <typename T>
class Object
{
public:
    Object();
    virtual ~Object();

    uint32_t getVao();

private:
    uint32_t vao;
};


//----------------------

template <typename T>
Object<T>::Object()
{
	glCreateBuffers(1, &this->vao);
}

template <typename T>
Object<T>::~Object()
{
	glDeleteVertexArrays(1, &this->vao);
}

template <typename T>
uint32_t Object<T>::getVao()
{
	return this->vao;
}

} // namespace llgl
