#include "llgl/Shaders.hpp"
#include <fstream>

namespace llgl
{


Shaders::Shaders()
{
}

Shaders::~Shaders()
{
	if(this->vertexId) glDeleteProgram(this->vertexId);
	if(this->fragmentId) glDeleteProgram(this->fragmentId);
}

bool Shaders::loadVertex(std::string filename)
{
	std::string shader = loadFile(filename);
	if(shader.empty()) return false;

	vertexId = compile(shader.c_str(), GL_VERTEX_SHADER);
	if(vertexId == 0) return false;
    
	return true;
}

bool Shaders::loadFragment(std::string filename)
{
	std::string shader = loadFile(filename);
	if(shader.empty()) return false;

	fragmentId = compile(shader.c_str(), GL_FRAGMENT_SHADER);
	if(fragmentId == 0) return false;

	return true;
}


std::string Shaders::loadFile(const std::string &filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::in);
	if(file.is_open() == false) return {};
    const size_t fileLength = file.tellg();
    file.seekg(0);

    std::string shader;
    shader.resize(fileLength);

    file.read(&shader.front(), fileLength);

    return shader;
}

uint32_t Shaders::compile(const std::string &shader, GLenum stage)
{
	const char *shaderChar = shader.c_str();
	GLuint shdr = glCreateShaderProgramv(stage, 1, &shaderChar);

    return shdr;
}

uint32_t Shaders::getVertex()
{
	return this->vertexId;
}

uint32_t Shaders::getFragment()
{
	return this->fragmentId;
}

} // llgl