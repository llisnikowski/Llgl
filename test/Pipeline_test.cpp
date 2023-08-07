#include <gtest/gtest.h>
#include "llgl/Llgl.hpp"
#include "llgl/Pipeline.hpp"


class Pipeline_test : public ::testing::Test
{
public:
	Pipeline_test()
		:llgl{"", {1, 1}}
	{
    	this->llgl.init();
	}

	llgl::Llgl llgl;
};

TEST_F(Pipeline_test, getId)
{
	llgl::Pipeline pipeline1{};
	llgl::Pipeline pipeline2{};
	EXPECT_NE(pipeline1.getId(), pipeline2.getId());
}

