#pragma once

#include "object.h"

// The sphere object is characterized by only its center and its radius.
class Sphere : public Object {
    public:
        Sphere(const Vector3& center, float radius, float diffuse = 1.0, float reflection = 0.0, float refraction = 0.0, float opacity = 1.0){
            m_center=center;
            m_radius=radius;
            m_surface = surface(diffuse, reflection, refraction, opacity);
        }
        virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const;

    private:
        Vector3 m_center;
        float   m_radius;
}; // class Sphere


bool Sphere::hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const {
    // This basically solves the equation:
    // |p(t)−C|^2 = R^2, where C and R are the center and radius of the circle
    // and p(t)=O+t*D is a point on the ray. Here O is the origin of the ray, and D is the
    // direction of the ray.
    //
    // Expanding out, this gives the following quadratic equation:
    // a*t^2 + 2*b*t + c = 0, where
    // a = |D|^2
    // b = dot(D, CO)
    // c = |CO|^2 - R^2
    //
    // So there are potentially two points on the sphere intersection with the ray.
    // Only the closest intersection is needed. This is assumed to correspond
    // to the smallest value of the parameter t.
    Vector3 co = ray.origin() - m_center;
    float a    = ray.direction().norm2();
    float b    = dot(ray.direction(), co);
    float c    = co.norm2() - m_radius*m_radius;

    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        // Find the two solutions to the quadratic equation,
        // such that t1 < t2.
        float t1 = (-b - sqrt(discriminant))/a;
        float t2 = (-b + sqrt(discriminant))/a;

        // Check the smallest value t1 first
        if (t1 < t_max && t1 > t_min) {
            rec.t      = t1;
            rec.point  = ray.point_at_parameter(t1);
            rec.normal = (rec.point - m_center) / m_radius; // Make sure it is unit length by dividing by radius
            rec.surface_settings = m_surface;
            return true;
        }

        // Check the largest value t2 last
        if (t2 < t_max && t2 > t_min) {
            rec.t      = t2;
            rec.point  = ray.point_at_parameter(t2);
            rec.normal = (rec.point - m_center) / m_radius; // Make sure it is unit length by dividing by radius
            rec.surface_settings = m_surface;
            return true;
        }
    }
    return false;
} // hit

