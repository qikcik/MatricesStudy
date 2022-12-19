#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "Matrix.tpp"
#include "CommonMath.tpp"


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

TEST(Matrices, AddingString)
{
    Matrix<std::string,2,2> A
            {{{
                      {"1",   "2"},
                      {"3",   "4"}
              }}};

    Matrix<std::string,2,2> C
            {{{
                      {"1a",   "2a"},
                      {"3a",   "4a"}
            }}};

    EXPECT_EQ( A + std::string("a"), C);
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
        {6.0,   6.0},
        {7.0,   8.0},
    }}};

    Matrix<float,2,2> C
    {{{
        {7.0,   8.0},
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

    Matrix<float,2,2> C
    {{{
        {5743,  8370},
        {12555, 18298}
    }}};

    EXPECT_EQ(A.pow(0), A.Identity());
    EXPECT_EQ(A.pow(1), A);
    EXPECT_EQ(A.pow(6), C);

}