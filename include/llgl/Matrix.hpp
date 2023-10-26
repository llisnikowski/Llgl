#pragma once
#include <array>
#include <type_traits>
#include <functional>
#include <numeric>
#include <cmath>

namespace llgl 
{


template <size_t ROW, size_t COL>
class Matrix;

template <size_t ROW>
using Vector = Matrix<ROW, 1>;

template <size_t ROW, size_t COL>
class Matrix
{
public:
    static_assert(ROW >= 1 && COL >= 1);

    using Row = std::array<float, COL>;
    using Array = std::array<Row, ROW>;
    
    constexpr Matrix();
    constexpr Matrix(Array array);
    template <typename ...Ts>
    using EnableIfFloat = std::enable_if_t<
        std::conjunction_v<std::is_convertible_v<Ts, float>...>
    >;
    template <typename ...Ts, EnableIfFloat<Ts...>>
    constexpr Matrix(Ts ...ts);

    constexpr decltype(auto) operator [](std::size_t pos);
    constexpr decltype(auto) operator [](std::size_t pos) const;
    constexpr decltype(auto) at(std::size_t pos);
    constexpr decltype(auto) at(std::size_t pos) const;

    float *begin();
    float *end();
    const float *cbegin() const;
    const float *cend() const;

    using IteratorFunc = std::function<void(float &value, size_t col, size_t row)>;
    constexpr void foreach(IteratorFunc fun);

    float length();


    Matrix<ROW, COL> getUnit();

    auto transform(Vector<ROW-1> vec);
    auto scale(Vector<ROW-1> vec);
    auto rotateDeg(Vector<ROW-1> vec, float degree);
    auto rotateRad(Vector<ROW-1> vec, float angle);
    template <size_t AXIS=0>
    auto rotateDeg(float degree);
    template <size_t AXIS=0>
    auto rotateRad(float angle);

    template <size_t ROW2, size_t COL2>
    constexpr auto operator *(const llgl::Matrix<ROW2, COL2> &rhs) const;
    template <size_t ROW2, size_t COL2>
    constexpr auto operator *(llgl::Matrix<ROW2, COL2> &&rhs) const;

