#include <gtest/gtest.h>
#include <llgl/Llgl.hpp>
#include <llgl/Object.hpp>
#include <llgl/Attributes.hpp>

class AttributeMock
{
public:
	static constexpr std::size_t argsNumber();
    static constexpr GLenum argsType();
	static std::string getName();
	int i[3];
};

constexpr std::size_t AttributeMock::argsNumber()
{
	return sizeof(AttributeMock) / sizeof(int);
}
constexpr GLenum AttributeMock::argsType()
{
	return GL_INT;
}
std::string AttributeMock::getName()
{
	return "AttributeMock";
}

class Object_test : public ::testing::Test
{
public:
	Object_test()
		:llgl{"", {1, 1}}
	{
    	this->llgl.init();
	}

	llgl::Llgl llgl;
};

TEST_F(Object_test, MultiObject)
{
	llgl::Object<llgl::Attributes<AttributeMock>> object1{{{AttributeMock{}}}};
	llgl::Object<llgl::Attributes<AttributeMock>> object2{{{AttributeMock{}}}};
	EXPECT_NE(object1.getVao(), object2.getVao());
	EXPECT_NE(object1.getVbo(), object2.getVbo());
}

