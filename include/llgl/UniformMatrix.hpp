#pragma once
#include "llgl/UniformBase.hpp"
#include <cstddef>
#include <array>
#include <type_traits>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <functional>
#include "llgl/Mat.hpp"

namespace llgl
{

template <std::size_t W=4, std::size_t H=4>
class UniformMatrix : public UniformBase
{
public:
	static_assert(W >= 2 && W <= 4 && H >= 2 && H <= 4);
	using GlFunction = void(*)(uint32_t shader, int location, int count, GLboolean transpose, const float *matrix);

	UniformMatrix();
	UniformMatrix(Mat<W, H> matrix);

	void set(Mat<W, H> matrix);

protected:
	void update() override;
	void updateShaders(uint32_t shader, int location) override;

private:
	GlFunction getGlFunction();

	Mat<W, H> matrix;
};


template <std::size_t W, std::size_t H>
UniformMatrix<W, H>::UniformMatrix()
:matrix{1}
{
}

template <std::size_t W, std::size_t H>
UniformMatrix<W, H>::UniformMatrix(Mat<W, H> matrix)
:matrix{matrix}
{
}

template <std::size_t W, std::size_t H>
void UniformMatrix<W, H>::updateShaders(uint32_t shader, int location)
{
	auto glFun = getGlFunction();
	glFun(shader, location, 1, GL_FALSE, glm::value_ptr(this->matrix));
}

template <std::size_t W, std::size_t H>
auto UniformMatrix<W, H>::getGlFunction() -> GlFunction
{
	if constexpr (W == 2){
		if constexpr (H == 2)
			return glProgramUniformMatrix2fv;
		else if constexpr (H == 3)
			return glProgramUniformMatrix2x3fv;
		else if constexpr (H == 4)
			return glProgramUniformMatrix2x4fv;
	}
	if constexpr (W == 3){
		if constexpr (H == 2)
			return glProgramUniformMatrix3x2fv;
		else if constexpr (H == 3)
			return glProgramUniformMatrix3fv;
		else if constexpr (H == 4)
			return glProgramUniformMatrix3x4fv;
	}
	if constexpr (W == 4){
		if constexpr (H == 2)
			return glProgramUniformMatrix4x2fv;
		else if constexpr (H == 3)
			return glProgramUniformMatrix4x3fv;
		else if constexpr (H == 4)
			return glProgramUniformMatrix4fv;
	}
}

template <std::size_t W, std::size_t H>
void UniformMatrix<W, H>::update()
{
	updateAllShaders();
}

template <std::size_t W, std::size_t H>
void UniformMatrix<W, H>::set(Mat<W, H> matrix)
{
	this->matrix = std::move(matrix);
	updateAllShaders();
}


} // namespace llgl
