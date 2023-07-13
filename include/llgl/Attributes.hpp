#pragma once

#include <stdint.h>
#include <vector>
#include <tuple>
#include "llgl/Utils.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

template <typename... Ts>
class Attributes
{
public:
	using AttribsTypes = std::tuple<Ts...>;
    using AttribsList = std::vector<AttribsTypes>;

	Attributes(AttribsList attribsList);

	void init(uint32_t vao, uint32_t vbo);
	static std::size_t attributesSize();
	std::size_t attributesListLength();
	std::size_t fullSize();
	void *bufforBegin();

private:
	template <std::size_t I = 0>
    void addAttributes(uint32_t vao, uint32_t vbo);

	AttribsList attribsList;
};


//--------------------------

template <typename... Ts>
Attributes<Ts...>::Attributes(AttribsList attribsList)
:attribsList{std::move(attribsList)}
{
}

template <typename... Ts>
void Attributes<Ts...>::init(uint32_t vao, uint32_t vbo)
{
	this->addAttributes<0>(vao, vbo);
}

template <typename... Ts>
template <std::size_t I>
void Attributes<Ts...>::addAttributes(uint32_t vao, uint32_t vbo)
{
	using AttribTyp = std::tuple_element_t<I, AttribsTypes>;
    glEnableVertexArrayAttrib(vao, I);
    glVertexArrayAttribFormat(vao, I, AttribTyp::argsNumber()
    , AttribTyp::argsType(), GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, I, vbo, llgl::offsetOf<AttribsTypes, I>(), sizeof(AttribTyp));
    glVertexArrayAttribBinding(vao, I, I);

    if constexpr(I + 1 < std::tuple_size<AttribsTypes>()) this->addAttributes<I+1>();
}

template <typename... Ts>
std::size_t Attributes<Ts...>::attributesSize()
{
	return sizeof(AttribsTypes);
}

template <typename... Ts>
std::size_t Attributes<Ts...>::attributesListLength()
{
	return attribsList.size();
}

template <typename... Ts>
std::size_t Attributes<Ts...>::fullSize()
{
	return this->attributesSize() * this->attributesListLength();
}

template <typename... Ts>
void *Attributes<Ts...>::bufforBegin()
{
	return (void*)attribsList.data();
}


} // namespace llgl
