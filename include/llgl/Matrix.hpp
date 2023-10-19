#pragma once
#include <array>

namespace llgl 
{

template <size_t W, size_t H>
class Matrix {
public:
    using Row = std::array<float, W>;
    using Array = std::array<Row, H>;

    constexpr decltype(auto) operator[] (std::size_t pos);

private:
    Array array = {};
};



template <size_t W, size_t H>
constexpr decltype(auto) Matrix<W, H>::operator[] (std::size_t pos)
{
    return array[pos];
}

} // namespace llgl