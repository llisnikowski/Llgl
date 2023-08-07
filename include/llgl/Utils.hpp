#pragma once
#include <stdint.h>
#include <tuple>
#include <type_traits>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{


template<typename T, typename U> 
constexpr std::size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

template <typename T, std::size_t I>
constexpr std::size_t offsetOf()
{
    return (char*)&std::get<I>(*(T*)nullptr) - (char*)nullptr;
}

template <typename T>
constexpr GLenum getGlType()
{
	if constexpr (std::is_same_v<T, float>) return GL_FLOAT;
	if constexpr (std::is_same_v<T, int>) return GL_INT;
	if constexpr (std::is_same_v<T, unsigned int>) return GL_UNSIGNED_INT;
}

}