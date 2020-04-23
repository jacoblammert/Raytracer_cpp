//
// Created by Jacob on 18.04.2020.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H


#include "../math/Vector.h"
#include "../math/Ray.h"

class Shape {
public:
    virtual int getId() = 0;

    virtual Vector getRgb() = 0;

    virtual bool getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id,
                                 int &newid) = 0; // returns true, if the Ray and the object intersect
    virtual Vector getNormal(Vector pos) = 0;

    virtual Vector getMin() = 0;

    virtual Vector getMax() = 0;

    virtual Vector getMedian() = 0;

    virtual void print() = 0;

protected:
    int id;
    Vector color;
};


#endif //RAYTRACER_SHAPE_H
