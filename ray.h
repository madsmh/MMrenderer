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

#ifndef MMRENDERER_RAY_H
#define MMRENDERER_RAY_H


#include "vector3.h"

class ray {
    Vector3 m_origin, m_direction;
    double m_time;

public:
    ray(const Vector3 origin, const Vector3 direction, double time = 0.0){
        m_origin = origin, m_direction = direction, m_time = time;
    }

    Vector3 origin() const { return  m_origin;}
    Vector3 direction() const  { return m_direction;}
    Vector3 ptAtParam (double t) const { return m_origin + t * m_direction;}
    double time() const  {return m_time;}
};


#endif //MMRENDERER_RAY_H
