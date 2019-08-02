//
// Created by mads on 02/08/2019.
//

#ifndef MMRENDERER_SURFACES_H
#define MMRENDERER_SURFACES_H


#include "object.h"

class lambartian : public surface {
private:
    Vector3 albedo;

public:
    explicit lambartian(Vector3 a): albedo(a) {};

    Vector3 randomUnitVector() {
        Vector3 temp;

        temp =Vector3(drand48(), drand48(), drand48());
        temp.normalize();

        return temp;
    }

    virtual bool scatter(const Ray& ray_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) {
        Vector3 target = rec.point + rec.normal + randomUnitVector();
        Vector3 direction = target-rec.point;
        direction.normalize();

        scattered = Ray(rec.point, direction);

        attenuation = albedo;
        return true;
    }


};

class metal : public surface{
private:

    Vector3 m_albedo;

public:

    metal(Vector3 a): m_albedo(a) {};

    Vector3 reflect (const Vector3& v, const Vector3& n){
        return v - 2.0*dot(v, n)*n;
    }

    virtual bool scatter(const Ray& ray_in, const hit_record& rec, Vector3& attenuation, Ray& scattered){
        Vector3 unit_ray_in = ray_in.direction();
        unit_ray_in.normalize();

        Vector3 reflected = reflect(unit_ray_in, rec.normal);
        scattered = Ray(rec.point, reflected);
        attenuation = m_albedo;
        return (dot(scattered.direction(), rec.normal)>0);
    }
};


#endif //MMRENDERER_SURFACES_H
