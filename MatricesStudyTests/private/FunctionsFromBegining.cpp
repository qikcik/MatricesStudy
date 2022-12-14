#include <gtest/gtest.h>
#include <gmock/gmock.h>

template<typename T>
T factorial (T x){
    T result = 1;
    for (int i = 0; i < x; i++)
    {
        result = result * (i+1);
    }
    return result;
}

template<typename T>
T powexp(T x, size_t n)
{
    T sum = 1;
    T u = 0;
    for (size_t i = 0; i < n; i++)
    {
        u = pow(factorial(i + 1), -1) * pow(x, i + 1);
        sum = sum + u;
    }
    return sum;
}

TEST(FunctionsFromBegining, factorialOpeartions)
{

    EXPECT_EQ( factorial(5) ,120);
    EXPECT_EQ( factorial(10),3628800);

    EXPECT_EQ( factorial(0) ,1);
}

TEST(FunctionsFromBegining, powexpOperations)
{
    EXPECT_NEAR( powexp<float>(1,5) ,2.71 ,  0.1);

    EXPECT_NEAR( powexp<float>(2,0) ,1   ,0.1);
    EXPECT_NEAR( powexp<float>(2,1) ,3   ,0.1);
    EXPECT_NEAR( powexp<float>(2,2) ,5   ,0.1);
    EXPECT_NEAR( powexp<float>(2,3) ,6.3 ,0.1);
    EXPECT_NEAR( powexp<float>(2,4) ,7   ,0.1);
    EXPECT_NEAR( powexp<float>(2,5) ,7.3 ,0.1);
}

