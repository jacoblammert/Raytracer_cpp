//
// Created by Jacob on 21.04.2020.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H


#include "Shape.h"
#include <vector>

class Box : public Shape {
public:
    Box();

    Box(Vector minXminYminZ, Vector maxXmaxYmaxZ);

    Box(Vector Pos, float xScale, float yScale, float zScale);

    Box(Vector minXminYminZ, Vector maxXmaxYmaxZ, Vector color);

    Box(Vector Pos, float xScale, float yScale, float zScale, Vector color);

    int getId() override;

    Vector getRgb() override;

    bool getIntersectVec(Ray ray, Vector &HitPoint, Vector &HitNormal, float &distance, int &id, int &newid) override;

    bool getIntersect(Ray ray);

    Vector getNormal(Vector pos) override;

    Vector getMin() override;

    Vector getMax() override;

    Vector getMedian() override;

    void print() override;

private:
    std::vector<Vector> bounds;

    Vector position;

};


#endif //RAYTRACER_BOX_H
