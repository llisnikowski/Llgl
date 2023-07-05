#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/Attribute.hpp"
#include <vector>
#include <tuple>

namespace llgl
{

template <typename... Atribs>
class Object
{
public:
    using Attributes = std::tuple<Atribs...>;
    using AttributesList = std::vector<Attributes>;

    Object(AttributesList attributesList);
    virtual ~Object();

    uint32_t getVao();
    uint32_t getVbo();

private:
    template <std::size_t I = 0>
    void addAttributes();
    template <typename T, std::size_t Ii>
    std::size_t attributOffset();

    uint32_t vao{};
    uint32_t vbo{};

    AttributesList attributesList;
};


//----------------------

template <typename... Atribs>
Object<Atribs...>::Object(AttributesList attributesList)
:attributesList{std::move(attributesList)}
{
	glCreateVertexArrays(1, &this->vao);

	glCreateBuffers(1, &this->vbo);
    glNamedBufferStorage(this->vbo, this->attributesList.size() * sizeof(Attributes), this->attributesList.data(), 0);

    addAttributes();
}

template <typename... Atribs>
Object<Atribs...>::~Object()
{
    glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}

template <typename... Atribs>
template <std::size_t I>
void Object<Atribs...>::addAttributes()
{
    using AtribTyp = std::tuple_element_t<I, std::tuple<int, int>>;
    glEnableVertexArrayAttrib(this->vao, I);
    glVertexArrayAttribFormat(this->vao, I, AtribTyp::argsNumber()
    , AtribTyp::argsType(), GL_FALSE, 0);
    glVertexArrayVertexBuffer(this->vao, I, this->vbo, this->attributOffset<AtribTyp, I>, AtribTyp::argsFullSize());
    glVertexArrayAttribBinding(this->vao, I, I);

    if(I + 1 < std::tuple_size<Attributes>()) this->addAttributes<I+1>();
}


template <typename... Atribs>
template <typename T, std::size_t I>
std::size_t Object<Atribs...>::attributOffset()
{
    return (char*)std::get<I>((T*)nullptr) - (char*)nullptr;
}

template <typename... Atribs>
uint32_t Object<Atribs...>::getVao()
{
	return this->vao;
}

template <typename... Atribs>
uint32_t Object<Atribs...>::getVbo()
{
	return this->vbo;
}

} // namespace llgl
