#pragma once

#include <vector>
#include "object.h"
#include "ray.h"

// The scene is described by a list of generic objects.
// I.e., all objects in the scene must derive from the Object base class.
// The function hit returns true if the given ray intersects with any object in the scene.
// and furthermore if the intersection happens for parameters t in the range
// [t_min, t_max].
// If a hit occurs, the structure rec is updated with information about the closest intersection,
// i.e. corresponding to points with the smallest value of the parameter t.

class Scene : public std::vector<Object*> {
    public:
        bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const {
            hit_record temp_rec;
            bool       hit_anything   = false;
            double     closest_so_far = t_max;
            for (auto it=begin(); it!=end(); ++it) {
                if ((*it)->hit(ray, t_min, closest_so_far, temp_rec)) {
                    hit_anything   = true;
                    closest_so_far = temp_rec.t;
                    rec            = temp_rec;
                }
            }
            return hit_anything;
        } // hit

}; // class Scene

