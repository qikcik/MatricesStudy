#include "Matrix.hpp"
#include "dynamic/DynamicMatrix.hpp"

template<typename T>
T factorial (T x){
    T result = 1;
    for (int i = 0; i < x; i++)
    {
        result = result * (i+1);
    }
    return result;
}

//for Matrix Math library support
template<typename TType, size_t TYSize, size_t TXSize>
Matrix<TType,TYSize,TXSize> pow(const Matrix<TType,TYSize,TXSize>& in_operand,size_t in_exponent)
{
    return in_operand.pow(in_exponent);
}

//for Matrix Math library support
template<typename TType>
DynamicMatrix<TType> pow(const DynamicMatrix<TType>& in_operand,size_t in_exponent)
{
    return in_operand.pow(in_exponent);
}


template<size_t TAccuracy,typename T>
requires (TAccuracy > 0)
T exp(T in_operand)
{
    T result = pow(in_operand,0);

    for (size_t accuracyIt = 1; accuracyIt < TAccuracy; accuracyIt++)
    {
        result = result + ( pow(in_operand,accuracyIt) * (1.f/(float)factorial(accuracyIt)) );
    }
    return result;
}

template<typename TType,int TDecimalPlaces>
requires (std::is_arithmetic<TType>::value)
void round(TType& num)
{
    TType factor = std::pow(10, TDecimalPlaces);
    num = std::round(num * factor) / factor;
}


