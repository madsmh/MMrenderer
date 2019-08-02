//
// Created by mads on 02/08/2019.
//

#ifndef MMRENDERER_LAMBARTIAN_H
#define MMRENDERER_LAMBARTIAN_H


#include "object.h"

class lambartian : public surface {
private:
    Vector3 albedo;

public:
    explicit lambartian(Vector3 a): albedo(a){};

    Vector3 randomUnitVector(){
        Vector3 temp;

        do {
            temp = 2.0*Vector3(drand48(), drand48(), drand48()) - Vector3(1.0, 1.0, 1.0);
        } while (temp.norm2()>= 1.0);
        return temp;
    }

    virtual bool scatter(const Ray ray_in, const hit_record& rec, Vector3 attenuation, Ray& scattered ){
        Vector3 target = rec.point + rec.normal + randomUnitVector();
        scattered = Ray(rec.point, target-rec.point);

        m_attenuation = attenuation;
        return true;
    }


};


#endif //MMRENDERER_LAMBARTIAN_H
