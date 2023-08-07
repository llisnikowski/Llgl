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
class VertexBuffor
{
public:
	using AttribsTypes = std::tuple<Ts...>;
    using Buffor = std::vector<AttribsTypes>;

	VertexBuffor(Buffor &&buffor);
	~VertexBuffor();

	void init(uint32_t vao);
	uint32_t getVbo();
	static std::size_t attiributesSize();
	static std::size_t attiributesNumber();
	std::size_t bufforLength();
	std::size_t bufforSize();
	void *bufforBegin();

private:
	template <std::size_t I = 0>
    void addAttributes(uint32_t vao);

    uint32_t vbo{};
	Buffor buffor;
};


//--------------------------

template <typename... Ts>
VertexBuffor<Ts...>::VertexBuffor(Buffor &&buffor)
:buffor{std::move(buffor)}
{
}

template <typename... Ts>
VertexBuffor<Ts...>::~VertexBuffor()
{
    if(this->vbo) glDeleteBuffers(1, &this->vbo);
	this->vbo = 0;
}

template <typename... Ts>
void VertexBuffor<Ts...>::init(uint32_t vao)
{
	glCreateBuffers(1, &this->vbo);
    glNamedBufferStorage(this->vbo, this->bufforSize(), this->bufforBegin(), 0);
	this->addAttributes<0>(vao);
}

template <typename... Ts>
uint32_t VertexBuffor<Ts...>::getVbo()
{
	return this->vbo;
}

template <typename... Ts>
template <std::size_t I>
void VertexBuffor<Ts...>::addAttributes(uint32_t vao)
{
	using AttribTyp = std::tuple_element_t<I, AttribsTypes>;
    glEnableVertexArrayAttrib(vao, I);
    glVertexArrayAttribFormat(vao, I, AttribTyp::argsNumber()
    , AttribTyp::argsType(), GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, I, this->vbo, llgl::offsetOf<AttribsTypes, I>(), sizeof(AttribsTypes));
    glVertexArrayAttribBinding(vao, I, I);

    if constexpr(I + 1 < std::tuple_size<AttribsTypes>()) this->addAttributes<I+1>(vao);
}

template <typename... Ts>
std::size_t VertexBuffor<Ts...>::attiributesSize()
{
	return sizeof(AttribsTypes);
}

template <typename... Ts>
std::size_t VertexBuffor<Ts...>::attiributesNumber()
{
	return sizeof...(Ts);
}

template <typename... Ts>
std::size_t VertexBuffor<Ts...>::bufforLength()
{
	return buffor.size();
}

template <typename... Ts>
std::size_t VertexBuffor<Ts...>::bufforSize()
{
	return this->attiributesSize() * this->bufforLength();
}

template <typename... Ts>
void *VertexBuffor<Ts...>::bufforBegin()
{
	return (void*)buffor.data();
}


} // namespace llgl
