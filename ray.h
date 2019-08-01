#pragma once

#include "vector3.h"

// This class represents a ray (a straight line), described
// by an origin and a direction.
// The direction does not need to have unit length.
// The ray is parametrized by a parameter t.
class Ray
{
    public:
        Ray() {}
        Ray(const Vector3& origin, const Vector3& direction)
            : m_origin(origin), m_direction(direction) {}
        const Vector3& origin() const             { return m_origin; }
        const Vector3& direction() const          { return m_direction; }
        Vector3 point_at_parameter(float t) const { return m_origin + t*m_direction; }

    private:
        Vector3 m_origin;
        Vector3 m_direction;     // Not necessarily unit length
}; // class Ray

