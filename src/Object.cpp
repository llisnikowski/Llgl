#include "llgl/Object.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

Object::Object()
{
	glCreateBuffers(1, &this->vao);
}

Object::~Object()
{
	glDeleteVertexArrays(1, &this->vao);
}

uint32_t Object::getVao()
{
	return this->vao;
}



} // namespace llgl
