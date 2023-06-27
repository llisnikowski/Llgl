#include <gtest/gtest.h>
#include "llgl/Window.hpp"

TEST(Window_test, WindowConstructor)
{
	llgl::Window windows{"hello world", {800, 500}};

	EXPECT_STREQ(windows.getName().c_str(), "hello world");
	EXPECT_TRUE((windows.getSize() == llgl::Size{800, 500}));
}

TEST(Window_test, setSize)
{
	llgl::Window windows{"hello world", {800, 500}};

	windows.setSize({10, 20});
	
	EXPECT_STREQ(windows.getName().c_str(), "hello world");
	EXPECT_TRUE((windows.getSize() == llgl::Size{10, 20}));
}

TEST(Window_test, setName)
{
	llgl::Window windows{"hello world", {800, 500}};

	windows.setName("Hi");

	EXPECT_STREQ(windows.getName().c_str(), "Hi");
	EXPECT_TRUE((windows.getSize() == llgl::Size{800, 500}));
}
