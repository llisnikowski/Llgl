#pragma once
#include <string>

namespace llgl
{

class Shader
{
public:
	Shader(std::string name);

	std::string getName();
	virtual std::string getInstruction();

private:
	std::string name;
	
};


} // namespace llgl