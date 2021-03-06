//
// Created by Jacob on 21.04.2020.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H


#include "Shape.h"
#include <vector>

class Box: public Shape {
public:
    Box();

    Box(Vector minXminYminZ, Vector maxXmaxYmaxZ);

    Box(Vector Pos, float xScale, float yScale, float zScale);

    Box(Vector minXminYminZ, Vector maxXmaxYmaxZ, Color color);

    Box(Vector Pos, float xScale, float yScale, float zScale, Color color);

    //int getId() override;

    void translate(Vector position) override;

    bool getIntersectVec(Intersect* intersect) override;

    void getIntersectVec(Vector &direction,  Vector &HitNormal);

    bool getIntersect(Ray ray);

    float getDistance(Ray ray);

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
    std::vector<Vector> bounds;


    Vector position;

};


#endif //RAYTRACER_BOX_H
