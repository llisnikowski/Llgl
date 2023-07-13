#pragma once
#include <string>

namespace llgl
{

template <typename ...Ts>
class PositionInstruct
{
public:
	static std::string createInstruct();

private:
	static constexpr std::size_t memberSize();
	static std::string completeCoordinates();
	static_assert(memberSize() <= 4, "the number of argument sums must be less than 4");
};

template <typename ...Ts>
std::string PositionInstruct<Ts...>::createInstruct()
{
	if constexpr (sizeof...(Ts) == 0)
		return "gl_Position = vec4(0.f,0.f,0.f,1.f);";
	else if constexpr (memberSize() < 4)
		return "gl_Position = vec4(" + ((Ts::getName() + ",") + ...) 
		+ completeCoordinates() + ");";
	else{
		std::string inst = "gl_Position = vec4(" + ((Ts::getName() + ",") + ...);
		inst.pop_back();
		inst += ");";
		return inst;
	}

}

template <typename ...Ts>
constexpr std::size_t PositionInstruct<Ts...>::memberSize()
{
	if constexpr(sizeof...(Ts) == 0) return 0;
	else
	return (Ts::argsNumber() + ... );
}

template <typename ...Ts>
std::string PositionInstruct<Ts...>::completeCoordinates()
{
	std::string completeString;
	if constexpr(4 - memberSize() == 4)
		completeString += "0.f,";
	if constexpr(4 - memberSize() >= 3)
		completeString += "0.f,";
	if constexpr(4 - memberSize() >= 2)
		completeString += "0.f,";
	if constexpr(4 - memberSize() >= 1)
		completeString += "1.f";
	return completeString;
}


} // namespace llgl




