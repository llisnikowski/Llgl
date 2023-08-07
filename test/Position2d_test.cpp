#include <gtest/gtest.h>
#include <llgl/Position2d.hpp>
#include <llgl/Utils.hpp>

TEST(Position2d_test, EmptyConstructor)
{
	llgl::Position2d point;

	EXPECT_FLOAT_EQ(point.x, 0);
	EXPECT_FLOAT_EQ(point.y, 0);
}

TEST(Position2d_test, floatConstructor)
{
	llgl::Position2d point{0.8f, 0.3f};

	EXPECT_FLOAT_EQ(point.x, 0.8);
	EXPECT_FLOAT_EQ(point.y, 0.3);
}

TEST(Position2d_test, sizeMember)
{
	EXPECT_EQ(sizeof(llgl::Position2d::x), 4);
	EXPECT_EQ(sizeof(llgl::Position2d::y), 4);
	EXPECT_EQ(sizeof(llgl::Position2d), 8);
}

TEST(Position2d_test, offsetMember)
{
	EXPECT_EQ(llgl::offsetOf(&llgl::Position2d::x), 0);
	EXPECT_EQ(llgl::offsetOf(&llgl::Position2d::y), sizeof(float));
}

TEST(Position2d_test, equalityOperator)
{
	EXPECT_TRUE((llgl::Position2d{0.3, 0.6} == llgl::Position2d{0.3, 0.6}));

	EXPECT_FALSE((llgl::Position2d{0.3, 0.6} == llgl::Position2d{0.3, 0.8}));
	EXPECT_FALSE((llgl::Position2d{0.3, 0.6} == llgl::Position2d{0.4, 0.6}));
	EXPECT_FALSE((llgl::Position2d{0.3, 0.6} == llgl::Position2d{0.5, 0.6}));
}

TEST(Position2d_test, argsNumber)
{
	EXPECT_EQ(llgl::Position2d::argsNumber(), 2);
}

TEST(Position2d_test, argsType)
{
	EXPECT_EQ(llgl::Position2d::argsType(), GL_FLOAT);
}

TEST(Position2d_test, getName)
{
	EXPECT_STREQ(llgl::Position2d::getName().c_str(), "position2d");
}
