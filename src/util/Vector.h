#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

#include "OBJ_Loader.h"

#define vec3 Vector3
#define vec4 Vector4

class Vector3
{
public:
    Vector3();
    Vector3(Vector3 const&);
    Vector3(std::initializer_list<float> list);
    ~Vector3();
    Vector3 operator=(Vector3 const&);

    Vector3(objl::Vector3 const&);
    Vector3& operator=(objl::Vector3 const&);

    Vector3 operator+(Vector3 const&) const;
    Vector3 operator+=(Vector3 const&);
    Vector3 operator-(Vector3 const&) const;
    Vector3 operator-=(Vector3 const&);

    Vector3 operator*(float) const;
    Vector3 operator*=(float);
    Vector3 operator/(float) const;
    Vector3 operator/=(float);
    Vector3 cross(Vector3 const& rhs);

    float& operator[](int);
    float operator[](int) const;

    // dot product
    float operator*(Vector3 const&);

    bool operator==(Vector3 const&) const;
    bool operator!=(Vector3 const&) const;

    float length() const;
    void normalize();

private:
    Vector3(float tmp[3]);

    float x[3];
};

class Vector4
{
public:
    Vector4();
    Vector4(Vector4 const&);
    Vector4(std::initializer_list<float> list);
    ~Vector4();
    Vector4 operator=(Vector4 const&);

    Vector4 operator+(Vector4 const&) const;
    Vector4 operator+=(Vector4 const&);
    Vector4 operator-(Vector4 const&) const;
    Vector4 operator-=(Vector4 const&);

    Vector4 operator*(float) const;
    Vector4 operator*=(float);
    Vector4 operator/(float) const;
    Vector4 operator/=(float);

    float& operator[](int);
    float operator[](int) const;

    // dot product
    float operator*(Vector4 const&);

    bool operator==(Vector4 const&) const;
    bool operator!=(Vector4 const&) const;

    float length() const;
    void normalize();

private:
    Vector4(float tmp[4]);

    float x[4];
};
#endif