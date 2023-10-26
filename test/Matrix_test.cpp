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
    constexpr llgl::Matrix<3, 2> m{{1, 2, 3, 4, 5, 6}};

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

TEST(Matrix_test, Multiplication)
{
    constexpr llgl::Matrix<4, 3> m1{{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
        10, 11, 12
    }};
    constexpr llgl::Matrix<3, 2> m2{{
        1, 2,
        3, 4,
        5, 6
    }};

    llgl::Matrix<4, 2> expect{{
        1*1 + 2*3 + 3*5, 1*2 + 2*4 + 3*6,
        4*1 + 5*3 + 6*5, 4*2 + 5*4 + 6*6,
        7*1 + 8*3 + 9*5, 7*2 + 8*4 + 9*6,
        10*1 + 11*3 + 12*5, 10*2 + 11*4 + 12*6,
    }};

    llgl::Matrix<4, 2> result = m1 * m2;

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 2; col++){
            EXPECT_FLOAT_EQ(result[row][col], expect[row][col]);
        }
    }
}

TEST(Matrix_test, Multiplication2)
{
    llgl::Matrix<3, 3> m1{{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    }};
    constexpr llgl::Matrix<3, 3> m2{{
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    }};

    llgl::Matrix<3, 3> expect = m1 * m2;
    m1 *= m2;

    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            EXPECT_FLOAT_EQ(m1[row][col], expect[row][col]);
        }
    }
}

TEST(Matrix_test, vector)
{
    llgl::Vector<3> vec{{
        1, 2, 3
    }};
    vec.at(2) = 4;

    llgl::Matrix<4, 1> expect{{
        1.f, 2.f, 4.f, 1.f
    }};

    llgl::Matrix<4, 4> one; 
    llgl::Matrix<4, 1> result = one * vec;

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 1; col++){
            EXPECT_FLOAT_EQ(result[row][col], expect[row][col]);
        }
    }
}

TEST(Matrix_test, length)
{
    llgl::Vector<5> vec{{2, -5, 0.5, -7, 4}};

    EXPECT_FLOAT_EQ(vec.length(), std::sqrt(2*2+5*5+0.5*0.5+7*7+4*4));
}

TEST(Matrix_test, unit)
{
    llgl::Vector<5> vec{{2, -5, 0.5, -7, 4}};

    llgl::Vector<5> unitVector = vec.getUnit();

    ASSERT_FLOAT_EQ(unitVector.length(), 1.0f);
    EXPECT_FLOAT_EQ(unitVector.at(0), vec.at(0) / vec.length());
    EXPECT_FLOAT_EQ(unitVector.at(1), vec.at(1) / vec.length());
    EXPECT_FLOAT_EQ(unitVector.at(2), vec.at(2) / vec.length());
    EXPECT_FLOAT_EQ(unitVector.at(3), vec.at(3) / vec.length());
    EXPECT_FLOAT_EQ(unitVector.at(4), vec.at(4) / vec.length());
}

TEST(Matrix_test, tranform)
{  
    llgl::Matrix<4, 4> mat{{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    }};

    mat.transform(llgl::Vector<3>{{-2, 3, 5}});

    constexpr llgl::Matrix<4, 4> expect{{
        1, 2, 3, (1*-2 + 2*3 + 3*5 + 4),
        5, 6, 7, (5*-2 + 6*3 + 7*5 + 8),
        9, 10, 11, (9*-2 + 10*3 + 11*5 + 12),
        13, 14, 15, (13*-2 + 14*3 + 15*5 + 16)
    }};

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}
TEST(Matrix_test, scale)
{  
    llgl::Matrix<4, 4> mat{{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    }};

    llgl::Matrix<4, 4> expect = mat 
    * llgl::Matrix<4, 4> {{
        -2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 5, 0,
        0, 0, 0, 1
    }};
    mat.scale(llgl::Vector<3>{{-2, 3, 5}});


    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}
TEST(Matrix_test, rotate)
{  
    llgl::Matrix<4, 4> mat{{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    }};

    llgl::Matrix<4, 4> expect = mat 
    * llgl::Matrix<4, 4> {{
        0, 0, 1, 0,
        0, 1, 0, 0,
        -1, 0, 0, 0,
        0, 0, 0, 1
    }};
    mat.rotateDeg(llgl::Vector<3>{{0, 5, 0}}, 90);

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}
TEST(Matrix_test, rotate2d)
{  
    llgl::Matrix<3, 3> mat{{
        1, 2, 3, 
        4, 5, 6,
        7, 8, 9,
    }};

    float deg = 53.0f;

    llgl::Matrix<3, 3> expect = mat 
    * llgl::Matrix<3, 3> {{
        std::cos((float)(deg*M_PI/180.f)), -std::sin((float)(deg*M_PI/180.0f)), 0,
        std::sin((float)(deg*M_PI/180.f)), std::cos((float)(deg*M_PI/180.0f)), 0,
        0, 0, 1
    }};
    mat.rotateDeg<0>(deg);

    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}
TEST(Matrix_test, rotateX)
{  
    llgl::Matrix<4, 4> mat{{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    }};

    float deg = 70.0f;
    float sinA = std::sin(deg/180.0*M_PI);
    float cosA = std::cos(deg/180.0*M_PI);

    llgl::Matrix<4, 4> expect = mat 
    * llgl::Matrix<4, 4> {{
        1, 0, 0, 0,
        0, cosA, -sinA, 0,
        0, sinA, cosA, 0,
        0, 0, 0, 1
    }};
    mat.rotateDeg<0>(deg);

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}
TEST(Matrix_test, rotateY)
{  
    llgl::Matrix<4, 4> mat{{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    }};

    float deg = 70.0f;
    float sinA = std::sin(deg/180.0*M_PI);
    float cosA = std::cos(deg/180.0*M_PI);

    llgl::Matrix<4, 4> expect = mat 
    * llgl::Matrix<4, 4> {{
        cosA, 0, sinA, 0,
        0, 1, 0, 0,
        -sinA, 0, cosA, 0,
        0, 0, 0, 1
    }};
    mat.rotateDeg<1>(deg);

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}
TEST(Matrix_test, rotateZ)
{  
    llgl::Matrix<4, 4> mat{{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    }};

    float deg = 70.0f;
    float sinA = std::sin(deg/180.0*M_PI);
    float cosA = std::cos(deg/180.0*M_PI);

    llgl::Matrix<4, 4> expect = mat 
    * llgl::Matrix<4, 4> {{
        cosA, -sinA, 0, 0,
        sinA, cosA, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
    mat.rotateDeg<2>(deg);

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            EXPECT_FLOAT_EQ(mat[row][col], expect[row][col]);
        }
    }
}