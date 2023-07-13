#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include "Attributes.hpp"

namespace llgl
{

template <typename Atribs>
class Object : public Atribs
{
public:
    Object(Atribs atribs);
    virtual ~Object();

    uint32_t getVao();
    uint32_t getVbo();

private:

    uint32_t vao{};
    uint32_t vbo{};
};


//----------------------

template <typename Atribs>
Object<Atribs>::Object(Atribs atribs)
:Atribs{std::move(atribs)}
{
	glCreateVertexArrays(1, &this->vao);

	glCreateBuffers(1, &this->vbo);
    glNamedBufferStorage(this->vbo, Atribs::fullSize(), Atribs::bufforBegin(), 0);

    Atribs::init(this->vao, this->vbo);
}

template <typename Atribs>
Object<Atribs>::~Object()
{
    glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}

template <typename Atribs>
uint32_t Object<Atribs>::getVao()
{
	return this->vao;
}

template <typename Atribs>
uint32_t Object<Atribs>::getVbo()
{
	return this->vbo;
}

} // namespace llgl
