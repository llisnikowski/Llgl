#include <gtest/gtest.h>
#include "llgl/Utils.hpp"

TEST(Utils_test, getGlType)
{
	EXPECT_EQ(llgl::getGlType<float>(), GL_FLOAT);
	EXPECT_EQ(llgl::getGlType<int>(), GL_INT);
	EXPECT_EQ(llgl::getGlType<unsigned int>(), GL_UNSIGNED_INT);
}

struct MockClass
{
	int a;
	int b;
	int c;
};

TEST(Utils_test, offsetOf)
{
	EXPECT_EQ(llgl::offsetOf(&MockClass::a), 0);
	EXPECT_EQ(llgl::offsetOf(&MockClass::b), sizeof(int));
	EXPECT_EQ(llgl::offsetOf(&MockClass::c), sizeof(int)*2);
}