    constexpr auto operator *=(const llgl::Matrix<ROW, COL> &rhs);
    constexpr auto operator *=(llgl::Matrix<ROW, COL> &&rhs);

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
template <typename ...Ts, Matrix<ROW, COL>::EnableIfFloat<Ts...>>
constexpr Matrix<ROW, COL>::Matrix(Ts ...ts)
:array{}
{
    static_assert(sizeof...(ts) == (ROW * COL));
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
constexpr decltype(auto) Matrix<ROW, COL>::at(std::size_t pos)
{
    if constexpr (COL == 1){
        return array[pos][0];
    }
    else{
        return array.at(pos);
    }
}

template <size_t ROW, size_t COL>
constexpr decltype(auto) Matrix<ROW, COL>::at(std::size_t pos) const
{
    if constexpr (COL == 1){
        return array[0].at(pos);
    }
    else{   
        return array.at(pos);
    }
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

template <size_t ROW, size_t COL>
float Matrix<ROW, COL>::length()
{
    static_assert(COL == 1);
    float length = std::accumulate(this->array.begin(), this->array.end()
    ,float{0.0}, [](float sum, std::array<float, 1> axis){
        return sum + (axis[0] * axis[0]);
    });
    return std::sqrt(length);
}

template <size_t ROW, size_t COL>
Matrix<ROW, COL> Matrix<ROW, COL>::getUnit()
{
    static_assert(COL == 1);
    float length = this->length();
    Matrix<ROW, COL> unit;
    std::transform(this->begin(), this->end(), unit.begin()
    ,[this, length](float val){
        return val / length;
    });
    return unit;
}

template <size_t ROW, size_t COL>
auto Matrix<ROW, COL>::transform(Vector<ROW-1> vec)
{
    static_assert(ROW == COL);
    Matrix<ROW, COL> transMat{};
    for(int i = 0; i < ROW - 1; i++){
        transMat[i][COL-1]= vec[i][0];
    }
    this->operator*=(transMat);
    return *this;
}

template <size_t ROW, size_t COL>
auto Matrix<ROW, COL>::scale(Vector<ROW-1> vec)
{
    static_assert(ROW == COL);
    Matrix<ROW, COL> scaleMat{};
    for(int i = 0; i < ROW - 1; i++){
        scaleMat[i][i]= vec[i][0];
    }
    this->operator*=(scaleMat);
    return *this;
}

template <size_t ROW, size_t COL>
auto Matrix<ROW, COL>::rotateDeg(Vector<ROW-1> vec, float degree)
{
    static_assert(ROW == COL && ROW == 4);
    return this->rotateRad(vec, degree / 180 * M_PI);
}

template <size_t ROW, size_t COL>
auto Matrix<ROW, COL>::rotateRad(Vector<ROW-1> vec, float angle)
{
    static_assert(ROW == COL && ROW == 4);
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    Vector<ROW - 1> unitVec = vec.getUnit();
    float x = unitVec[0][0];
    float y = unitVec[0][1];
    float z = unitVec[0][2];
    Matrix<ROW, COL> rotateMat{{
        cosA + x*(1-cosA), x*y*(1-cosA) - z*sinA, x*z*(1-cosA) + y*sinA, 0,
        x*y*(1-cosA) + z*sinA, cosA + y*y*(1-cosA), y*z*(1-cosA) - x*sinA, 0,
        z*x*(1-cosA) - y*sinA, z*y*(1-cosA) + x*sinA, cosA + z*z*(1-cosA), 0,
        0, 0, 0, 1
    }};
    this->operator*=(rotateMat);
    return *this;
}

template <size_t ROW, size_t COL>
template <size_t AXIS>
auto Matrix<ROW, COL>::rotateDeg(float degree)
{
    static_assert(ROW == COL && (ROW == 4 || ROW == 3));
    static_assert(AXIS < ROW - 1);
    return this->rotateRad<AXIS>(degree / 180 * M_PI);
}

template <size_t ROW, size_t COL>
template <size_t AXIS>
auto Matrix<ROW, COL>::rotateRad(float angle)
{
    static_assert(ROW == COL && (ROW == 4 || ROW == 3));
    static_assert(AXIS < ROW - 1);
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    if constexpr(ROW == 3){
        static_assert(AXIS == 0);
        Matrix<ROW, COL> rotateMat{{
            cosA, -sinA, 0,
            sinA, cosA, 0,
            0, 0, 1
        }};
        this->operator*=(rotateMat);
    }
    else {
        if constexpr(AXIS == 0){
            Matrix<ROW, COL> rotateMat{{
                1, 0, 0, 0,
                0, cosA, -sinA, 0,
                0, sinA, cosA, 0,
                0, 0, 0, 1
            }};
            this->operator*=(rotateMat);
        }
        else if constexpr(AXIS == 1){
            Matrix<ROW, COL> rotateMat{{
                cosA, 0, sinA, 0,
                0, 1, 0, 0,
                -sinA, 0, cosA, 0,
                0, 0, 0, 1
            }};
            this->operator*=(rotateMat);
        }
        else if constexpr(AXIS == 2){
            Matrix<ROW, COL> rotateMat{{
                cosA, -sinA, 0, 0,
                sinA, cosA, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            }};
            this->operator*=(rotateMat);
        }
    }
    return *this;
}

template <size_t ROW, size_t COL>
template <size_t ROW2, size_t COL2>
constexpr auto Matrix<ROW, COL>::operator *(const llgl::Matrix<ROW2, COL2> &rhs) const
{
    static_assert(COL == ROW2 || (COL > ROW2 && COL2 == 1));
    llgl::Matrix<ROW, COL2> mat;
    mat.foreach([this, &rhs](float &value, size_t row, size_t col)
    {
        float sum = 0;
        for(int i = 0; i < COL; i++){
            if constexpr (COL == ROW2){
                sum += array[row][i] * rhs[i][col];
            }
            else {
                if(i < ROW2){
                    sum += array[row][i] * rhs[i][col];
                }
                else{
                    sum += array[row][i];
                }
            }
        }
        value = sum;
    });
    return mat;
}

template <size_t ROW, size_t COL>
template <size_t ROW2, size_t COL2>
constexpr auto Matrix<ROW, COL>::operator *(llgl::Matrix<ROW2, COL2> &&rhs) const
{
    static_assert(COL == ROW2 || (COL > ROW2 && COL2 == 1));
    llgl::Matrix<ROW, COL2> mat;
    mat.foreach([this, &rhs](float &value, size_t row, size_t col)
    {
        float sum = 0;
        for(int i = 0; i < COL; i++){
            if constexpr (COL == ROW2){
                sum += array[row][i] * rhs[i][col];
            }
            else {
                if(i < ROW2){
                    sum += array[row][i] * rhs[i][col];
                }
                else{
                    sum += array[row][i];
                }
            }
        }
        value = sum;
    });
    return mat;
}

template <size_t ROW, size_t COL>
constexpr auto Matrix<ROW, COL>::operator *=(const llgl::Matrix<ROW, COL> &rhs)
{
    static_assert((COL == ROW));
    this->array = (*this * rhs).array;
    return *this;
}

template <size_t ROW, size_t COL>
constexpr auto Matrix<ROW, COL>::operator *=(llgl::Matrix<ROW, COL> &&rhs)
{
    static_assert((COL == ROW));
    this->array = (*this * rhs).array;
    return *this;
}


} // namespace llgl


