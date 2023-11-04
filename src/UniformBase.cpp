#include "llgl/UniformBase.hpp"
#include "llgl/Shaders.hpp"

namespace llgl
{


UniformBase::UniformBase()
{}

void UniformBase::addShader(Shaders &shader, uint8_t location)
{
	this->shaders.push_back({shader, location});
	this->updateShaders(shader.getVertex(), location);
}

void UniformBase::removeShader(Shaders &shader)
{
	for(int i = 0; i < this->shaders.size(); i++){
		if(&this->shaders[i].first.get() == &shader){
			this->shaders.erase(this->shaders.begin() + i);
			return;
		}
	}
}

void UniformBase::updateAllShaders()
{
	for(auto shaiderPair : this->shaders){
		this->updateShaders(shaiderPair.first.get().getVertex(), shaiderPair.second);
	}
}

} // namespace llgl
