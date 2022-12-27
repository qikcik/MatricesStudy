#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "Matrix.tpp"
#include "CommonMath.tpp"

TEST(Exp, RealNumber)
{
    EXPECT_NEAR( exp<10>(1.f),  2.7182f, 0.01f);

    EXPECT_NEAR( exp<10>(0.f),  1.f,     0.01f);
    EXPECT_NEAR( exp<10>(-1.f), 0.3678f, 0.01f);
}

TEST(Exp, Matrices)
{
    constexpr auto ACCURACY = 10;

    Matrix<float,2,2> A
    {{{
        {0, 0},
        {0, 0}
    }}};

    Matrix<float,2,2> C
    {{{
        {1, 0},
        {0, 1}
    }}};

    EXPECT_EQ(exp<ACCURACY>(A), C);
}

TEST(Exp, MatricesExpExp)
{
    constexpr auto ACCURACY = 10;

    Matrix<float,2,2> A
    {{{
        {0, 0},
        {0, 0}
    }}};

    auto B = exp<ACCURACY>(exp<ACCURACY>(A));

    Matrix<float,2,2> C
    {{{
        {2.718, 0    },
        {0    , 2.718}
    }}};

    B.onEachElement(round<float,3>); // for equality
    EXPECT_EQ(B, C);
}

TEST(Exp, Sandbox)
{
    constexpr auto ACCURACY = 10;

    Matrix<float,2,2> A
    {{{
        {0, -1},
        {1, 0}
    }}};

    std::cout << "A "<< A << std::endl;
    std::cout << "exp(A) "<< exp<10>(A) << std::endl;
    std::cout << "exp(exp(A)) "<< exp<10>(exp<10>(A)) << std::endl;
}