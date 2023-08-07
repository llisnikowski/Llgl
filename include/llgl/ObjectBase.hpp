#pragma once
#include <stdint.h>
#include <memory>

namespace llgl
{
class Pipeline;

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

    uint32_t getVao();

	void setPipeline(std::shared_ptr<Pipeline> pipeline);

    virtual void draw() = 0;
	void bind();

protected:
	uint32_t vao{};
	std::shared_ptr<Pipeline> pipeline{};
};


} // namespace llgl
