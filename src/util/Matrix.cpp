#include "Matrix.h"
#include "Vector.h"

#include <cmath>
#include <iostream>

#include "Matrix.h"

Matrix4::Matrix4()
    : Matrix4 {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1}
{
    
}

Matrix4::Matrix4(Matrix4 const & rhs)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = rhs.m[i][j];
        }
    }
}

Matrix4::Matrix4(std::initializer_list<float> list)
{
    if (list.size() != 16)
    {
        throw std::logic_error("dimension missmatch in matrix constructor.");
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = *(list.begin() + i * 4 + j);
        }
    }
}

Matrix4::~Matrix4()
{
}

Matrix4 Matrix4::operator=(Matrix4 const & rhs)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = rhs.m[i][j];
        }
    }
    return *this;
}

Matrix4 Matrix4::operator*(float f) const
{
    float tmp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = m[i][j] * f;
        }
    }
    return Matrix4 {tmp};
}

Matrix4 Matrix4::operator*=(float f)
{
    *this = operator*(f);
    return *this;
}

Matrix4 Matrix4::operator/(float f) const
{
    return operator*(1 / f);
}

Matrix4 Matrix4::operator/=(float f)
{
    *this = operator/(f);
    return *this;
}

Matrix4 Matrix4::operator*(Matrix4 const & rhs) const
{
    Matrix4 tmp {};
    tmp.m[0][0] = m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0] + m[0][2] * rhs.m[2][0] + m[0][3] * rhs.m[3][0];
    tmp.m[1][0] = m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0] + m[1][2] * rhs.m[2][0] + m[1][3] * rhs.m[3][0];
    tmp.m[2][0] = m[2][0] * rhs.m[0][0] + m[2][1] * rhs.m[1][0] + m[2][2] * rhs.m[2][0] + m[2][3] * rhs.m[3][0];
    tmp.m[3][0] = m[3][0] * rhs.m[0][0] + m[3][1] * rhs.m[1][0] + m[3][2] * rhs.m[2][0] + m[3][3] * rhs.m[3][0];

    tmp.m[0][1] = m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1] + m[0][2] * rhs.m[2][1] + m[0][3] * rhs.m[3][1];
    tmp.m[1][1] = m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1] + m[1][2] * rhs.m[2][1] + m[1][3] * rhs.m[3][1];
    tmp.m[2][1] = m[2][0] * rhs.m[0][1] + m[2][1] * rhs.m[1][1] + m[2][2] * rhs.m[2][1] + m[2][3] * rhs.m[3][1];
    tmp.m[3][1] = m[3][0] * rhs.m[0][1] + m[3][1] * rhs.m[1][1] + m[3][2] * rhs.m[2][1] + m[3][3] * rhs.m[3][1];
    
    tmp.m[0][2] = m[0][0] * rhs.m[0][2] + m[0][1] * rhs.m[1][2] + m[0][2] * rhs.m[2][2] + m[0][3] * rhs.m[3][2];
    tmp.m[1][2] = m[1][0] * rhs.m[0][2] + m[1][1] * rhs.m[1][2] + m[1][2] * rhs.m[2][2] + m[1][3] * rhs.m[3][2];
    tmp.m[2][2] = m[2][0] * rhs.m[0][2] + m[2][1] * rhs.m[1][2] + m[2][2] * rhs.m[2][2] + m[2][3] * rhs.m[3][2];
    tmp.m[3][2] = m[3][0] * rhs.m[0][2] + m[3][1] * rhs.m[1][2] + m[3][2] * rhs.m[2][2] + m[3][3] * rhs.m[3][2];

    tmp.m[0][3] = m[0][0] * rhs.m[0][3] + m[0][1] * rhs.m[1][3] + m[0][2] * rhs.m[2][3] + m[0][3] * rhs.m[3][3];
    tmp.m[1][3] = m[1][0] * rhs.m[0][3] + m[1][1] * rhs.m[1][3] + m[1][2] * rhs.m[2][3] + m[1][3] * rhs.m[3][3];
    tmp.m[2][3] = m[2][0] * rhs.m[0][3] + m[2][1] * rhs.m[1][3] + m[2][2] * rhs.m[2][3] + m[2][3] * rhs.m[3][3];
    tmp.m[3][3] = m[3][0] * rhs.m[0][3] + m[3][1] * rhs.m[1][3] + m[3][2] * rhs.m[2][3] + m[3][3] * rhs.m[3][3];
    
    return tmp;
}

Vector<3> Matrix4::operator*(Vector<3> const & rhs) const
{
    float x = m[0][0] * rhs[0] + m[0][1] * rhs[1] + m[0][2] * rhs[2] + m[0][3] * 1;
    float y = m[1][0] * rhs[0] + m[1][1] * rhs[1] + m[1][2] * rhs[2] + m[1][3] * 1;
    float z = m[2][0] * rhs[0] + m[2][1] * rhs[1] + m[2][2] * rhs[2] + m[2][3] * 1;
    float w = m[3][0] * rhs[0] + m[3][1] * rhs[1] + m[3][2] * rhs[2] + m[3][3] * 1;
    return Vector<3> {x / w, y / w, z / w};
}

