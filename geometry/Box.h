//
// Created by Jacob on 21.04.2020.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H


#include "Shape.h"
#include <vector>

class Box: public Shape{
public:
    Box(Vector minXminYminZ, Vector maxXmaxYmaxZ);
    Box(Vector minXminYminZ, Vector maxXmaxYmaxZ,Vector color);

    int getId() override;
    Vector getRgb() override;
    bool getIntersectVec(Ray ray, Vector& HitPoint, Vector& HitNormal, float &distance, int &id, int &newid) override;
    Vector getNormal(Vector pos) override;

private:
std::vector<Vector> bounds;

};


#endif //RAYTRACER_BOX_H
