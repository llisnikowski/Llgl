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

	uint32_t getId();
	void setShaders(std::shared_ptr<Shaders> shaders);
	void bind();

private:
	void setShader(uint32_t shaderId, GLbitfield stages);

	uint32_t id{};
	std::shared_ptr<Shaders> shaders{};
};


} // namespace llgl
