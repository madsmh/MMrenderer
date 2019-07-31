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


#ifndef MMRENDERER_SCENE_H
#define MMRENDERER_SCENE_H


#include <vector>

#include "camera.h"
#include "solid.h"
#include "material.h"

struct hit_record {
    double t;
    double u;
    double v;
    Vector3 p;
    Vector3 normal;
    material *mat_ptr;


};

class scene {

    std::vector<camera> m_cam_list;
    std::vector<solid> m_object_list;

    void getRays();

public:
    //Constructors
    scene(std::vector<camera> camera_list, std::vector<solid> object_list);
    scene(camera c, std::vector<solid> object_list);

    // Utility functions
    void movePrimeCamera(Vector3 new_position);
    void moveAllCameras(std::vector<Vector3> new_positions);
    void moveObjects(std::vector<Vector3> new_positions);

    void callculateHits();
    void render();
};


#endif //MMRENDERER_SCENE_H