Vector<4> Matrix4::operator*(Vector<4> const& rhs) const
{
    float x = m[0][0] * rhs[0] + m[0][1] * rhs[1] + m[0][2] * rhs[2] + m[0][3] * rhs[3];
    float y = m[1][0] * rhs[0] + m[1][1] * rhs[1] + m[1][2] * rhs[2] + m[1][3] * rhs[3];
    float z = m[2][0] * rhs[0] + m[2][1] * rhs[1] + m[2][2] * rhs[2] + m[2][3] * rhs[3];
    float w = m[3][0] * rhs[0] + m[3][1] * rhs[1] + m[3][2] * rhs[2] + m[3][3] * rhs[3];
    return Vector<4> {x, y, z, w};
}

bool Matrix4::operator==(Matrix4 const & rhs) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m[i][j] != rhs.m[i][j])
            {
                return false;
            }

        }
    }
    return true;
}

bool Matrix4::operator!=(Matrix4 const & rhs) const
{
    return !(*this == rhs);
}

//TODO: inverse

// TODO
float Matrix4::determinant() const
{
    return 0.0f;
}

Matrix4 Matrix4::transpose() const
{
    float tmp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j][i] = m[i][j];
        }
    }
    return Matrix4 {tmp};
}

Matrix4 Matrix4::remove_translation()
{
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    return *this;
}

Matrix4::Matrix4(float tmp[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = tmp[i][j];
        }
    }
}

std::ostream& operator<<(std::ostream & os, Matrix4 const & rhs)
{
    os << "[";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            os << rhs.m[i][j] << ", ";
        }
        os << "\n";
    }
    os << "]";
    return os;
}


Matrix4 frustum_projection_matrix(float near, float far, float right, float left, float top, float bottom)
{
    Matrix4 frustum {};

    frustum.m[0][0] = (2.0f * near) / (right - left);
    frustum.m[0][2] = (right + left) / (right - left);
    frustum.m[1][1] = (2.0f * near) / (top - bottom);
    frustum.m[1][2] = (top + bottom) / (top - bottom);
    frustum.m[2][2] = -(far + near) / (far - near);
    frustum.m[2][3] = -(2.0f * far * near) / (far - near);
    frustum.m[3][2] = -1;
    frustum.m[3][3] = 0;

    return frustum;
}

Matrix4 fov_projection_matrix(float fovy, float aspect, float near, float far)
{
    float const rad = fovy * 3.1415f / 180.0f;
    float const tanHalfFovy = tan(rad / 2.0f);

    Matrix4 result {};
    result.m[0][0] = 1 / (aspect * tanHalfFovy);
    result.m[1][1] = 1 / (tanHalfFovy);
    result.m[2][2] = - (far + near) / (far - near);
    result.m[3][2] = - 1;
    result.m[2][3] = - (2 * far * near) / (far - near);
    return result;
}

Matrix4 look_at(Vector<3> position, Vector<3> look_at, Vector<3> up_vector)
{
    Vector<3> n {position - look_at};
    n.normalize();
    Vector<3> u {cross(up_vector, n)};
    u.normalize();
    Vector<3> v {cross(n, u)};

    Matrix4 rotation
    {
        u[0], u[1], u[2], 0,
        v[0], v[1], v[2], 0,
        n[0], n[1], n[2], 0,
        0, 0, 0, 1
    };
    
    Matrix4 translation {translation_matrix(-position[0], -position[1], -position[2])};

    return (rotation * translation);
}

//angle of rotation is in degrees
Matrix4 rotation_matrix(float angle, float x, float y, float z)
{
    Matrix4 matrix {};

    float c = (float) cos(angle * 3.1415 / 180);
    float s = (float) sin(angle * 3.1415 / 180);
    Vector<3> vec {x, y, z};
    if (vec.length() != 1)
    {
        vec.normalize();
        x = vec[0];
        y = vec[1];
        z = vec[2];
    }

    matrix.m[0][0] = x * x * (1 - c) + c;
    matrix.m[1][0] = y * x * (1 - c) + z * s;
    matrix.m[2][0] = x * z * (1 - c) - y * s;
    matrix.m[0][1] = x * y * (1 - c) - z * s;
    matrix.m[1][1] = y * y * (1 - c) + c;
    matrix.m[2][1] = y * z * (1 - c) + x * s;
    matrix.m[0][2] = x * z * (1 - c) + y * s;
    matrix.m[1][2] = y * z * (1 - c) - x * s;
    matrix.m[2][2] = z * z * (1 - c) + c;
    matrix.m[3][3] = 1;

    return matrix;
}

Matrix4 rotation_matrix(float x, float y, float z)
{
    return rotation_matrix(x, 1, 0, 0) *
           rotation_matrix(x, 0, 1, 0) *
           rotation_matrix(x, 0, 0, 1);
}

Matrix4 translation_matrix(float x, float y, float z)
{
    Matrix4 matrix {};

    matrix.m[0][0] = 1;
    matrix.m[1][1] = 1;
    matrix.m[2][2] = 1;
    matrix.m[3][3] = 1;
    matrix.m[0][3] = x;
    matrix.m[1][3] = y;
    matrix.m[2][3] = z;

    return matrix;
}

Matrix4 scale_matrix(float x, float y, float z)
{
    return Matrix4 {
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
}
