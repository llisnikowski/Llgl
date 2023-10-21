#pragma once
#include <array>
#include <type_traits>

namespace llgl 
{

template <size_t W, size_t H>
class Matrix
{
public:
    using Row = std::array<float, H>;
    using Array = std::array<Row, W>;
    
    constexpr Matrix();
    constexpr Matrix(Array array);
    template <typename ...Ts>
    constexpr Matrix(Ts ...ts);

    constexpr decltype(auto) operator [](std::size_t pos);
    constexpr decltype(auto) operator [](std::size_t pos) const;

    float *begin();
    float *end();
    const float *cbegin() const;
    const float *cend() const;

private:
    template <std::size_t pos, typename ...Ts>
    constexpr void fill(float t, Ts... ts);

    Array array;
};


template <size_t W, size_t H>
constexpr Matrix<W, H>::Matrix()
:array{}
{
    if constexpr(W == H){
        for(int i = 0; i < W; i++){
            array[i][i] = 1.0f;
        }
    }
}

template <size_t W, size_t H>
constexpr Matrix<W, H>::Matrix(Array array)
:array{array}
{}

template <size_t W, size_t H>
template <typename ...Ts>
constexpr Matrix<W, H>::Matrix(Ts ...ts)
:array{}
{
    static_assert(sizeof...(ts) == W * H);
    this->fill<0>(ts...);
}

template <size_t W, size_t H>
constexpr decltype(auto) Matrix<W, H>::operator [](std::size_t pos)
{
    return array[pos];
}

template <size_t W, size_t H>
constexpr decltype(auto) Matrix<W, H>::operator [](std::size_t pos) const
{
    return array[pos];
}

template <size_t W, size_t H>
float *Matrix<W, H>::begin()
{
    return &array.front().front();
}

template <size_t W, size_t H>
float *Matrix<W, H>::end()
{
    return &array.back().back()+1;
}

template <size_t W, size_t H>
const float *Matrix<W, H>::cbegin() const
{
    return &array.front().front();
}

template <size_t W, size_t H>
const float *Matrix<W, H>::cend() const
{
    return &array.back().back()+1;
}

template <size_t W, size_t H>
template <std::size_t pos, typename ...Ts>
constexpr void Matrix<W, H>::fill(float t, Ts... ts)
{
    static_assert(pos < W * H);
    array[pos/H][pos%H] = t;
    if constexpr (sizeof...(ts)){
        this->fill<pos+1>(ts...);
    } 
}



} // namespace llgl