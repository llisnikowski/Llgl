#include <gtest/gtest.h>
#include "llgl/Llgl.hpp"


TEST(Llgl_test, WindowConstructor)
{
	llgl::Llgl llgl{"hello world", {800, 500}};

	EXPECT_STREQ(llgl.getName().c_str(), "hello world");
	EXPECT_TRUE((llgl.getSize() == llgl::Size{800, 500}));
}
