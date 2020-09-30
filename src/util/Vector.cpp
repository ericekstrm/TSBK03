#include "Vector.h"

Vector<3> cross(Vector<3> const & lhs, Vector<3> const & rhs)
{
    float x = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    float y = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    float z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return Vector<3> {x, y, z};
}
