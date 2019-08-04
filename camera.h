#pragma once

#include "ray.h"
#include "vector3.h"

class Camera {
    public:
        Camera()
            : m_lower_left_corner (Vector3(-2.0, -1.0, -1.0)),
              m_horizontal        (Vector3( 4.0,  0.0,  0.0)),
              m_vertical          (Vector3( 0.0,  2.0,  0.0)),
              m_camera            (Vector3( 1,  0.0,  2.0)) {}

        // This returns a ray given by the horizontal and vertical fractional coordinates.
        // Both u and v must be in the range [0, 1].
        Ray get_ray(float u, float v) {
            // Calculate a position on the viewing screen.
            Vector3 screen_pos = m_lower_left_corner + u*m_horizontal + v*m_vertical;

            // Calculate a ray from the camera through the position on the viewing screen.
            return Ray(m_camera, screen_pos - m_camera);
        } // get_ray

    private:
        // Position of camera.
        Vector3 m_camera;

        // Position of viewing screen.
        Vector3 m_lower_left_corner;
        Vector3 m_horizontal;
        Vector3 m_vertical;    
}; // class Camera

