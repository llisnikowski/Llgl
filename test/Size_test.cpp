#include <gtest/gtest.h>
#include "llgl/Size.hpp"

TEST(Size_test, EmptyConstructor)
{
	llgl::Size size;

	EXPECT_EQ(size.width, 0);
	EXPECT_EQ(size.height, 0);
	EXPECT_TRUE((size == llgl::Size{0, 0}));
}

TEST(Size_test, SquareConstructor)
{
	llgl::Size size{123};

	EXPECT_EQ(size.width, 123);
	EXPECT_EQ(size.height, 123);
	EXPECT_TRUE((size == llgl::Size{123, 123}));
}

TEST(Size_test, RectangleConstructor)
{
	llgl::Size size{800, 500};

	EXPECT_EQ(size.width, 800);
	EXPECT_EQ(size.height, 500);
	EXPECT_TRUE((size == llgl::Size{800, 500}));
}
