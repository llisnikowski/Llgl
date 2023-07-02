#pragma once 
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

namespace llgl
{

enum class Type
{
	NONE,
	FLOAT = GL_FLOAT
};

struct Attribute
{
	Type type;
	int32_t number;
	uint32_t offset;
	uint32_t stride;
};

using AttributesList = std::vector<Attribute>;


} // namespace llgl
