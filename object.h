#pragma once

#include "vector3.h"
#include "ray.h"

class surface {
private:
    // diffuse and reflection are percentages 0-1, refractive_index is arbitrary.
    float m_diffuse, m_reflection, m_refractive_index, m_opacity;
    Vector3 m_color;
public:
    surface(float diffuse = 1.0, float reflection=0.0, float refractive_index = 0.0, float opacity = 1.0, Vector3 color = Vector3(1.0, 1.0, 1.0)){
        m_diffuse = diffuse;
        m_reflection = reflection;
        m_refractive_index = refractive_index;
        m_opacity = opacity;
        m_color = color;
    }

    float getDiffuse(){
        return m_diffuse;
    }

    float getReflection(){
        return m_reflection;
    }

    float getOpacity(){
        return m_opacity;
    }

    float getRefractiveIndex(){
        return m_refractive_index;
    }

    Vector3 getColor(){
        return m_color;
    }
};

// This structure contains information about the intersection between a ray and an object.
struct hit_record
{
    float t;        // Value of ray parameter t at intersection.
    Vector3 point;  // Coordinate of intersection point.
    Vector3 normal; // Unit vector normal to surface at intersection point.
    surface surface_settings; // variable to hold surface information
}; // struct hit_record

// Abstract base class for any visible objects
class Object {

protected:
    surface m_surface;

public:
    // This function returns true if the given ray intersects with the object,
    // and furthermore if the intersection happens for parameters t in the range
    // [t_min, t_max].
    // If a hit occurs, the structure rec is updated with information about the intersection.
    virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const = 0;

    surface getSurface(){
        return m_surface;
    }
}; // class Object

