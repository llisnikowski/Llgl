#include <gtest/gtest.h>
#include <llgl/Llgl.hpp>
#include <llgl/Object.hpp>
#include <llgl/Attribute.hpp>

class AttributeMock
{
public:
	static constexpr std::size_t argsNumber();
    static constexpr GLenum argsType();
	int i;
};

constexpr std::size_t AttributeMock::argsNumber()
{
	return sizeof(AttributeMock) / sizeof(int);
}
constexpr GLenum AttributeMock::argsType()
{
	return GL_INT;
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
	llgl::Object<AttributeMock> object1{{AttributeMock{}}};
	llgl::Object<AttributeMock> object2{{AttributeMock{}}};
	EXPECT_NE(object1.getVao(), object2.getVao());
	EXPECT_NE(object1.getVbo(), object2.getVbo());
}

TEST_F(Object_test, vaoSize)
{
	EXPECT_EQ(sizeof(decltype(llgl::Object<AttributeMock>({AttributeMock{}}) 
		.getVbo())), 4);
}

TEST_F(Object_test, vboSize)
{
	EXPECT_EQ(sizeof(decltype(llgl::Object<AttributeMock>({AttributeMock{}}) 
		.getVbo())), 4);
}