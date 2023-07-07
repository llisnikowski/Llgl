#include <gtest/gtest.h>
#include "llgl/Shader.hpp"

class Shader_Mock : public llgl::Shader
{
public:
	Shader_Mock(std::string name)
	:llgl::Shader{name}
	{}

	std::string getInstruction() override {return "mock";}
};

TEST(Shader_test, Constructor)
{
	llgl::Shader shader{"helloWorld"};

	EXPECT_STREQ(shader.getName().c_str(), "helloWorld");
	EXPECT_STREQ(shader.getInstruction().c_str(), "");
}

TEST(Shader_test, getInstruction)
{
	Shader_Mock shader{"helloWorld"};

	EXPECT_STREQ(shader.getInstruction().c_str(), "mock");
}

