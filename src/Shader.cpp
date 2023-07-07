#include "llgl/Shader.hpp"

namespace llgl
{

Shader::Shader(std::string name)
:name{name}
{
}

std::string Shader::getName()
{
	return name;
}

std::string Shader::getInstruction()
{
	return "";
}




} // namespace llgl