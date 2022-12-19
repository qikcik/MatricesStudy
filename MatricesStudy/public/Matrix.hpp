#pragma once

#include <memory>
#include <array>
#include <functional>

enum class SpecialType {Identity};



template<typename TType,size_t TYSize, size_t TXSize>
class Matrix
{
public:
    static_assert(TYSize != 0 && TXSize != 0, "Cannot make Matrix with dimension size: 0");
    using TArray = typename std::array<std::array<TType,TXSize>, TYSize>;


    explicit Matrix();
    explicit Matrix(const TArray& in_value);

    void onEachElement(std::function<void(TType&)> in_operation);

    static Matrix<TType,TYSize,TXSize> Identity() requires (TYSize == TXSize);

    Matrix<TType,TYSize,TXSize> pow(size_t in_exponent) const;

    template<typename TType_friend,size_t TYSize_friend, size_t TXSize_friend,typename TRhs>
    friend Matrix<TType_friend,TYSize_friend,TXSize_friend> operator+(
        const Matrix<TType_friend,TYSize_friend,TXSize_friend>& lhs,
        const TRhs& rhs
    );

    template<typename TType_friend,size_t TYSize_friend, size_t TXSize_friend,typename TRhs>
    friend Matrix<TType_friend,TYSize_friend,TXSize_friend> operator*(
        const Matrix<TType_friend,TYSize_friend,TXSize_friend>& lhs,
        const TRhs& rhs
    );

    template<typename TType_friend,size_t TYSize_friend, size_t TXSize_friend>
    friend Matrix<TType_friend,TYSize_friend,TXSize_friend> operator+(
        const Matrix<TType_friend,TYSize_friend,TXSize_friend>& lhs,
        const Matrix<TType_friend,TYSize_friend,TXSize_friend>& rhs
    );

    template<typename TType_friend, size_t T_LY_Size_friend, size_t T_LX_RY_Size_friend, size_t T_RX_Size_friend>
    friend Matrix<TType_friend, T_LY_Size_friend, T_RX_Size_friend> operator*(
        const Matrix<TType_friend, T_LY_Size_friend, T_LX_RY_Size_friend>& lhs,
        const Matrix<TType_friend, T_LX_RY_Size_friend, T_RX_Size_friend>& rhs
    );

    template<typename TType_friend,size_t TYSize_friend, size_t TXSize_friend>
    friend bool operator==(
        const Matrix<TType_friend,TYSize_friend,TXSize_friend>& lhs,
        const Matrix<TType_friend,TYSize_friend,TXSize_friend>& rhs
    );

    inline size_t getXSize() {return TXSize;};
    inline size_t getYSize() {return TXSize;};

    template<size_t TY, size_t TX >
    inline constexpr TType& at();

    inline TType& at(size_t in_y,size_t in_x );
    inline const TType& at(size_t in_y,size_t in_x ) const;

protected:
    TArray m_value;

};



