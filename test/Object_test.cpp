#include <gtest/gtest.h>
#include <llgl/Llgl.hpp>
#include <llgl/Object.hpp>

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
	llgl::Object<int> object1;
	llgl::Object<int> object2;
	EXPECT_NE(object1.getVao(), object2.getVao());
}

TEST_F(Object_test, vaoSize)
{
	EXPECT_EQ(sizeof(decltype(llgl::Object<int>().getVao())), 4);
}