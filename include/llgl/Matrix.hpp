#pragma once
#include <array>
#include <type_traits>
#include <functional>

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

    using IteratorFunc = std::function<void(float &value, size_t col, size_t row)>;
    constexpr void foreach(IteratorFunc fun);

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

template <size_t W, size_t H>
constexpr void Matrix<W, H>::foreach(IteratorFunc func)
{
    for(int row = 0; row < W; row++){
        for(int col = 0; col < H; col++){
            func(array[row][col], row, col);
        }
    }
}

} // namespace llgl


template <size_t W1, size_t H1, size_t W2, size_t H2>
auto operator *(llgl::Matrix<W1, H1> lhs, llgl::Matrix<W2, H2> rhs);


template <size_t W1, size_t H1, size_t W2, size_t H2>
auto operator *(llgl::Matrix<W1, H1> lhs, llgl::Matrix<W2, H2> rhs)
{
    static_assert(H1 == W2);
    llgl::Matrix<W1, H2> mat;
    mat.foreach([&lhs, &rhs](float &value, size_t row, size_t col)
    {
        float sum = 0;
        for(int i = 0; i < H1; i++){
            sum += lhs[row][i] * rhs[i][col];
        }
        value = sum;
    });
    return mat;
}