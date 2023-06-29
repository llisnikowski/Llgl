#include <gtest/gtest.h>
#include <llgl/Point2d.hpp>

TEST(Point2d_test, EmptyConstructor)
{
	llgl::Point2d point;

	EXPECT_FLOAT_EQ(point.x, 0);
	EXPECT_FLOAT_EQ(point.y, 0);
}

TEST(Point2d_test, floatConstructor)
{
	llgl::Point2d point{0.8f, 0.3f};

	EXPECT_FLOAT_EQ(point.x, 0.8);
	EXPECT_FLOAT_EQ(point.y, 0.3);
}

TEST(Point2d_test, sizeMember)
{
	EXPECT_EQ(sizeof(llgl::Point2d::x), 4);
	EXPECT_EQ(sizeof(llgl::Point2d::y), 4);
}

TEST(Point2d_test, offsetMember)
{
	EXPECT_EQ(offsetof(llgl::Point2d, x), 0);
	EXPECT_EQ(offsetof(llgl::Point2d, y), sizeof(float));
}

TEST(Point2d_test, equalityOperator)
{
	EXPECT_TRUE((llgl::Point2d{0.3, 0.6} == llgl::Point2d{0.3, 0.6}));

	EXPECT_FALSE((llgl::Point2d{0.3, 0.6} == llgl::Point2d{0.3, 0.8}));
	EXPECT_FALSE((llgl::Point2d{0.3, 0.6} == llgl::Point2d{0.4, 0.6}));
	EXPECT_FALSE((llgl::Point2d{0.3, 0.6} == llgl::Point2d{0.5, 0.6}));
}
