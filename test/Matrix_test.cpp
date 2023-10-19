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
}
