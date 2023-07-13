#include <gtest/gtest.h>
#include <llgl/PositionInstruct.hpp>
#include <llgl/Position2d.hpp>


struct MockPositionArg
{
	static constexpr std::size_t argsNumber(){return 1;};
    static std::string getName(){return "MockPositionArg";}
};



TEST(PositionInstruct_test, Empty)
{
	EXPECT_STREQ(llgl::PositionInstruct<>::createInstruct().c_str(), 
	"gl_Position = vec4(0.f,0.f,0.f,1.f);");
}

TEST(PositionInstruct_test, Single)
{
	EXPECT_STREQ(llgl::PositionInstruct<MockPositionArg>::createInstruct().c_str(), 
	"gl_Position = vec4(MockPositionArg,0.f,0.f,1.f);");
}

TEST(PositionInstruct_test, Double)
{
	EXPECT_STREQ(llgl::PositionInstruct<llgl::Position2d>::createInstruct().c_str(), 
	"gl_Position = vec4(position2d,0.f,1.f);");
}

TEST(PositionInstruct_test, Three)
{
	EXPECT_STREQ((llgl::PositionInstruct<llgl::Position2d, MockPositionArg>::createInstruct().c_str()), 
	"gl_Position = vec4(position2d,MockPositionArg,1.f);");
}

TEST(PositionInstruct_test, Four)
{
	EXPECT_STREQ((llgl::PositionInstruct<MockPositionArg, llgl::Position2d, MockPositionArg>::createInstruct().c_str()), 
	"gl_Position = vec4(MockPositionArg,position2d,MockPositionArg);");
}