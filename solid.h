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


#ifndef MMRENDERER_SOLID_H
#define MMRENDERER_SOLID_H


#include "ray.h"
#include "vector3.h"

class solid {

protected:
    Vector3 m_position;

public:
    virtual bool isHit (ray& r, double t_min, double t_max) const;
    virtual double pdf_value(Vector3 o, Vector3 v);
    virtual Vector3 random(const Vector3& o){ return Vector3(1.0, 0.0, 0.0);}
};


#endif //MMRENDERER_SOLID_H
