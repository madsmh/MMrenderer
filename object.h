#pragma once

#include "vector3.h"
#include "ray.h"


class surface;

// This structure contains information about the intersection between a ray and an object.
struct hit_record
{
    float t;        // Value of ray parameter t at intersection.
    Vector3 point;  // Coordinate of intersection point.
    Vector3 normal; // Unit vector normal to surface at intersection point.
    surface *surface_ptr; // variable to hold surface information
}; // struct hit_record

// Abstract class for surface materials.

class surface {

public:
    virtual bool scatter(const Ray& ray_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) {};

};


// Abstract base class for any visible objects
class Object {

protected:
    surface *m_surface;

public:
    // This function returns true if the given ray intersects with the object,
    // and furthermore if the intersection happens for parameters t in the range
    // [t_min, t_max].
    // If a hit occurs, the structure rec is updated with information about the intersection.
    virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const {};

}; // class Object

