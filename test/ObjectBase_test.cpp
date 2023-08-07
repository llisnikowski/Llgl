#include <gtest/gtest.h>
#include "llgl/Llgl.hpp"
#include "llgl/ObjectBase.hpp"
#include "llgl/Pipeline.hpp"

class ObjectMock : public llgl::ObjectBase
{
public:

	void draw(){}
};

class ObjectBase_test : public ::testing::Test
{
public:
	ObjectBase_test()
		:llgl{"", {1, 1}}
		,object{}
		,pipeline{}
	{
    	this->llgl.init();
		this->object = std::make_shared<ObjectMock>();
		this->pipeline = std::make_shared<llgl::Pipeline>();
		this->object->setPipeline(this->pipeline);
	}

	llgl::Llgl llgl;
	std::shared_ptr<ObjectMock> object;
	std::shared_ptr<llgl::Pipeline> pipeline;
};

TEST_F(ObjectBase_test, getPipeline)
{
	EXPECT_EQ(object->getPipeline().get() ,pipeline.get());
}

