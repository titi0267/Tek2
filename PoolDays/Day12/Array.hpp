/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD12-timothe.coniel
** File description:
** Array
*/

#include <iostream>
#include <exception>
#include <functional>
#include <vector>
#ifndef ARRAY_HPP_
#define ARRAY_HPP_

template<typename Type, size_t Size>
class Array {
    public:
        Array() : _array(std::vector<Type>{Size}) {};

        Type &operator[](size_t);
        const Type operator[](size_t) const;
        std::size_t size() const;
        void forEach(const std::function<void(const Type&)>& task) const;
        template <typename U>
        Array<U, Size> convert(const std::function <U(const Type&)>& converter) const;

    protected:
        std::vector<Type> _array;
    private:
};

template<typename T, size_t Size>
T &Array<T,Size>::operator[](size_t index)
{
    if (index >= Size)
        throw std::invalid_argument("Out of range");
    return _array[index];
}

template<typename T, size_t Size>
const T Array<T,Size>::operator[](size_t index) const
{
    if (index >= Size)
        throw std::invalid_argument("Out of range");
    return _array[index];
}

template<typename Type, size_t Size>
std::ostream &operator<<(std::ostream &os, const Array<Type, Size> &array)
{
    os << "[";
    for (size_t i = 0; i < Size - 1; i++)
        os << array[i] << ", ";
    os << array[Size - 1] << "]";
    return os;
}

template<typename Type, size_t Size>
std::size_t Array<Type, Size>::size() const
{
    return Size;
}

template<typename Type, size_t Size>
void Array<Type, Size>::forEach(const std::function <void(const Type &)>& task) const
{
    for (size_t i = 0; i < Size; i++)
        task(_array[i]);
}

template<typename Type, size_t Size>
template<typename U>
Array<U, Size> Array<Type, Size>::convert(const std::function <U(const Type&)>& converter) const
{
    Array<U, Size> arrayU;

    for (size_t i = 0; i < Size; i++)
        arrayU[i] = converter(_array[i]);
    return arrayU;
}

#endif /* !ARRAY_HPP_ */
