#include "llgl/IndexBufferBase.hpp"

namespace llgl
{

IndexBufferBase::IndexBufferBase()
{
    glCreateBuffers(1, &id);
}

IndexBufferBase::~IndexBufferBase()
{
	if(id) glDeleteBuffers(1, &this->id);
	this->id = 0;
}

uint32_t IndexBufferBase::getId()
{
	return this->id;
}


} // namespace llgl
