//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"

class Sphere: public Shape{
public:
    Sphere(Vector position, float radius);
    Sphere(Vector position, float radius, Vector color);

    int getId() override;
    Vector getRgb() override;
    virtual bool getIntersectVec(Ray ray, Vector& HitPoint, Vector& HitNormal) override;
    Vector getNormal(Vector pos) override;

private:
    Vector pos;
    float radius;
};


#endif //RAYTRACER_SPHERE_H
