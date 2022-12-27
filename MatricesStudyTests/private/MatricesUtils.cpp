#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "Matrix.tpp"



TEST(Matrices, CreateIdentity)
{
    auto A = Matrix<float,4,4>::Identity();

    Matrix<float,4,4> C
    {{{
        {1,   0,  0,   0},
        {0,   1,  0,   0},
        {0,   0,  1,   0},
        {0,   0,  0,   1}
    }}};


    Matrix<float,4,4> X;
    Matrix<float,3,3> Z;


    EXPECT_EQ(A, C);
}
