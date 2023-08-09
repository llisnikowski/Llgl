#pragma once
#include <memory> 
#include <vector>
#include <utility>
#include <stdint.h>

namespace llgl
{
class Shaders;

class UniformBase
{
public:
	UniformBase();
	virtual ~UniformBase() = default;

	void addShader(Shaders &shader, uint8_t location);
	void removeShader(Shaders &shader);
	virtual void update(){};

protected:
	virtual void updateShaders(uint32_t shader, int location) = 0;
	void updateAllShaders();

private:
	std::vector<std::pair<std::reference_wrapper<Shaders>, uint8_t>> shaders;

};


} // namespace llgl
