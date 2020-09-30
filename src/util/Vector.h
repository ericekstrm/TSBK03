#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

#include "OBJ_Loader.h"

#define vec2 Vector<2>
#define vec3 Vector<3>
#define vec4 Vector<4>

template <int N>
class Vector
{
public:
    Vector();
    Vector(Vector<N> const&);
    Vector(std::initializer_list<float> list);
    ~Vector();
    Vector<N> operator=(Vector<N> const&);
    vec3& operator=(objl::Vector3 const&);

    Vector<N> operator+(Vector<N> const&) const;
    Vector<N> operator+=(Vector<N> const&);
    Vector<N> operator-(Vector<N> const&) const;
    Vector<N> operator-=(Vector<N> const&);

    Vector<N> operator*(float) const;
    Vector<N> operator*=(float);
    Vector<N> operator/(float) const;
    Vector<N> operator/=(float);

    float& operator[](int);
    float operator[](int) const;

    // dot product
    float operator*(Vector<N> const&);

    bool operator==(Vector<N> const&) const;
    bool operator!=(Vector<N> const&) const;

    float length() const;
    void normalize();

private:
    Vector(float tmp[N]);

    float x[N];
};

Vector<3> cross(Vector<3> const& lhs, Vector<3> const& rhs);

#include "Vector.tcc"

#endif