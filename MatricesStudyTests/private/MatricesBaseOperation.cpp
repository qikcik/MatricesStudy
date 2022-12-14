#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Matrix.tpp"

TEST(Matrices, AddingScalarToMatrices)
{
    Matrix<float,2,2> A
    {{{
        {1.0,   2.0},
        {3.0,   4.0}
    }}};

    Matrix<float,2,2> C
    {{{
        {6.0,   7.0},
        {8.0,   9.0}
    }}};

    EXPECT_EQ( A + 5.f, C);
}

TEST(Matrices, MultplingScalarToMatrices)
{
    Matrix<float,2,2> A
    {{{
        {1.0,   2.0},
        {3.0,   4.0}
    }}};

    Matrix<float,2,2> C
    {{{
        {3.0,   6.0},
        {9.0,   12.0}
    }}};

    EXPECT_EQ( A * 3.f, C);
}

TEST(Matrices, Adding2Matrices)
{
    Matrix<float,2,2> A
    {{{
        {1.0,   2.0},
        {3.0,   4.0}
    }}};

    Matrix<float,2,2> B
    {{{
        {5.0,   6.0},
        {7.0,   8.0},
    }}};

    Matrix<float,2,2> C
    {{{
        {6.0,   8.0},
        {10.0,  12.0}
    }}};

    EXPECT_EQ( A + B ,C);
}

TEST(Matrices, Multipling2Matrices)
{
    Matrix<float,2,3> A
    {{{
        {1.0,   2.0,    3.0},
        {4.0,   5.0,    6.0}
    }}};

    Matrix<float,3,2> B
    {{{
        {10.0,  11.0},
        {20.0,  21.0},
        {30.0,  31.0}
    }}};

    Matrix<float,2,2> C
    {{{
        {140.0, 146.0},
        {320.0, 335.0}
    }}};

    EXPECT_EQ( A * B ,C);
}

TEST(Matrices, MatrixPow)
{
    Matrix<float,2,2> A
    {{{
        {1.0,   2.0},
        {3.0,   4.0}
    }}};

    const size_t n = 6;

    auto C = A;
    for(size_t i = 0; i!= n-1; i++)
        C = C * A;

    Matrix<float,2,2> CExp
    {{{
        {5743,  8370},
        {12555, 18298}
    }}};


    EXPECT_EQ(C, CExp);
}

