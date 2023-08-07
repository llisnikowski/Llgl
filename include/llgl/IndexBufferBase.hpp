#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

class IndexBufferBase
{
public:
	IndexBufferBase();
	~IndexBufferBase();

	uint32_t getId();
	virtual GLenum getType() = 0;
	virtual uint32_t getLength() = 0;

protected:
	uint32_t id{};
};


} // namespace llgl
