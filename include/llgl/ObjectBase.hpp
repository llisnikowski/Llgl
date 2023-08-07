#pragma once
#include <stdint.h>
#include <memory>

namespace llgl
{
class Pipeline;
class IndexBufferBase;

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

    uint32_t getVao();

	void setPipeline(std::shared_ptr<Pipeline> pipeline);
	std::shared_ptr<Pipeline> getPipeline();

	void setIndexBuffer(std::unique_ptr<IndexBufferBase> &&indexBuffer);

    virtual void draw() = 0;
	void bind();

protected:
	uint32_t vao{};
	std::shared_ptr<Pipeline> pipeline{};
	std::unique_ptr<IndexBufferBase> indexBuffer{};
};


} // namespace llgl
