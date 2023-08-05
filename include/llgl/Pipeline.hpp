#pragma once
#include <memory>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{
class Shaders;

class Pipeline
{
public:
	Pipeline();
	~Pipeline();

	void setShaders(std::shared_ptr<Shaders> shaders);
	void bind();

private:
	void setShader(uint32_t shaderId, GLbitfield stages);

	uint32_t id{};
};


} // namespace llgl
