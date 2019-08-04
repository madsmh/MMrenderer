#pragma once

#include "ray.h"
#include "vector3.h"

static inline std::string float_to_string(float arg) {
    if (arg >= 0.0) {
        return std::to_string(arg).substr(0,4);
    } else {
        return std::to_string(arg).substr(0,5);
    }
} // float_to_string

class Camera {
    public:
        Camera()
            : m_lower_left_corner (Vector3(-2.0, -1.0, -1.0)),
              m_horizontal        (Vector3( 4.0,  0.0,  0.0)),
              m_vertical          (Vector3( 0.0,  2.0,  0.0)),
              m_camera            (Vector3( 0.0,  0.0,  3.0)) {}

        // This returns a ray given by the horizontal and vertical fractional coordinates.
        // Both u and v must be in the range [0, 1].
        Ray get_ray(float u, float v) {
            // The direction of the ray is entirely determined by the coordinates (u,v), i.e.
            // the position on the screen.
            return Ray(m_camera, Vector3(tan(1.0*(u-0.5)), tan(0.5*(v-0.5)), -1.0));
        } // get_ray

        void move(const Vector3& delta) {
            m_camera            += delta;
            m_lower_left_corner += delta;
        } // move

        std::string to_string() const {
            return float_to_string(m_camera[0]) + " " +
                   float_to_string(m_camera[1]) + " " +
                   float_to_string(m_camera[2]);
        } // to_string

    private:
        // Position of camera.
        Vector3 m_camera;

        // Position of viewing screen.
        Vector3 m_lower_left_corner;
        Vector3 m_horizontal;
        Vector3 m_vertical;    
}; // class Camera

