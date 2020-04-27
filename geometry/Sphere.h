//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(Vector position, float radius);

    Sphere(Vector position, float radius, Color color);

    int getId() override;

    Color getRgb() override;

    bool getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) override;

    Vector getNormal(Vector pos) override;

    Vector getMin() override;

    Vector getMax() override;

    Vector getMedian() override;
/**/
    Material getMaterial() override;

    void setMaterial(Material material) override;
/**/
    void print() override;

private:
    Vector pos;
    float radius;
};


#endif //RAYTRACER_SPHERE_H
