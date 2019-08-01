#pragma once

#include "vector3.h"
#include "ray.h"

// This structure contains information about the intersection between a ray and an object.
struct hit_record
{
    float t;        // Value of ray parameter t at intersection.
    Vector3 point;  // Coordinate of intersection point.
    Vector3 normal; // Unit vector normal to surface at intersection point.
}; // struct hit_record

// Abstract base class for any visible objects
class Object {
    public:
        // This function returns true if the given ray intersects with the object,
        // and furthermore if the intersection happens for parameters t in the range
        // [t_min, t_max].
        // If a hit occurs, the structure rec is updated with information about the intersection.
        virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const = 0;
}; // class Object

