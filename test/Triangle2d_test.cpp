#include <gtest/gtest.h>
#include <llgl/Llgl.hpp>
#include <llgl/Object.hpp>
#include <llgl/Triangle2d.hpp>

class Triangle2d_test : public ::testing::Test
{
public:
	Triangle2d_test()
	:triangle{
		{1.0, 0.8},
		{-0.5, 0.4},
		{0.3, -0.2}
	}
	{
	}

	llgl::Triangle2d triangle;
};

TEST_F(Triangle2d_test, GetArray)
{
	EXPECT_TRUE((triangle.getArray()[0] == llgl::Point2d{1.0, 0.8}));
	EXPECT_TRUE((triangle.getArray()[1] == llgl::Point2d{-0.5, 0.4}));
	EXPECT_TRUE((triangle.getArray()[2] == llgl::Point2d{0.3, -0.2}));
}

TEST_F(Triangle2d_test, SizeArray)
{
	EXPECT_EQ(triangle.arraySize(), sizeof(llgl::Point2d)*3);
}

TEST_F(Triangle2d_test, Attributes)
{
	EXPECT_EQ(triangle.getAttributeList().size(), 1);
	EXPECT_EQ(triangle.getAttributeList()[0].type, llgl::Type::FLOAT);
	EXPECT_EQ(triangle.getAttributeList()[0].number, 2);
	EXPECT_EQ(triangle.getAttributeList()[0].offset, 0);
	EXPECT_EQ(triangle.getAttributeList()[0].stride, sizeof(float)*2);
}
