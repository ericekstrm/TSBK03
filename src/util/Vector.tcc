#include "Vector.h"

#include <stdexcept>
#include <cmath>
#include <stdexcept>

template <int N>
Vector<N>::Vector()
{
    for (int i = 0; i < N; i++)
    {
        x[i] = 0;
    }
}

template<int N>
Vector<N>::Vector(Vector<N> const & rhs)
{
    for (int i = 0; i < N; i++)
    {
        x[i] = rhs.x[i];
    }
}

template<int N>
Vector<N>::Vector(std::initializer_list<float> list)
{
    if (list.size() != N)
    {
        throw std::domain_error("Dimension missmatch in constructor of Vector.");
    }

    for (int i = 0; i < N; i++)
    {
        x[i] = *(list.begin() + i);
    }
}

template<int N>
float Vector<N>::length() const
{
    float sum {0};

    for (int i = 0; i < N; i++)
    {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}

template<int N>
void Vector<N>::normalize()
{
    operator/=(length());
}

template<int N>
Vector<N>::Vector(float tmp[N])
{
    for (int i = 0; i < N; i++)
    {
        x[i] = tmp[i];
    }
}

template <int N>
Vector<N>::~Vector()
{
}

template<int N>
Vector<N> Vector<N>::operator=(Vector<N> const & rhs)
{
    for (int i = 0; i < N; i++)
    {
        x[i] = rhs.x[i];
    }
    return *this;
}

template<int N>
Vector<N> Vector<N>::operator+(Vector<N> const & rhs) const
{
    float tmp[N];
    for (int i = 0; i < N; i++)
    {
        tmp[i] = x[i] + rhs.x[i];
    }
    return Vector<N>(tmp);
}

template<int N>
Vector<N> Vector<N>::operator+=(Vector<N> const & rhs)
{
    *this = operator+(rhs);
    return *this;
}

template<int N>
Vector<N> Vector<N>::operator-(Vector<N> const & rhs) const
{
    float tmp[N];
    for (int i = 0; i < N; i++)
    {
        tmp[i] = x[i] - rhs.x[i];
    }
    return Vector<N>(tmp);
}

template<int N>
Vector<N> Vector<N>::operator-=(Vector<N> const & rhs)
{
    *this = operator-(rhs);
    return *this;
}

template<int N>
Vector<N> Vector<N>::operator*(float f) const
{
    float tmp[N];
    for (int i = 0; i < N; i++)
    {
        tmp[i] = x[i] * f;
    }
    return Vector<N> {tmp};
}

template<int N>
Vector<N> Vector<N>::operator*=(float f)
{
    *this = operator*(f);
    return *this;
}

template<int N>
Vector<N> Vector<N>::operator/(float f) const
{
    return operator*(1.0f / f);
}

template<int N>
Vector<N> Vector<N>::operator/=(float f)
{
    *this = operator/(f);
    return *this;
}

template<int N>
float& Vector<N>::operator[](int index)
{
    if (index >= N)
    {
        throw std::logic_error("index out of bounds in vector.");
    }
    return x[index];
}

template<int N>
float Vector<N>::operator[](int index) const
{
    if (index >= N)
    {
        throw std::logic_error("index out of bounds in vector.");
    }
    return x[index];
}

template<int N>
float Vector<N>::operator*(Vector<N> const & rhs)
{
    float sum {0};

    for (int i = 0; i < N; i++)
    {
        sum += x[i] * rhs.x[i];
    }
    return sum;
}

template<int N>
bool Vector<N>::operator==(Vector<N> const & rhs) const
{
    for (int i = 0; i < N; i++)
    {
        if (x[i] != rhs.x[i])
        {
            return false;
        }
    }
    return true;
}

template<int N>
bool Vector<N>::operator!=(Vector<N> const & rhs) const
{
    return !(*this == rhs);
}

template<int N>
std::ostream& operator<<(std::ostream & os, Vector<N> const & rhs)
{
    os << "[";
    for (int i = 0; i < N-1; i++)
    {
        os << rhs[i] << ", ";
    }
    os << rhs[N-1] << "]";
    return os;
}