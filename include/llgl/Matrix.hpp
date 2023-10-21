#pragma once
#include <array>
#include <type_traits>
#include <functional>

namespace llgl 
{

template <size_t ROW, size_t COL>
class Matrix
{
public:
    using Row = std::array<float, COL>;
    using Array = std::array<Row, ROW>;
    
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



template <size_t ROW, size_t COL>
constexpr Matrix<ROW, COL>::Matrix()
:array{}
{
    if constexpr(ROW == COL){
        for(int i = 0; i < ROW; i++){
            array[i][i] = 1.0f;
        }
    }
}

template <size_t ROW, size_t COL>
constexpr Matrix<ROW, COL>::Matrix(Array array)
:array{array}
{}

template <size_t ROW, size_t COL>
template <typename ...Ts>
constexpr Matrix<ROW, COL>::Matrix(Ts ...ts)
:array{}
{
    static_assert(sizeof...(ts) == ROW * COL);
    this->fill<0>(ts...);
}

template <size_t ROW, size_t COL>
constexpr decltype(auto) Matrix<ROW, COL>::operator [](std::size_t pos)
{
    return array[pos];
}

template <size_t ROW, size_t COL>
constexpr decltype(auto) Matrix<ROW, COL>::operator [](std::size_t pos) const
{
    return array[pos];
}

template <size_t ROW, size_t COL>
float *Matrix<ROW, COL>::begin()
{
    return &array.front().front();
}

template <size_t ROW, size_t COL>
float *Matrix<ROW, COL>::end()
{
    return &array.back().back()+1;
}

template <size_t ROW, size_t COL>
const float *Matrix<ROW, COL>::cbegin() const
{
    return &array.front().front();
}

template <size_t ROW, size_t COL>
const float *Matrix<ROW, COL>::cend() const
{
    return &array.back().back()+1;
}

template <size_t ROW, size_t COL>
template <std::size_t pos, typename ...Ts>
constexpr void Matrix<ROW, COL>::fill(float t, Ts... ts)
{
    static_assert(pos < ROW * COL);
    array[pos/COL][pos%COL] = t;
    if constexpr (sizeof...(ts)){
        this->fill<pos+1>(ts...);
    } 
}

template <size_t ROW, size_t COL>
constexpr void Matrix<ROW, COL>::foreach(IteratorFunc func)
{
    for(int row = 0; row < ROW; row++){
        for(int col = 0; col < COL; col++){
            func(array[row][col], row, col);
        }
    }
}

} // namespace llgl


template <size_t ROW1, size_t COL1, size_t ROW2, size_t COL2>
auto operator *(llgl::Matrix<ROW1, COL1> lhs, llgl::Matrix<ROW2, COL2> rhs);


template <size_t ROW1, size_t COL1, size_t ROW2, size_t COL2>
auto operator *(llgl::Matrix<ROW1, COL1> lhs, llgl::Matrix<ROW2, COL2> rhs)
{
    static_assert(COL1 == ROW2);
    llgl::Matrix<ROW1, COL2> mat;
    mat.foreach([&lhs, &rhs](float &value, size_t row, size_t col)
    {
        float sum = 0;
        for(int i = 0; i < COL1; i++){
            sum += lhs[row][i] * rhs[i][col];
        }
        value = sum;
    });
    return mat;
}