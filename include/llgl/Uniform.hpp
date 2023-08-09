#pragma once
#include "llgl/UniformBase.hpp"
#include <cstddef>
#include <array>
#include <type_traits>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace llgl
{

template <typename T, std::size_t N>
class Uniform : public UniformBase
{
public:
	using GlFunction = void(*)(uint32_t shader, int location, int count, const T *value);
	using UpdateFunc = std::function<bool(std::array<T, N> &array)>;

	Uniform();
	Uniform(std::array<T, N> array);
	void setUpdateFunction(UpdateFunc updateFunct);
	void update() override;

protected:
	void updateShaders(uint32_t shader, int location) override;

private:
	GlFunction getGlFunction();

	std::array<T, N> array;
	UpdateFunc updateFunct{};
};


template <typename T, std::size_t N>
Uniform<T,N>::Uniform()
{
}

template <typename T, std::size_t N>
Uniform<T,N>::Uniform(std::array<T, N> array)
:array{array}
{
}

template <typename T, std::size_t N>
void Uniform<T,N>::updateShaders(uint32_t shader, int location)
{
	auto glFun = getGlFunction();
	glFun(shader, location, 1, (float*)this->array.data());
}

template <typename T, std::size_t N>
auto Uniform<T,N>::getGlFunction() -> GlFunction
{
	if constexpr (std::is_same_v<T, int32_t>){
		if constexpr (N == 1)
			return glProgramUniform1iv;
		else if constexpr (N == 2)
			return glProgramUniform2iv;
		else if constexpr (N == 3)
			return glProgramUniform3iv;
		else if constexpr (N == 4)
			return glProgramUniform4iv;
	}
	else if constexpr (std::is_same_v<T, uint32_t>){
		if constexpr (N == 1)
			return glProgramUniform1uiv;
		else if constexpr (N == 2)
			return glProgramUniform2uiv;
		else if constexpr (N == 3)
			return glProgramUniform3uiv;
		else if constexpr (N == 4)
			return glProgramUniform4uiv;
	}
	else if constexpr (std::is_same_v<T, float>){
		if constexpr (N == 1)
			return glProgramUniform1fv;
		else if constexpr (N == 2)
			return glProgramUniform2fv;
		else if constexpr (N == 3)
			return glProgramUniform3fv;
		else if constexpr (N == 4)
			return glProgramUniform4fv;
	}
}

template <typename T, std::size_t N>
void Uniform<T,N>::setUpdateFunction(UpdateFunc updateFunct)
{
	this->updateFunct = updateFunct;
}

template <typename T, std::size_t N>
void Uniform<T,N>::update()
{
	if(this->updateFunct == nullptr) return;
	if(this->updateFunct(array) == false) return;
	updateAllShaders();
}


} // namespace llgl
