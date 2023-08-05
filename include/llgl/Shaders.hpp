#pragma once
#include <stdint.h>
#include <string>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

class Shaders
{
public:
	Shaders();
	~Shaders();

	bool loadVertex(std::string filename);
	bool loadFragment(std::string filename);

	uint32_t getVertex();
	uint32_t getFragment();

private:
	std::string loadFile(const std::string &filename);
	uint32_t compile(const std::string &shader, GLenum stage);

	uint32_t vertexId{};
	uint32_t fragmentId{};
};


} // namespace llgl

