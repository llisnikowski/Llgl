#include <gtest/gtest.h>
#include <llgl/Llgl.hpp>
#include <llgl/Object.hpp>
#include <llgl/Attribute.hpp>

class BufforMock
{
public:
	void *getArray(){return nullptr;}
    std::size_t arraySize(){return 0;};

	llgl::AttributesList getAttributeList(){return {};}
};

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
	// llgl::Object<BufforMock> object1{BufforMock{}};
	// llgl::Object<BufforMock> object2{BufforMock{}};
	// EXPECT_NE(object1.getVao(), object2.getVao());
	// EXPECT_NE(object1.getVbo(), object2.getVbo());
}

TEST_F(Object_test, vaoSize)
{
	// EXPECT_EQ(sizeof(decltype(llgl::Object<BufforMock>(BufforMock{}) 
	// 	.getVbo())), 4);
}

TEST_F(Object_test, vboSize)
{
	// EXPECT_EQ(sizeof(decltype(llgl::Object<BufforMock>(BufforMock{}) 
	// 	.getVbo())), 4);
}