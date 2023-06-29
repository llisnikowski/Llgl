#include <gtest/gtest.h>
#include "llgl/Color.hpp"

TEST(Color_test, EmptyConstructor)
{
	llgl::Color color;

	EXPECT_FLOAT_EQ(color.r, 0);
	EXPECT_FLOAT_EQ(color.g, 0);
	EXPECT_FLOAT_EQ(color.b, 0);
	EXPECT_FLOAT_EQ(color.alpha, 1);
}

TEST(Color_test, floatConstructor)
{
	llgl::Color color{0.4f, 0.2f, 0.8f, 0.9f};

	EXPECT_FLOAT_EQ(color.r, 0.4);
	EXPECT_FLOAT_EQ(color.g, 0.2);
	EXPECT_FLOAT_EQ(color.b, 0.8);
	EXPECT_FLOAT_EQ(color.alpha, 0.9);
	EXPECT_TRUE((color == llgl::Color{0.4f, 0.2f, 0.8f, 0.9f}));
}

