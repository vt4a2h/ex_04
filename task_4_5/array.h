#pragma once
#include <exception>
#include <algorithm>
#include <stdio.h>

// CQRS is not for marcos!
#define CHECK_AND_RETURN(len, index) if (index >= len) throw BadIndex(); return m_Array[index];

namespace fixed_arrays {

    class BadIndex : public std::exception { const char* what() const throw() { return "bad array index"; } };

    /*! \brief Класс ConstantSizeArray представляет собой реализацию одномерного статического массива. */
    template <class Type>
    class ConstantSizeArray
    {
    public:
        ConstantSizeArray(size_t size) :  m_Array(new Type[size]), m_Size(size) {}
        ConstantSizeArray(std::initializer_list<Type> l);
        ConstantSizeArray(const ConstantSizeArray &src);
        ConstantSizeArray(ConstantSizeArray &&src);
        virtual ~ConstantSizeArray() {delete []m_Array; }

        ConstantSizeArray& operator =(const ConstantSizeArray &rhs);
        ConstantSizeArray& operator =(ConstantSizeArray &&rhs);
        Type& operator[](size_t index)             { CHECK_AND_RETURN(m_Size, index) }
        const Type& operator[](size_t index) const { CHECK_AND_RETURN(m_Size, index) }

        const Type& at(size_t index) const { CHECK_AND_RETURN(m_Size, index) }
        size_t size() const { return m_Size; }
        bool empty()  const { return m_Size != 0 ? true : false; }

        Type* begin() { return m_Array;}
        const Type* begin() const { return m_Array;}

        Type* end() { return m_Array + m_Size;}
        const Type* end() const { return m_Array + m_Size;}

    private:
        void move(ConstantSizeArray &src, ConstantSizeArray &dst);

        Type  *m_Array;
        size_t m_Size;
    };

    template <class Type>
    ConstantSizeArray<Type>::ConstantSizeArray(std::initializer_list<Type> l)
    {
        ConstantSizeArray<int> tmp(l.size());
        std::copy(l.begin(), l.end(), tmp.begin());
        move(tmp, *this);
    }

    template <class Type>
    ConstantSizeArray<Type>::ConstantSizeArray(const ConstantSizeArray &src)
    {
        ConstantSizeArray<Type> tmp(src.size());
        std::copy(src.begin(), src.end(), tmp.begin());
        move(tmp, *this);
    }

    template <class Type>
    ConstantSizeArray<Type>& ConstantSizeArray<Type>::operator=(const ConstantSizeArray &rhs)
    {
        if (this != &rhs) {
            auto tmp(rhs);
            move(tmp, *this);
        }

        return *this;
    }

    template <class Type>
    ConstantSizeArray<Type>& ConstantSizeArray<Type>::operator=(ConstantSizeArray &&rhs)
    {
        if (this != &rhs) {
            delete []m_Array;
            move(rhs, *this);
        }

        return *this;
    }

    template <class Type>
    ConstantSizeArray<Type>::ConstantSizeArray(ConstantSizeArray &&src)
    {
        move(src, *this);
    }

    template <class Type>
    void ConstantSizeArray<Type>::move(ConstantSizeArray &src, ConstantSizeArray &dst)
    {
        std::swap(src.m_Array, dst.m_Array); // move?
        std::swap(src.m_Size, dst.m_Size);
        src.m_Array = nullptr;
        src.m_Size  = 0;
    }

} // namespace array
