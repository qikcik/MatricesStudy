#pragma once

#include <memory>
#include <array>
#include <functional>



template<typename TType>
class DynamicMatrix
{
public:

    explicit DynamicMatrix(size_t inX = 0,size_t inY = 0);
    DynamicMatrix(const DynamicMatrix& inOriginal);
    DynamicMatrix& operator=(const DynamicMatrix& t);

    ~DynamicMatrix();


    static DynamicMatrix Identity(size_t inSize);

    void resize(size_t inSizeX, size_t inSizeY);
    void unsafeSetFromRaw(std::initializer_list<TType> array);

    DynamicMatrix pow(size_t in_exponent) const;

    size_t getSizeX() const;
    size_t getSizeY() const;

    inline TType& at(size_t inY,size_t inX );
    inline const TType& at(size_t inX,size_t inY ) const;


    void performOnEachElement(std::function<void(TType&)> inOperation);
    void performOnEachElement(const DynamicMatrix& inSecond,std::function<void(TType& inFirst,const TType& inSecond)> inOperation);

    template<typename _TType>
    friend DynamicMatrix<_TType> operator+(
            const DynamicMatrix<_TType>& lhs,
            const DynamicMatrix<_TType>& rhs
    );

    template<typename _TType>
    friend DynamicMatrix<_TType> operator*(
            const DynamicMatrix<_TType>& lhs,
            const DynamicMatrix<_TType>& rhs
    );

    template<typename _TType>
    friend DynamicMatrix<_TType> operator*(
            const DynamicMatrix<_TType>& lhs,
            const _TType& rhs
    );

    template<typename _TType>
    friend bool operator==(
            const DynamicMatrix<_TType>& lhs,
            const DynamicMatrix<_TType>& rhs
    );


protected:
    TType** array {nullptr};
    size_t sizeX {0};
    size_t sizeY {0};
};











