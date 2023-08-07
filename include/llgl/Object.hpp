#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include "llgl/VertexBuffor.hpp"
#include "llgl/ObjectBase.hpp"

namespace llgl
{

template <typename ...Ts>
class Object : public ObjectBase
{
public:
    Object(std::vector<std::tuple<Ts...>> ts);
    virtual ~Object();

    uint32_t getVbo();

    void draw() override;

private:

    VertexBuffor<Ts...> vertexBuffer;
};


//----------------------

template <typename ...Ts>
Object<Ts...>::Object(std::vector<std::tuple<Ts...>> ts)
:vertexBuffer{std::move(ts)}
{
    this->vertexBuffer.init(this->vao);
}

template <typename ...Ts>
Object<Ts...>::~Object()
{
}


template <typename ...Ts>
uint32_t Object<Ts...>::getVbo()
{
	return this->vertexBuffer.getVbo();
}

template <typename ...Ts>
void Object<Ts...>::draw()
{
    this->bind();
	glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.bufforLength());
}


} // namespace llgl
