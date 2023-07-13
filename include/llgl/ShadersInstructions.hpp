#pragma once


namespace llgl
{

template <typename... Ts>
class ShadersInstructions
{
public:
	using Instructions = std::Instructions<Ts...>;

	ShadersInstructions();

};


} // namespace llgl

