#include <gtest/gtest.h>
#include "llgl/Color.hpp"

TEST(Color_test, EmptyConstructor)
{
	llgl::Color color;

	EXPECT_FLOAT_EQ(color.r, 0);
	EXPECT_FLOAT_EQ(color.g, 0);
	EXPECT_FLOAT_EQ(color.b, 0);
}

TEST(Color_test, floatConstructor)
{
	llgl::Color color{0.4f, 0.2f, 0.8f};

	EXPECT_FLOAT_EQ(color.r, 0.4);
	EXPECT_FLOAT_EQ(color.g, 0.2);
	EXPECT_FLOAT_EQ(color.b, 0.8);
	EXPECT_TRUE((color == llgl::Color{0.4f, 0.2f, 0.8f}));
}

TEST(Color_test, attributInfo)
{
	EXPECT_EQ(llgl::Color::argsNumber(), 3);
	EXPECT_EQ(llgl::Color::argsType(), GL_FLOAT);
	EXPECT_STREQ(llgl::Color::getName().c_str(), "color");
}

TEST(Color_test, colors)
{
	EXPECT_TRUE((llgl::Color::white() == llgl::Color{1, 1, 1}));
	EXPECT_TRUE((llgl::Color::black() == llgl::Color{}));
	EXPECT_TRUE((llgl::Color::red() == llgl::Color{1, 0, 0}));
	EXPECT_TRUE((llgl::Color::green() == llgl::Color{0, 1, 0}));
	EXPECT_TRUE((llgl::Color::blue() == llgl::Color{0, 0, 1}));
}