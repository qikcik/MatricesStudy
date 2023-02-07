#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "dynamic/DynamicMatrix.hpp"
#include "dynamic/DynamicMatrix.tpp"

TEST(DynamicMatrices, SettingNumbersAndResize)
{
    auto A = DynamicMatrix<float>(1,1);
    A.at(0,0) = 2;

    A.resize(2,2);
    A.at(1,1) = 3;

    auto C = DynamicMatrix<float>(2,2);

    C.unsafeSetFromRaw({
       2,0,
       0,3
    });

    EXPECT_EQ( A.at(0,0), 2);
    EXPECT_EQ( A.at(0,1), 0);
    EXPECT_EQ( A.at(1,0), 0);
    EXPECT_EQ( A.at(1,1), 3);
}

TEST(DynamicMatrices, EqualitySizeTest)
{
    DynamicMatrix<float> A;
    A.resize(2,2);

    DynamicMatrix<float> B;
    B.resize(1,1);

    EXPECT_NE( A, B);
}

TEST(DynamicMatrices, EqualityValueTest)
{
    auto A = DynamicMatrix<float>(2,2);
    A.unsafeSetFromRaw({1,2,3,4});

    EXPECT_EQ( A, A);
}

TEST(DynamicMatrices, CopyConstructorTest)
{
    auto A = DynamicMatrix<float>(2,2);

    {
        auto B = DynamicMatrix<float>(2, 2);
        B.unsafeSetFromRaw({1, 2, 3, 4});

        A = B;
    }


    EXPECT_EQ(A.at(1,1), 4);
}

TEST(DynamicMatrices, Adding)
{
    auto A = DynamicMatrix<float>(2,2);
    A.unsafeSetFromRaw({1, 2, 3, 4});

    A = A+A;

    auto C = DynamicMatrix<float>(2,2);
    C.unsafeSetFromRaw({2, 4, 6, 8});

    EXPECT_EQ( A, C);
}

TEST(DynamicMatrices, MultipingByScalar)
{
    auto A = DynamicMatrix<float>(2,2);
    A.unsafeSetFromRaw({1, 2, 3, 4});

    A = A * 3.f;

    auto C = DynamicMatrix<float>(2,2);
    C.unsafeSetFromRaw({3, 6, 9, 12});

    EXPECT_EQ( A, C);
}

TEST(DynamicMatrices, Mulitplying)
{
    auto A = DynamicMatrix<float>(2,3);
    A.unsafeSetFromRaw({1, 2, 3, 4, 5, 6});

    auto B = DynamicMatrix<float>(3,2);
    B.unsafeSetFromRaw({10, 11, 20, 21, 30, 31});

    auto C = DynamicMatrix<float>(2,2);
    C.unsafeSetFromRaw({140, 146, 320, 335});

    EXPECT_EQ( A * B ,C);
}

TEST(DynamicMatrices, Idendity)
{
    auto A = DynamicMatrix<float>(2,2);
    A.unsafeSetFromRaw({1, 0, 0, 1});

    EXPECT_EQ(A, DynamicMatrix<float>::Identity(2));


}

TEST(DynamicMatrices, MatrixPow)
{
    auto A = DynamicMatrix<float>(2,2);
    A.unsafeSetFromRaw({1, 2, 3, 4});

    auto C = DynamicMatrix<float>(2,2);
    C.unsafeSetFromRaw({5743, 8370, 12555, 18298});

    EXPECT_EQ(A.pow(0), A.Identity(2));
    EXPECT_EQ(A.pow(1), A);
    EXPECT_EQ(A.pow(6), C);

}