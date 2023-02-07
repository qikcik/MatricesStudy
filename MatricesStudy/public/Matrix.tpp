#pragma once

#include <concepts>
#include "Matrix.hpp"

#include <iostream>

template<typename TType,size_t TYSize, size_t TXSize>
Matrix<TType, TYSize, TXSize>::Matrix()
:m_value( {} )
{

}

template<typename TType,size_t TYSize, size_t TXSize>
Matrix<TType, TYSize, TXSize>::Matrix(const TArray& in_value)
: m_value(in_value)
{

}

template<typename TType, size_t TYSize, size_t TXSize>
void Matrix<TType, TYSize, TXSize>::onEachElement(std::function<void(TType &)> in_operation)
{
    for(size_t yInx = 0 ; yInx != TYSize ; yInx++)
        for(size_t xInx = 0 ; xInx != TXSize ; xInx++)
            in_operation(at(yInx,xInx));
}

template<typename TType, size_t TYSize, size_t TXSize>
template<size_t TY, size_t TX>
constexpr TType &Matrix<TType, TYSize, TXSize>::at()
{
    static_assert(TX < TYSize && TY < TXSize, "oversize request");
    return m_value[TY][TX];
}

template<typename TType, size_t TYSize, size_t TXSize>
TType& Matrix<TType, TYSize, TXSize>::at(size_t in_y,size_t in_x)
{
    return m_value[in_y][in_x];
}

template<typename TType, size_t TYSize, size_t TXSize>
const TType& Matrix<TType, TYSize, TXSize>::at(size_t in_y,size_t in_x) const
{
    return m_value[in_y][in_x];
}



template<typename TType, size_t TYSize, size_t TXSize,typename TRhs>
Matrix<TType, TYSize, TXSize> operator+(const Matrix<TType, TYSize, TXSize>& lhs, const TRhs& rhs)
{
    auto result = lhs;

    result.onEachElement([&rhs](auto& op)
    {
        op = op + rhs;
    });

    return result;
}

template<typename TType, size_t TYSize, size_t TXSize,typename TRhs>
Matrix<TType, TYSize, TXSize> operator*(const Matrix<TType, TYSize, TXSize>& lhs, const TRhs& rhs)
{
    auto result = lhs;

    result.onEachElement([&rhs](auto& op)
    {
        op = op * rhs;
    });

    return result;
}

template<typename TType, size_t TYSize, size_t TXSize>
Matrix<TType, TYSize, TXSize> operator+(
        const Matrix<TType, TYSize, TXSize>& lhs,
        const Matrix<TType, TYSize, TXSize>& rhs)
{
    auto result = lhs;

    for(size_t yInx = 0 ; yInx != TYSize ; yInx++)
    for(size_t xInx = 0 ; xInx != TXSize ; xInx++)
        result.at(yInx,xInx) += rhs.at(yInx,xInx);

    return result;
}

template<typename TType, size_t TYSize, size_t TXSize>
bool operator==(const Matrix<TType, TYSize, TXSize>& lhs, const Matrix<TType, TYSize, TXSize>& rhs)
{
    for(size_t yInx = 0 ; yInx != TYSize ; yInx++)
    for(size_t xInx = 0 ; xInx != TXSize ; xInx++)
        if( lhs.at(yInx,xInx) != rhs.at(yInx,xInx) )
            return false;

    return true;
}

template<typename TType_friend, size_t T_LY_Size_friend, size_t T_LX_RY_Size_friend, size_t T_RX_Size_friend>
Matrix<TType_friend, T_LY_Size_friend, T_RX_Size_friend>
operator*(const Matrix<TType_friend, T_LY_Size_friend, T_LX_RY_Size_friend>& lhs,
          const Matrix<TType_friend, T_LX_RY_Size_friend, T_RX_Size_friend>& rhs)
{
    auto result = Matrix<TType_friend, T_LY_Size_friend, T_RX_Size_friend>();

    for(size_t yInx = 0 ; yInx != T_LY_Size_friend ; yInx++)
    for(size_t xInx = 0 ; xInx != T_RX_Size_friend ; xInx++)
        for(size_t kInx = 0 ; kInx != T_LX_RY_Size_friend ; kInx++)
            result.at(yInx, xInx) += lhs.at(yInx, kInx) * rhs.at(kInx, xInx);

    return result;
}

template<typename TType_friend, size_t T_LY_Size_friend, size_t T_LX_RY_Size_friend, size_t T_RX_Size_friend>
Matrix<TType_friend, T_LY_Size_friend, T_RX_Size_friend>
operator/(const Matrix<TType_friend, T_LY_Size_friend, T_LX_RY_Size_friend>& lhs,
          const Matrix<TType_friend, T_LX_RY_Size_friend, T_RX_Size_friend>& rhs)
{
    auto result = Matrix<TType_friend, T_LY_Size_friend, T_RX_Size_friend>();

    for(size_t yInx = 0 ; yInx != T_LY_Size_friend ; yInx++)
        for(size_t xInx = 0 ; xInx != T_RX_Size_friend ; xInx++)
            for(size_t kInx = 0 ; kInx != T_LX_RY_Size_friend ; kInx++)
                result.at(yInx, xInx) += lhs.at(yInx, kInx) * rhs.at(kInx, xInx);

    return result;
}

template<typename TType, size_t TYSize, size_t TXSize>
Matrix<TType, TYSize, TXSize> Matrix<TType, TYSize, TXSize>::Identity() requires (TYSize == TXSize)
{
    Matrix<TType, TYSize, TXSize> result {};

    for(size_t yInx = 0 ; yInx != TYSize ; yInx++)
    for(size_t xInx = 0 ; xInx != TXSize ; xInx++)
        if(yInx == xInx)
            result.at(yInx,xInx) = 1;

    return result;
}


template<typename TType, size_t TYSize, size_t TXSize>
Matrix<TType,TYSize,TXSize> Matrix<TType, TYSize, TXSize>::pow(size_t in_exponent) const
{
    if(in_exponent == 0)
        return Matrix<TType,TYSize,TXSize>::Identity();

    auto result = (*this);
    for(size_t i = 0; i!= in_exponent-1; i++)
        result = result * (*this);

    return result;
}

template<typename TType, size_t TYSize, size_t TXSize>
std::ostream& operator<<(std::ostream& os, const Matrix<TType, TYSize, TXSize>& mat)
{
    os << "["<<TYSize<<"]["<<TXSize<<"] = \n{\n";

    for(size_t yInx = 0 ; yInx != TYSize ; yInx++)
    {
        os << "\t";
        for(size_t xInx = 0 ; xInx != TXSize ; xInx++)
        {
            os << mat.at(yInx,xInx) << ",\t";
        }
        os << "\n";
    }
    os << "}\n";
    return os;
}
