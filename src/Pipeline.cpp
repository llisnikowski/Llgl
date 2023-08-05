#include "llgl/Pipeline.hpp"
#include "llgl/Shaders.hpp"

namespace llgl
{

Pipeline::Pipeline()
{
	glCreateProgramPipelines(1, &this->id);
}

Pipeline::~Pipeline()
{
	if(id) glDeleteProgramPipelines(1, &this->id);
}

void Pipeline::setShaders(std::shared_ptr<Shaders> shaders)
{
	setShader(shaders->getVertex(), GL_VERTEX_SHADER_BIT);
	setShader(shaders->getFragment(), GL_FRAGMENT_SHADER_BIT);
}

void Pipeline::setShader(uint32_t shaderId, GLbitfield stages)
{
	if(shaderId == 0) return;
	glUseProgramStages(this->id, stages, shaderId);
}

void Pipeline::bind()
{
	glBindProgramPipeline(this->id);
}


} // namespace llgl
