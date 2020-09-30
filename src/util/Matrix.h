#pragma once

#include <type_traits>
#include "Vector.h"

#include <vector>

class Matrix4
{
public:
    Matrix4();
    Matrix4(Matrix4 const&);
    Matrix4(std::initializer_list<float> list);
    ~Matrix4();
    Matrix4 operator=(Matrix4 const&);

    Matrix4 operator*(float) const;
    Matrix4 operator*=(float);
    Matrix4 operator/(float) const;
    Matrix4 operator/=(float);

    Matrix4 operator*(Matrix4 const&) const;

    Vector<3> operator*(Vector<3> const&) const;
    Vector<4> operator*(Vector<4> const&) const;

    bool operator==(Matrix4 const&) const;
    bool operator!=(Matrix4 const&) const;

    Matrix4 inverse() const;
    float determinant() const;
    Matrix4 transpose() const;
    Matrix4 remove_translation();

    float m[4][4];

private:
    Matrix4(float tmp[4][4]);
};

std::ostream& operator<<(std::ostream & os, Matrix4 const & rhs);

Matrix4 frustum_projection_matrix(float near, float far, float right, float left, float top, float bottom);
Matrix4 fov_projection_matrix(float fovy, float aspect, float near, float far);

Matrix4 look_at(Vector<3> position, Vector<3> look_at, Vector<3> up_vector);

Matrix4 rotation_matrix(float angle, float x, float y, float z);
Matrix4 rotation_matrix(float x, float y, float z);
Matrix4 translation_matrix(float x, float y, float z);
Matrix4 scale_matrix(float x, float y, float z);

