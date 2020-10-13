#include "Vector.h"

#include <stdexcept>
#include <cmath>
#include <stdexcept>

Vector3::Vector3()
{
    for (int i = 0; i < 3; i++)
    {
        x[i] = 0;
    }
}

Vector3::Vector3(Vector3 const & rhs)
{
    for (int i = 0; i < 3; i++)
    {
        x[i] = rhs.x[i];
    }
}

Vector3::Vector3(std::initializer_list<float> list)
{
    if (list.size() != 3)
    {
        throw std::domain_error("Dimension missmatch in constructor of Vector.");
    }

    for (int i = 0; i < 3; i++)
    {
        x[i] = *(list.begin() + i);
    }
}

float Vector3::length() const
{
    float sum {0};

    for (int i = 0; i < 3; i++)
    {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}


void Vector3::normalize()
{
    operator/=(length());
}


Vector3::Vector3(float tmp[3])
{
    for (int i = 0; i < 3; i++)
    {
        x[i] = tmp[i];
    }
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator=(Vector3 const & rhs)
{
    for (int i = 0; i < 3; i++)
    {
        x[i] = rhs.x[i];
    }
    return *this;
}

Vector3::Vector3(objl::Vector3 const& rhs)
{
    *this = rhs;
}

vec3& Vector3::operator=(objl::Vector3 const& rhs)
{
	x[0] = rhs.X;
	x[1] = rhs.Y;
	x[2] = rhs.Z;

	return *this;
}

Vector3 Vector3::operator+(Vector3 const & rhs) const
{
    float tmp[3];
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = x[i] + rhs.x[i];
    }
    return Vector3(tmp);
}

Vector3 Vector3::operator+=(Vector3 const & rhs)
{
    *this = operator+(rhs);
    return *this;
}

Vector3 Vector3::operator-(Vector3 const & rhs) const
{
    float tmp[3];
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = x[i] - rhs.x[i];
    }
    return Vector3(tmp);
}

Vector3 Vector3::operator-=(Vector3 const & rhs)
{
    *this = operator-(rhs);
    return *this;
}

Vector3 Vector3::operator*(float f) const
{
    float tmp[3];
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = x[i] * f;
    }
    return Vector3 {tmp};
}

Vector3 Vector3::operator*=(float f)
{
    *this = operator*(f);
    return *this;
}

Vector3 Vector3::operator/(float f) const
{
    return operator*(1.0f / f);
}

Vector3 Vector3::operator/=(float f)
{
    *this = operator/(f);
    return *this;
}

float& Vector3::operator[](int index)
{
    if (index >= 3)
    {
        throw std::logic_error("index out of bounds in vector.");
    }
    return x[index];
}

float Vector3::operator[](int index) const
{
    if (index >= 3)
    {
        throw std::logic_error("index out of bounds in vector.");
    }
    return x[index];
}

float Vector3::operator*(Vector3 const & rhs)
{
    float sum {0};

    for (int i = 0; i < 3; i++)
    {
        sum += x[i] * rhs.x[i];
    }
    return sum;
}

bool Vector3::operator==(Vector3 const & rhs) const
{
    for (int i = 0; i < 3; i++)
    {
        if (x[i] != rhs.x[i])
        {
            return false;
        }
    }
    return true;
}

bool Vector3::operator!=(Vector3 const & rhs) const
{
    return !(*this == rhs);
}

Vector3 Vector3::cross(Vector3 const & rhs)
{
    float x = this->x[1] * rhs[2] - this->x[2] * rhs[1];
    float y = this->x[2] * rhs[0] - this->x[0] * rhs[2];
    float z = this->x[0] * rhs[1] - this->x[1] * rhs[0];
    return Vector3 {x, y, z};
}

std::ostream& operator<<(std::ostream& os, vec3 const& rhs)
{
    os << "[" << rhs[0] << ", " << rhs[1] << ", " << rhs[2] << "]";
    return os;
}

//=================
//===| Vector4 |===
//=================

Vector4::Vector4()
{
    for (int i = 0; i < 4; i++)
    {
        x[i] = 0;
    }
}

Vector4::Vector4(Vector4 const & rhs)
{
    for (int i = 0; i < 4; i++)
    {
        x[i] = rhs.x[i];
    }
}

Vector4::Vector4(std::initializer_list<float> list)
{
    if (list.size() != 4)
    {
        throw std::domain_error("Dimension missmatch in constructor of Vector.");
    }

    for (int i = 0; i < 4; i++)
    {
        x[i] = *(list.begin() + i);
    }
}

float Vector4::length() const
{
    float sum {0};

    for (int i = 0; i < 4; i++)
    {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}


void Vector4::normalize()
{
    operator/=(length());
}


Vector4::Vector4(float tmp[4])
{
    for (int i = 0; i < 4; i++)
    {
        x[i] = tmp[i];
    }
}

Vector4::~Vector4()
{
}

Vector4 Vector4::operator=(Vector4 const & rhs)
{
    for (int i = 0; i < 4; i++)
    {
        x[i] = rhs.x[i];
    }
    return *this;
}

Vector4 Vector4::operator+(Vector4 const & rhs) const
{
    float tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = x[i] + rhs.x[i];
    }
    return Vector4(tmp);
}

Vector4 Vector4::operator+=(Vector4 const & rhs)
{
    *this = operator+(rhs);
    return *this;
}

Vector4 Vector4::operator-(Vector4 const & rhs) const
{
    float tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = x[i] - rhs.x[i];
    }
    return Vector4(tmp);
}

Vector4 Vector4::operator-=(Vector4 const & rhs)
{
    *this = operator-(rhs);
    return *this;
}

Vector4 Vector4::operator*(float f) const
{
    float tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = x[i] * f;
    }
    return Vector4 {tmp};
}

Vector4 Vector4::operator*=(float f)
{
    *this = operator*(f);
    return *this;
}

Vector4 Vector4::operator/(float f) const
{
    return operator*(1.0f / f);
}

Vector4 Vector4::operator/=(float f)
{
    *this = operator/(f);
    return *this;
}

float& Vector4::operator[](int index)
{
    if (index >= 4)
    {
        throw std::logic_error("index out of bounds in vector.");
    }
    return x[index];
}

float Vector4::operator[](int index) const
{
    if (index >= 4)
    {
        throw std::logic_error("index out of bounds in vector.");
    }
    return x[index];
}

float Vector4::operator*(Vector4 const & rhs)
{
    float sum {0};

    for (int i = 0; i < 4; i++)
    {
        sum += x[i] * rhs.x[i];
    }
    return sum;
}

bool Vector4::operator==(Vector4 const & rhs) const
{
    for (int i = 0; i < 4; i++)
    {
        if (x[i] != rhs.x[i])
        {
            return false;
        }
    }
    return true;
}

bool Vector4::operator!=(Vector4 const & rhs) const
{
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream & os, Vector4 const & rhs)
{
    os << "[";
    for (int i = 0; i < 2; i++)
    {
        os << rhs[i] << ", ";
    }
    os << rhs[2] << "]";
    return os;
}