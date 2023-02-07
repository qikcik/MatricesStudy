#pragma once

#include <concepts>
#include "DynamicMatrix.hpp"

#include <iostream>
#include <exception>

template<typename TType>
DynamicMatrix<TType>::DynamicMatrix(size_t inX, size_t inY)
{
    resize(inX,inY);
}

template<typename TType>
DynamicMatrix<TType>::DynamicMatrix(const DynamicMatrix &inOriginal)
{
    resize(inOriginal.sizeX,inOriginal.sizeY);
    performOnEachElement(inOriginal,[] (TType& inFirst,const TType& inSecond) {
        inFirst = inSecond;
    });
}

template<typename TType>
DynamicMatrix<TType> DynamicMatrix<TType>::Identity(size_t inSize)
{
    DynamicMatrix<TType> result(inSize,inSize);

    for(size_t yInx = 0 ; yInx != inSize ; yInx++)
        for(size_t xInx = 0 ; xInx != inSize ; xInx++)
            if(yInx == xInx)
                result.at(yInx,xInx) = 1;

    return result;
}


template<typename TType>
DynamicMatrix<TType>::~DynamicMatrix()
{
    for(size_t xInx = 0 ; xInx != sizeX ; xInx++)
    {
        delete array[xInx];
    }
    delete array;
}

template<typename TType>
DynamicMatrix<TType> &DynamicMatrix<TType>::operator=(const DynamicMatrix &t)
{
    resize(t.sizeX,t.sizeY);
    performOnEachElement(t,[] (TType& inFirst,const TType& inSecond) {
        inFirst = inSecond;
    });
    return *this;
}



template<typename TType>
void DynamicMatrix<TType>::unsafeSetFromRaw(std::initializer_list<TType> array)
{
    auto it = array.begin();
    for(size_t xInx = 0 ; xInx != sizeX ; xInx++)
        for(size_t yInx = 0 ; yInx != sizeY ; yInx++)
        {
            at(xInx, yInx) = *it;
            it++;
        }
}

template<typename TType>
void DynamicMatrix<TType>::resize(size_t inSizeX, size_t inSizeY)
{
    auto oldArray = array;


    array = new TType*[inSizeX];

    for(size_t xInx = 0 ; xInx != inSizeX ; xInx++)
    {
        array[xInx] = new TType[inSizeY];
        for(size_t yInx = 0 ; yInx != inSizeY ; yInx++)
        {
            array[xInx][yInx] = {};
        }
    }

    for(size_t xInx = 0 ; xInx != (sizeX < inSizeX ? sizeX : inSizeX) ; xInx++)
    {
        for(size_t yInx = 0 ; yInx != (sizeY < inSizeY ? sizeX : inSizeY) ; yInx++)
        {
            array[xInx][yInx] = oldArray[xInx][yInx];
        }
    }


    for(size_t xInx = 0 ; xInx != sizeX ; xInx++)
    {
        delete oldArray[xInx];
    }
    delete oldArray;

    sizeX = inSizeX;
    sizeY = inSizeY;

}


template<typename TType>
const TType &DynamicMatrix<TType>::at(size_t inX, size_t inY) const
{
    if(inX > sizeX-1 && inY > sizeY-1 )
        throw std::invalid_argument(
                "try to read unallocated memory, try read: "+
                std::to_string(inX)+","+std::to_string(inY)
        );

    return array[inX][inY];
}

template<typename TType>
TType &DynamicMatrix<TType>::at(size_t inX, size_t inY)
{
    if(inX > sizeX-1 && inY > sizeY-1 )
        throw std::invalid_argument(
            "try to read unallocated memory, try read: "+
            std::to_string(inX)+","+std::to_string(inY)
        );

    return array[inX][inY];
}


template<typename TType>
size_t DynamicMatrix<TType>::getSizeX() const
{
    return sizeX;
}

template<typename TType>
size_t DynamicMatrix<TType>::getSizeY() const
{
    return sizeY;
}

template<typename TType>
void DynamicMatrix<TType>::performOnEachElement(std::function<void(TType &)> inOperation)
{
    for(size_t xInx = 0 ; xInx != sizeX ; xInx++)
        for(size_t yInx = 0 ; yInx != sizeY ; yInx++)
            inOperation(at(xInx,yInx));
}

template<typename TType>
void DynamicMatrix<TType>::performOnEachElement(const DynamicMatrix& inSecond,std::function<void(TType& inFirst,const TType& inSecond)> inOperation)
{
    for(size_t xInx = 0 ; xInx != sizeX ; xInx++)
        for(size_t yInx = 0 ; yInx != sizeY ; yInx++)
            inOperation(at(xInx,yInx),inSecond.at(xInx,yInx));
}
template<typename TType>
DynamicMatrix<TType> operator+(const DynamicMatrix<TType> &lhs, const DynamicMatrix<TType> &rhs)
{
    DynamicMatrix<TType> result = lhs;

    result.performOnEachElement(rhs,[] (TType& inFirst,const TType& inSecond) {
        inFirst = inFirst+inSecond;
    });

    return result;
}


template<typename TType>
DynamicMatrix<TType> operator*(const DynamicMatrix<TType> &lhs, const TType &rhs)
{
    DynamicMatrix<TType> result = lhs;

    result.performOnEachElement([rhs] (TType& inEl) {
        inEl = inEl*rhs;
    });

    return result;
}


template<typename TType>
DynamicMatrix<TType> operator*(const DynamicMatrix<TType> &lhs, const DynamicMatrix<TType> &rhs)
{
    DynamicMatrix<TType> result;
    result.resize(lhs.sizeX,rhs.sizeY);

    if(lhs.sizeY != rhs.sizeX) throw std::invalid_argument("invalid size to multiply");

    for(size_t xInx = 0 ; xInx != lhs.sizeX ; xInx++)
        for(size_t yInx = 0 ; yInx != rhs.sizeY ; yInx++)
            for(size_t kInx = 0 ; kInx != lhs.sizeY ; kInx++)
                result.at(xInx, yInx) += lhs.at(xInx, kInx) * rhs.at(kInx, yInx);

    return result;
}


template<typename TType>
bool operator==(const DynamicMatrix<TType> &lhs, const DynamicMatrix<TType> &rhs)
{
    if(lhs.sizeX != rhs.sizeX && lhs.sizeY != rhs.sizeY) return false;

    for(size_t xInx = 0 ; xInx != lhs.sizeX ; xInx++)
        for(size_t yInx = 0 ; yInx != lhs.sizeY ; yInx++)
            if( lhs.at(xInx,yInx) != rhs.at(xInx,yInx) )
                return false;

    return true;
}

template<typename TType>
std::ostream& operator<<(std::ostream& os, const DynamicMatrix<TType>& mat)
{
    os << "["<<mat.getSizeX()<<"]["<<mat.getSizeY()<<"] = \n{\n";

    for(size_t yInx = 0 ; yInx != mat.getSizeX() ; yInx++)
    {
        os << "\t";
        for(size_t xInx = 0 ; xInx != mat.getSizeY() ; xInx++)
        {
            os << mat.at(yInx,xInx) << ",\t";
        }
        os << "\n";
    }
    os << "}\n";
    return os;
}


template<typename TType>
DynamicMatrix<TType> DynamicMatrix<TType>::pow(size_t in_exponent) const
{
    if(in_exponent == 0)
    {
        if(sizeX != sizeY) throw std::bad_function_call();
        return DynamicMatrix::Identity(sizeX);
    }


    auto result = (*this);
    for(size_t i = 0; i!= in_exponent-1; i++)
        result = result * (*this);

    return result;
}
