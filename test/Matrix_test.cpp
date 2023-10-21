#include <gtest/gtest.h>
#include "llgl/Matrix.hpp"

TEST(Matrix_test, operatonSquare)
{
	llgl::Matrix<4, 3> m;

    m[2][0] = 1.2;
    m[1][2] = 3.1;

    EXPECT_FLOAT_EQ(m[0][3], 0);
    EXPECT_FLOAT_EQ(m[2][0], 1.2);
    EXPECT_FLOAT_EQ(m[0][2], 0);
    EXPECT_FLOAT_EQ(m[1][2], 3.1);
    EXPECT_FLOAT_EQ(m[2][1], 0);
    
    const auto &mconst = m;
    EXPECT_FLOAT_EQ(mconst[1][2], 3.1);

}

TEST(Matrix_test, beginAndEnd)
{
    llgl::Matrix<4, 3> m;
    const llgl::Matrix<4, 3> mconst;
    EXPECT_EQ(static_cast<void*>(&m), m.begin());
    EXPECT_EQ(m.begin()+4*3, m.end());
    EXPECT_EQ(static_cast<const void*>(&mconst), mconst.cbegin());
    EXPECT_EQ(mconst.cbegin()+4*3, mconst.cend());
}

TEST(Matrix_test, emptyConstructor)
{
    llgl::Matrix<4, 3> m;

    for(float value : m){
        EXPECT_FLOAT_EQ(value, 0);
    }
}

TEST(Matrix_test, constructorArray)
{
    constexpr llgl::Matrix<3, 2> m{
        {{{1, 2}, {3, 4}, {5, 6}}}
    };

    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 2; col++){
            EXPECT_FLOAT_EQ(m[row][col], row*2+col+1);
        }
    }
}

TEST(Matrix_test, constructorValues)
{
    constexpr llgl::Matrix<3, 2> m{1, 2, 3, 4, 5, 6};

    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 2; col++){
            EXPECT_FLOAT_EQ(m[row][col], row*2+col+1);
        }
    }
}

TEST(Matrix_test, identyMatrix)
{
    constexpr llgl::Matrix<3, 3> m;
    constexpr llgl::Matrix<3, 2> m2;

    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            EXPECT_FLOAT_EQ(m[row][col], row == col ? 1.f : 0.f);
        }
    }
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 2; col++){
            EXPECT_FLOAT_EQ(m2[row][col], 0.f);
        }
    }
}