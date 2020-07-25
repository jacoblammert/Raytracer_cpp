//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "Shape.h"

class Plane : public Shape {
public:
    Plane(Vector position, Vector normal);

    Plane(Vector position, Vector normal, Color color);

    int getId() override;

    bool getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) override;

    Vector getNormal(Vector pos) override;

    Vector getMin() override;

    Vector getMax() override;

    Vector getMedian() override;
/**/
    Material* getMaterial() override;
    void setMaterial(Material* material) override;
/**/
    void print() override;

private:
    Vector pos;
    Vector normal;
};


#endif //RAYTRACER_PLANE_H
