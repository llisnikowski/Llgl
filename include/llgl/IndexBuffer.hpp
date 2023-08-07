#pragma once
#include <memory>
#include <vector>
#include <stdint.h>
#include <type_traits>
#include "llgl/IndexBufferBase.hpp"

namespace llgl
{

template <typename T = uint8_t>
class IndexBuffer : public IndexBufferBase
{
public:
	IndexBuffer(const std::vector<T> &indices);
	IndexBuffer(std::vector<T> &&indices);
	~IndexBuffer();

	GLenum getType() override;
	uint32_t getLength() override;

private:

	std::vector<T> indices;
};

template <typename T>
IndexBuffer<T>::IndexBuffer(const std::vector<T> &indices)
:indices{indices}
{
    glNamedBufferStorage(this->id, sizeof(T) * this->indices.size(), this->indices.data(), 0);
}

template <typename T>
IndexBuffer<T>::IndexBuffer(std::vector<T> &&indices)
:indices{std::move(indices)}
{
    glNamedBufferStorage(this->id, sizeof(T) * this->indices.size(), this->indices.data(), 0);
}

template <typename T>
IndexBuffer<T>::~IndexBuffer()
{
}

template <typename T>
GLenum IndexBuffer<T>::getType()
{
	if constexpr (std::is_same_v<T, uint8_t>){
		return GL_UNSIGNED_BYTE;
	}
	else if constexpr (std::is_same_v<T, uint16_t>){
		return GL_UNSIGNED_SHORT;
	}
	else if constexpr (std::is_same_v<T, uint32_t>){
		return GL_UNSIGNED_INT;
	}
}

template <typename T>
uint32_t IndexBuffer<T>::getLength()
{
	return this->indices.size();
}

} // namespace llgl
