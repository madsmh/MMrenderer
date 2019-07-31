/* Copyright (c) 2019 By the Authors
 *
 * This file is part of MMRender.

    Orbit Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Orbit Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MMRender.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#ifndef MMRENDERER_CAMERA_H
#define MMRENDERER_CAMERA_H

#include "constants.h"
#include "vector3.h"
#include "ray.h"

class camera {

    Vector3 m_position; // Camera position
    Vector3 m_u, m_v, m_w;
    Vector3 m_lower_left_corner;
    Vector3 m_horizontal, m_vertical;
    double m_aspect, m_focal_length, m_lens_radius, m_t0, m_t1;

    Vector3 random_in_unit_disc(){
        Vector3 p;
        do {
            p = 2.0*Vector3(drand48(),drand48(), 0.0)-Vector3(1.0, 1.0, 0.0);
        } while (p.norm2() >= 1.0);

        return p;
    }

public:
    camera(Vector3 position, Vector3 direction, Vector3 vup, double vfov,
            double aspect, double aperature, double focus_dist, double t0, double t1){
        m_lens_radius = aperature/2.0;
        m_t0 = t0, m_t1 = t1;
        m_position = position;

        m_w = position - direction;
        m_w.normalize();
        m_u = cross(vup, m_w);
        m_u.normalize();
        m_v = cross(m_w,m_u);

        double theta = vfov*PI/180.0;
        double half_height = std::tan(theta/2);
        double half_width = aspect*half_height;

        m_lower_left_corner = m_position - half_width*focus_dist*m_u-half_height*focus_dist*m_v - focus_dist*m_w;
        m_horizontal = 2*half_width*focus_dist*m_u;
        m_vertical = 2*half_height*focus_dist*m_v;

    }

    ray getRay(double s, double t){
        Vector3 rd = m_lens_radius*random_in_unit_disc();
        Vector3 offset = m_u* rd[0] + m_v*rd[1];
        double time = m_t0+drand48()*(m_t1-m_t0);
        return ray(m_position + offset, m_lower_left_corner + s*m_horizontal + t*m_vertical - m_position - offset, time);
    }
};


#endif //MMRENDERER_CAMERA_H
