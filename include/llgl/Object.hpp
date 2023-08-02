#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include "llgl/VertexBuffor.hpp"

namespace llgl
{

class ObjectBase
{
public:
    virtual void draw() = 0;
};

template <typename ...Ts>
class Object : public ObjectBase
{
public:
    Object(std::vector<std::tuple<Ts...>> ts);
    virtual ~Object();

    uint32_t getVao();
    uint32_t getVbo();

    void draw() override;

private:

    uint32_t vao{};
    VertexBuffor<Ts...> vertexBuffer;
};


//----------------------

template <typename ...Ts>
Object<Ts...>::Object(std::vector<std::tuple<Ts...>> ts)
:vertexBuffer{std::move(ts)}
{
	glCreateVertexArrays(1, &this->vao);

    this->vertexBuffer.init(this->vao);
}

template <typename ...Ts>
Object<Ts...>::~Object()
{
	glDeleteVertexArrays(1, &this->vao);
}

template <typename ...Ts>
uint32_t Object<Ts...>::getVao()
{
	return this->vao;
}

template <typename ...Ts>
uint32_t Object<Ts...>::getVbo()
{
	return this->vertexBuffer.getVbo();
}

template <typename ...Ts>
void Object<Ts...>::draw()
{
	
}


} // namespace llgl
