#include "llgl/ObjectBase.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/Pipeline.hpp"

namespace llgl
{

ObjectBase::ObjectBase()
{
	glCreateVertexArrays(1, &this->vao);
}

ObjectBase::~ObjectBase()
{
	if(this->vao) glDeleteVertexArrays(1, &this->vao);
}

void ObjectBase::setPipeline(std::shared_ptr<Pipeline> pipeline)
{
	this->pipeline = pipeline;
}

std::shared_ptr<Pipeline> ObjectBase::getPipeline()
{
	return this->pipeline;
}

uint32_t ObjectBase::getVao()
{
	return this->vao;
}

void ObjectBase::bind()
{
	if(this->pipeline) pipeline->bind();
	glBindVertexArray(this->vao);
}


} // namespace llgl
