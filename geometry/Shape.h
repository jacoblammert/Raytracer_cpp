//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H


#include "../math/Vector.h"
#include "../math/Ray.h"
#include "Color.h"
#include "Material.h"

class Shape {
public:

    virtual bool getIntersectVec(Ray ray, Vector &HitPoint,Vector &Hitnormal, float &distance) = 0; // returns true, if the Ray and the object intersect

    virtual Vector getNormal(Vector pos) = 0;

    virtual Vector getMin() = 0;

    virtual Vector getMax() = 0;

    virtual Vector getMedian() = 0;

    virtual Material* getMaterial() = 0; // needs override for composite object

    virtual void setMaterial(Material* material) = 0; // needs override for composite object

    virtual void print() = 0;

    virtual void translate(Vector position) = 0;

protected:
    Material* material;
};


#endif //RAYTRACER_SHAPE_H
